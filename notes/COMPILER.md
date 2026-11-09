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
| NitroSystem | present (hypothesis from `.nsbmd` / `.nsbtx` game files); version unknown | game file names |
| MSL, C++ runtime | not looked for yet | — |

## Code generation (dsd analysis)

- Main module: 5859 functions, 1632 of them Thumb (`config/jpn/arm9/symbols.txt`).
  Which regions are Thumb (game code or libraries) is not known yet.
- No `.init` section and an empty `.ctor` in the main module; overlays 2 and 3 have a
  non-empty `.ctor`.

## Compiler (not identified)

- `tools/configure.py` uses mwccarm 2.0/sp1p5 with twewy's flags without `-ipa file`
  (`-O4,p -enum int -char signed -proc arm946e -gccext,on -fp soft -inline noauto
  -RTTI off -interworking -str reuse -Cpp_exceptions off ...`). This is a placeholder
  taken from ts2-castaway, **not evidence**: the all-assembly build does not use the
  compiler.
- To do: `tools/compiler_sweep.py` on NitroSDK functions and game
  leaf functions, ARM and Thumb, with every mwccarm family (1.2, 2.0, DSi).
- Reference points, not evidence: dqix-decomp (Dragon Quest IX, 2009) uses 2.0/sp2p2
  for the game and 2.0/sp1p2 for its SDK; DQIV-DECOMP uses 2.0/sp1p6.

## Linker

- `-proc arm946e -interworking -dead -nostdlib -m Entry` (from ts2-castaway). The
  all-assembly build links and matches with it; whether the original link stripped
  dead code (C1/C2, D1/D2 variants) is to be checked when the first C++ unit links.
