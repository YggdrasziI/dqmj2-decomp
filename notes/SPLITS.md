# Splits

Region map and unit table of every module. Bounds found from call clusters, literal
pools or string runs are hypotheses until the unit matches (`SPEC.md`).

## Modules (dsd analysis, 2026-11-08)

| Module | Range | Functions | Notes |
|---|---|---|---|
| main | `.text` 0x02000000-0x020BCE10, `.bss` end 0x021CB360 | 5859 (1632 Thumb) | crt0 at 0x02000800; SDK markers from 0x02000B8C |
| ITCM | 0x01FF8000-0x01FFF72C, `.bss` -0x01FFF980 | 151 | |
| DTCM | 0x027E0000-0x027E0080 | — | data and bss only |
| ov000 | 0x021CB360-0x02240BA0 | 2073 | |
| ov001 | 0x021CB360-0x02231960 | 1994 | |
| ov002 | 0x021CB360-0x021CD340 | 59 | DS Protect |
| ov003 | 0x021CB360-0x021DF040 | 251 | |
| ov004 | 0x021CB360-0x0220CCC0 | 2805 | |
| ov005 | 0x021CB360-0x021CF260 | 98 | |

All overlays share one load address, so only one is resident at a time. Their roles
are in the region map below.

## Region map (2026-11-09)

Each region gives its evidence. The tools are `tools/module_map.py` (ARM / Thumb runs,
strings loaded by a range, runs of sweep hits) and `tools/compiler_sweep.py` (library
functions compiled from the reference projects, `notes/COMPILER.md`). A string or a
sweep hit shows what a region holds, not its exact bounds: the bounds below are those
of the evidence (first and last hit, mode change), and a bound is only proven when the
unit on it matches. "Hypothesis" marks a region whose content is inferred, not shown.

### main

| Range | Content | Evidence |
|---|---|---|
| 0x02000000-0x02000800 | secure area: BIOS call veneers and data | starts with the words 0xE7FFDEFF (the decrypted secure area marker, GBATEK); dsd found and named 18 Thumb BIOS call veneers in it (`Halt`, `IntrWait`, `CpuSet`, `Div`, `Sqrt`, ...: 4-6 bytes each). The rest is not identified |
| 0x02000800-0x02000B68 | NitroSDK crt0 (`Entry`, `AutoloadCallback`, 8 functions) | entry point of `arm9.yaml`; sweep hits of khdays `libs/nitro/init` (`MIi_UncompressBackward` at 0x02000950, next to `Entry.c`) |
| 0x02000B68-0x02000C34 | build info and `[SDK+...]` markers (data) | `arm9.yaml` (`build_info`), strings at 0x02000B8C-0x02000C34 |
| 0x02000C34-0x02000C90 | `main` (dsd name, 0x50 bytes) and one Thumb function | owner unknown |
| 0x02000C90-0x0201AD84 | NitroSDK (MTX, FX, GX, OS, MI, SND, PXI, FS, DGT, MATH, CP, TP, RTC, CARD, WM, CTRDG, STD) | sweep hits from 0x02000C90 (`MTX_ScaleApply22`) to 0x02019B80 (`STD_GetStringLength`). 0x02019B80-0x0201AD84 has no hit (hypothesis: still STD / SDK) |
| 0x0201AD84-0x020266D8 | MSL C | sweep hits (`abs` at 0x0201AD84 ... ) |
| 0x020266D8-0x0202A1D8 | MSL runtime, then unknown | `__call_static_initializers` at 0x020266D8; the rest has no hit and no string (hypothesis: runtime helpers, soft-float, C++ runtime) |
| 0x0202A1D8-0x0203C130 | NitroSystem (FND, G3D, G2D, SND, GFD) | sweep hits from 0x0202A1D8 (`NNS_FndAllocFromAllocator`) to 0x0203C0C8 (`GFXi_EnqueueCommand`) |
| 0x0203C130-0x02084880 | game code (ARM) | no library hit; the first game unit (`unit_02040BD8`) and the game leaves of `notes/COMPILER.md` are here; calls into the ITCM game code. Three 16-byte twewy hits (0x02062C74, 0x02062D48, 0x0207E958, `GX_GetBankFor*`) are field getters that happen to match: not library code |
| 0x02084880-0x020B32E0 | Nintendo Wi-Fi Connection: DWC and GameSpy (Thumb) | Thumb run; strings `"DWCauth"`, `"https://nas.nintendowifi.net/ac"`, `"Nitro WiFi SDK/%d.%d"` (0x02088FA0-0x02095F24), then GameSpy `"GPCM"` (0x02096ED0), `"dwc_pid"`, `"%s.ms%d.gs.nintendowifi.net"`, `"natneg1.gs.nintendowifi.net"` ... (to 0x020B3224); `[SDK+NINTENDO:DWC3.1...]` marker. Where WiFi SOC / CPS / SSL (`[SDK+UBIQUITOUS:CPS]`, `SSL`) sit is not known: 0x02084880-0x02088FA0 loads no string |
| 0x020B3358-0x020B4AF8 | Thumb code using `"wf001.wifi.square-enix.com"` (0x020B4264) | hypothesis: Square Enix network code built like the libraries (Thumb) |
| 0x020B4AF8-0x020BCE10 | game WiFi code (ARM) | strings `"dqmonjoker2ds"` and `"MXsuQS"` (GameSpy game name and key, 0x020B5024), `"msg_wifi"` (0x020BC98C); calls into the ITCM game code |

### ITCM

| Range | Content | Evidence |
|---|---|---|
| 0x01FF8000-0x01FF8580 | NitroSDK (OS reset, MI DMA) | 10 sweep hits from 0x01FF8000 to 0x01FF851C; called from the SDK range of main (and once from the WiFi range) |
| 0x01FF8580-0x01FFF72C | game code placed in ITCM (hypothesis) | no library hit; called from main game code (0x02043000-0x02084FFF, 0x020B6000-0x020BCFFF) and ov000, and calls main game code (0x0203C000-0x02084FFF) |

### DTCM

0x027E0000-0x027E0080: data and `.bss` only (dsd), owner unknown.

### Overlays

The role of each overlay is inferred from the game files and strings its code loads
(hypothesis: a role, not a name).

| Overlay | Role (hypothesis) | Evidence |
|---|---|---|
| ov000 | field, synthesis, library (monsters, skills) | ARM only; loads `FldChrTbl.bin`, `FldObjTbl.bin`, `FldEnmyPrm2.bin`, `d2_ObjNaviMapData.bin`, `Combination*Tbl.bin`, `MonsLibTbl.bin`, `SkillLibTbl.bin` |
| ov001 | battle | ARM only; loads `BtlChrTbl.bin`, `BtlEnmyPrm2.bin`, `BtlSts*Tbl.bin`, `AI*Tbl.bin`, `d2_ObjBattleData.bin`, `d2_ObjScoutValueData.bin` |
| ov002 | protection code | DS Protect (`SPEC.md`); no string |
| ov003 | link with the arcade game Monster Battle Road II | ARM only; strings `"MonsterBattleRoadII"`, `"10.168.10.2"`; loads `d2_ObjBR2Data.bin`, `d2_ObjPastData.bin`, `d2_ObjPastVsData.bin` |
| ov004 | WiFi mode: game ARM 0x021CB360-0x021E116C and 0x021FA028-0x021FD4DC, Nintendo WFC setup utility in Thumb 0x021E116C-0x021FA028 | game part loads `"msg_shop"`, `friend_status_icon.pal`, `flag.bin`; Thumb part loads `rom:/dwc/utility.bin`, `"ESSID-AOSS"`, `"MELCO"`, `char/*.ncg.l`, `msg/usa.bmg.l` (the DWC utility's own resources) |
| ov005 | world map | ARM only; loads `"world.e"`, `"world.ez%c"`, `d2_ObjWorldData.bin` |

No overlay has a library sweep hit (`notes/COMPILER.md`).

### Library units (2026-11-09)

`tools/sweep_names.py` read the sweep of khdays `libs/{msl,nitro,nns}` and twewy
`libs/nitro` with 2.0/sp2p2 (`compiler_sweep.py --json`, 993 unique hits) and kept
848 whole library functions (one address, the whole dsd function, more than 8 bytes,
in main 0x02000800-0x0203C130 or ITCM 0x01FF8000-0x01FF8580). 772 dsd names were
replaced by the references' names (`SPEC.md`); 75 kept hits have no usable name.
Each run of consecutive kept functions from one reference folder is a library unit
in `delinks.txt` (`.text` only, not `complete`, no source yet): 226 in main, 3 in
ITCM, 848 functions. Their bounds are hypotheses: a unit can lack unnamed functions
of its file, or join two files; their data sections are not assigned.

One bound set by hand: `libs/nitro/src/dgt/unit_0200D630.c` starts at 0x0200D630,
before `DGTi_Hash2ProcessBlock` (0x0200D644), to hold the five SHA-1 constant words
(0x00FF00FF, 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6) that it reads
pc-relative; without them the link moved every later function by 0x14 bytes.

Sources (2026-11-09, `tools/lib_unit_gen.py`): each library unit's source is the
merge of the reference sources of its functions, checked against the delinked
original (bytes with relocated words masked, relocation types, symbols and addends)
before it is written. A unit whose merged sources do not build or match is split
into one unit per reference file (each built alone in the sweep), which is why most
library units hold one to three functions: a finer cut than the real files, still a
hypothesis. 657 of the 659 library units (653 main, 4 ITCM; 109456 bytes) are
`complete`; 68 of them came after fixes to the configuration and to the generator
(missing or inner-symbol relocations, header macros, twewy headers, edited drafts:
`notes/MATCHING.md`, "Data addressing" and "Link-defined values").
`libs/nitro/src/gx/unit_020038A8.c` matches on Windows but not under wibo in CI
(`notes/COMPILER.md`), so it stays not `complete`.

Eight units needed their own data, link-defined values or asm data:

| Unit | Function | How it matches |
|---|---|---|
| `os/unit_02005DAC.c` | `OSi_InitStackChecker` | `SDK_IRQ_STACKSIZE` defined by the link (`tools/lcf_keep.py`) |
| `os/unit_02005DE0.c` | `OS_InitLock` | the init lock word at 0x027FFFF0, reached through the symbol `data_027ffff0` that the link defines; a constant address schedules the stores differently |
| `os/unit_02007560.c` | `OS_GetInitArenaHi` | `SDK_SYS_STACKSIZE`, `SDK_IRQ_STACKSIZE` and `SDK_SECTION_ARENA_DTCM_START` defined by the link |
| `snd/unit_020095E8.c` | `SND_RecvCommandReply` | defines its nine scalars and owns `.bss` 0x020CC080-0x020CC0A4 |
| `fs/unit_0200C890.c` | `FS_StartOverlay` | `SDK_OVERLAY_DIGEST` and `SDK_OVERLAY_DIGEST_END` defined by the link, both 0x020CBBFC (an empty digest table) |
| `snd/unit_02039248.c` | `NNS_SndArcLoadWaveArcTable` | a function `static` (`data_020ddac8$157`, local) owns `.bss` 0x020DDAC8-0x020DDB04 |
| `gfd/unit_0203C044.c` | `GfxQueue_Configure` | defines the 0x14-byte queue `data_020dea60` (`= {0}`) and owns `.bss` 0x020DEA60-0x020DEA74 |
| `dgt/unit_0200D630.c` | `DGTi_Hash2ProcessBlock` | hand-written ARM (khdays asm); the 0x14 bytes of constants before it are an `asm` block of `dcd` words first in the file |

One has no source and stays delinked from the original:

| Unit | Function | Why |
|---|---|---|
| `ctrdg/unit_02019368.c` | `CTRDGi_InitModuleInfo` | matches (100 %) only with a function `static` at 0x020D4CC0, but `CTRDG_Init`, `CTRDGi_PulledOutCallback` and `func_020195f8` use that address too: dsd rejects a relocation to a local symbol from another unit, and a link-defined global is not seen by `check symbols` |

Symbols changed for these units: `_ll_udiv` (0x02025D20, which also holds
`_ull_mod` at 0x02025D2C) and `_u32_div_f` (0x02025F94) are the entries that mwccarm
calls for 64-bit and unsigned division; `func_02025b70` became a function (the
matrix code calls it at 0x020022F0) and `func_02025b60` is a separate 0x10-byte
entry that saves the same registers, sets r4 = r1 | 1 and branches into its body.

### Not assigned yet

- Library functions between the library units (no hit: not compiled by a reference,
  asm, or changed), main 0x02019B80-0x0201AD84 and 0x02026704-0x0202A1D8, and
  the WiFi sub-libraries (SOC, CPS, SSL, WCM) inside 0x02084880-0x020B32E0.
- Bounds between game units: found unit by unit (`/decomp-unit`).
- `.rodata`, `.data` and `.bss` owners: per unit.

## Units

| Unit | Range | Content | Bounds evidence | Status |
|---|---|---|---|---|
| `src/main/unit_02040BD8.cpp` | `.text` 0x02040BD8-0x02041090 | brightness fades of the two 2D engines (`include/game/unk_fade.h`), 26 functions | hypothesis: every reference to the object at 0x020DEF68 comes from this range; neighbours use other data. Its `.bss` (0x020DEF68-0x020DEF94) is left out, owner of 0x020DEF94-0x020DEFEC unknown | complete (2026-11-09) |
| `src/ov005/unit_021CD658.cpp` | `.text` 0x021CD658-0x021CD7A0, `.data` 0x021CE878-0x021CE88C | wrappers of main-module services, object at 0x021CE990 loaded from `"world.e"` / `"world.ez%c"`, 9 functions | hypothesis: the objects at 0x021CE98C and 0x021CE990 are used only here; neighbours use 0x021CE95C and 0x021CE88C; the two strings are used only here, in order. `.bss` left out | not complete: `func_ov005_021cd6ec` 96.12 % (gap in the comment above it) |
