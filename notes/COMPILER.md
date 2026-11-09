# Compiler, SDK and runtime

What is known about the tools the original was built with. Every line has its
evidence; the rest is a hypothesis and is labelled so.

## SDK and middleware (evidence: the ROM)

| Item | Value | Evidence |
|---|---|---|
| NitroSDK | version word `0x04027539`: 4.2, relstep 30009 | `extract/jpn/arm9/arm9.yaml` (`sdk_version`; build info at 0x02000B68) |
| Backup library | `[SDK+NINTENDO:BACKUP]` | string at 0x02000B8C |
| Ubiquitous CPS / SSL | `[SDK+UBIQUITOUS:CPS]`, `[SDK+UBIQUITOUS:SSL]` | strings at 0x02000BA4, 0x02000BE4 |
| NITRO WiFi | `[SDK+NINTENDO:WiFi2.1.30003.0709200229]` | string at 0x02000BBC |
| DWC (Nintendo Wi-Fi Connection) | `[SDK+NINTENDO:DWC3.1.30006.20090131.2222_DWC_3_1_PLUS6]` | string at 0x02000BFC |
| NitroSystem | present (FND, G3D, G2D, SND, GFD at 0x0202A1D8-0x0203C130); version unknown | `compiler_sweep.py` hits, khdays `libs/nns` (`notes/SPLITS.md`) |
| MSL | present: 18 MSL C functions found by the sweep (`strcpy`, `strtol`, `abs`, `_ll_mul`, ...) at 0x0201AD84-0x020266D8 | `compiler_sweep.py`, khdays `libs/msl` |
| C++ runtime | not looked for yet | — |

## Code generation (dsd analysis)

- Main module: 5859 functions, 1632 of them Thumb (`config/jpn/arm9/symbols.txt`).
  The Thumb code is the WiFi libraries (DWC, GameSpy, 0x02084880-0x020B32E0) and
  a block using a Square Enix server (0x020B3358-0x020B4AF8); ov004's Thumb block is
  the DWC setup utility. The game code found so far is all ARM (`notes/SPLITS.md`).
- No `.init` section and an empty `.ctor` in the main module; overlays 2 and 3 have a
  non-empty `.ctor`.

## Compiler

Method: `tools/compiler_sweep.py` compiles reference sources with every mwccarm in
`tools/mwccarm/` (project flags, `-lang=c99`) and searches each function in the
extracted main, ITCM, DTCM and overlay modules with relocated words masked. A hit at
one address only counts. Sweeps of 2026-11-09 (dsd 0.12.1, flags of
`tools/configure.py` at that date).

Tool fix found on the way: mwccarm writes `SHT_RELA` relocation sections (12-byte
entries), and the sweep only masked `SHT_REL`, so a function with a relocated word
(literal pool pointer, call) could never match. The ts2-castaway copy of the script
has the same limitation.

### Libraries (NitroSDK, NitroSystem, MSL): 2.0/sp2p2, sp2p3 or sp2p4

| Sources | Unique functions | Result |
|---|---|---|
| twewy `libs/nitro/src/*/*.c`, every compiler | 151 with each 2.0 sp1 ... sp2p4; 135 with 2.0/base; ≤ 89 with DSi; ≤ 30 with 1.2 | 2.0 sp1 or later |
| khdays-decomp `libs/{nitro,nns,msl}` (`.c`), 2.0 base ... sp2p4, 1.2/sp4, dsi/1.2 | 851 with each 2.0 sp2p2 / sp2p3 / sp2p4; 847 with sp1p6 ... sp2; 846 with sp1 ... sp1p5; 811 with base | 2.0 sp2p2 or later |

Every one of the 851 functions is produced by sp2p2, sp2p3 and sp2p4; four are
produced by no earlier version:

| Address | Function | Library |
|---|---|---|
| 0x02006B7C | `OS_Sleep` | NitroSDK OS |
| 0x0203262C | `getTransData_` | NitroSystem G3D |
| 0x020328E0 | khdays `func_02017bec` | NitroSystem (khdays `libs/nitro/nns`) |
| 0x02039C9C | `NNS_SndArcStrmGetCurrentPlayingPos` | NitroSystem sound (also dsi/1.2) |

The difference is the same in all of them: for a 32x32 -> 64-bit unsigned product,
2.0/sp2 and earlier zero a register and emit two `mla` with it for the (null) high
words (`mov r2, #0; umull; mla; mla`); sp2p2 and later emit the `umull` alone. That
pattern (`mla` on a register set to 0 just before a `umull`) occurs nowhere in the ROM
(main, ITCM, overlays: about 1200 `umull` / `smull`).

Address ranges of the hits (hypothesis for the region map, Step 4): all library hits
of the main module lie in 0x02000950-0x0203C0C8 (NitroSDK mostly below 0x0201A000, MSL
0x0201AD84-0x020266D8, NitroSystem 0x0202A1D8-0x0203C044), plus 10 in ITCM; none in
the overlays. The khdays folders mix some code of other libraries, so a folder name
is not a library proof.

### Game code: 2.0 family, service pack open

Leaf functions written from the disassembly (scratch files, not in `src/`), all flags
of `tools/configure.py`:

| Function | Compilers that produce it |
|---|---|
| `func_0203d030`, `func_02041000` | every family (not distinctive) |
| `func_0203e7d4` | 2.0 (base ... sp2p4) and DSi; not 1.2 |
| `func_02041544` | 2.0 base ... sp2p4 only |
| `func_02068cc0`, `func_02068cf0` | 1.2 and 2.0; not DSi |
| `func_02045f84`, `func_0204cc6c` | 2.0 base ... sp2p4 (only 2.0 tried) |
| `func_ov000_02204dec` (s64 fixed-point square) | 2.0 and DSi |
| `func_ov001_021fbbe4` (divide by 5) | 2.0 and DSi (1.3 and later not checked) |

So the game code is built with the 2.0 family; nothing so far separates base ... sp2p4.
The sp2 / sp2p2 product difference above cannot be used: the game code has no 64-bit
unsigned product (its plain `umull` are divisions by constants, the same with every
2.0). `MWCC_DEFAULT_VERSION` is 2.0/sp2p2, the lowest version consistent with both the
libraries and the game code: provisional for the game code.

Flags: the functions above match with `-O4,p -inline noauto` and the rest of
`configure.py`'s flags; nothing proves the other flags yet.

Open points:

- `func_ov000_021df200` (`(x + 11) / 12`) and `func_ov001_02215268` (`x / 10 + 1`) are
  leaves that still save `{r3, lr}`; no flag tried (`-O4,p/s`, `-O3`, `-O2`, `-O1`,
  `-O0`, `-ipa file`, `-inline auto`) with 2.0 base, sp1p5 or sp2p2 reproduces that
  prologue, so the source is likely different (inlined call, C++); not explained.
- Several loop functions (`func_02060510`, `func_020608e0`, `func_02060a6c`,
  `func_02077224`) differ only in register allocation with the C tried; to retry when
  their units are delinked.
- Service pack of the game code: probe larger functions (switches, struct copies,
  inlining) with base ... sp2p4. The first `complete` unit (`unit_02040BD8.cpp`,
  26 functions, a switch and calls to `_s32_div_f`) compiles to the same bytes with
  every 2.0 from base to sp2p4, so it does not settle it. Same for the first
  overlay unit (`src/ov005/unit_021CD658.cpp`: its eight 100 % functions with base,
  sp1p5, sp2, sp2p2 and sp2p4). This is also why the trace tools (`mwcc_irdump.py`,
  `mwcc_blocks.py`, `mwcc_sched.py`), bound to 2.0/sp1p5's binary, still describe the
  build's code.
- Reference points, not evidence: dqix-decomp (Dragon Quest IX, 2009) uses 2.0/sp2p2
  for the game and 2.0/sp1p2 for its SDK; DQIV-DECOMP uses 2.0/sp1p6.

- Function order: mwccarm 2.0 writes one `.text` section per function, in reverse
  source order (a file with `f` then `g` links as `g`, `f`). Every library unit
  built from merged reference sources needed the sources in reverse address order
  (`tools/lib_unit_gen.py` tries that order first).

## Linker

- `-proc arm946e -interworking -dead -nostdlib -m Entry` (from ts2-castaway).
  `-dead` drops a function that nothing calls, while the ROM holds such functions
  (`OS_DisableProtectionUnit`); `#pragma force_active on` does not keep an `asm`
  function, so `tools/lcf_keep.py` lists every function of the units with a source
  in a `FORCE_ACTIVE` block of the link script. The
  all-assembly build links and matches with it; whether the original link stripped
  dead code (C1/C2, D1/D2 variants) is to be checked when the first C++ unit links.
