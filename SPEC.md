# Dragon Quest Monsters: Joker 2 (DS) decompilation — specification

## Goal

Rebuild Dragon Quest Monsters: Joker 2 (Nintendo DS, Japan) from C/C++ source written
from scratch so that, compiled with the original compiler and flags, it produces ARM9
modules (main, ITCM, DTCM, overlays 0-5) identical byte for byte to the original, and
so the original ROM.

Out of scope: a port, game assets, any redistribution of game files, the ARM7 binary
(standard SDK component, rebuilt from the extracted binary as is).

## Target ROM

| Item | Value | Evidence |
|---|---|---|
| Game code | `CJRJ` (Japan), maker `GD` (Square Enix) | ROM header 0x0C, 0x10 (`extract/jpn/header.yaml`) |
| Internal title | `DQM-JOKER2` | ROM header 0x00 |
| Revision | 0 | ROM header 0x1E |
| ROM SHA-1 | `fa7da80d6ba30d1cdaa43a157a5851a97f9e97ea` (128 MiB) | `config/jpn/build.sha1` |
| ARM9 main | load 0x02000000, entry 0x02000800, 0x88A6C bytes in the ROM, compressed | ROM header 0x20-0x2C, `extract/jpn/arm9/arm9.yaml` |
| ARM9 sections | `.text` 0x02000000-0x020BCE10, `.rodata` -0x020C5C9C, `.ctor` empty, `.data` 0x020C5CA0-0x020CBC00, `.bss` 0x020CBC00-0x021CB360 | `config/jpn/arm9/delinks.txt` (dsd analysis) |
| ITCM | 0x01FF8000, `.text` -0x01FFF72C, `.bss` 0x01FFF740-0x01FFF980 | `config/jpn/arm9/itcm/delinks.txt` |
| DTCM | 0x027E0000, 0x60 bytes data + 0x20 bss | `config/jpn/arm9/dtcm/delinks.txt` |
| ARM9 overlays | 6, all loaded at 0x021CB360 (one at a time), compressed; overlay 2 is protected by "DS Protect" (dsd decrypts it on extract, `enable_dsprot: true`) | `extract/jpn/arm9_overlays/overlays.yaml`, `config/jpn/arm9/config.yaml` |
| ARM7 | 0x27130 bytes, no overlays | ROM header 0x3C, 0x5C |
| NitroSDK | version word `0x04027539` (major 4, minor 2, relstep 30009) | `extract/jpn/arm9/arm9.yaml`, `sdk_version` |
| Other SDK markers | `[SDK+NINTENDO:BACKUP]` 0x02000B8C, `[SDK+UBIQUITOUS:CPS]` 0x02000BA4, `[SDK+NINTENDO:WiFi2.1.30003.0709200229]` 0x02000BBC, `[SDK+UBIQUITOUS:SSL]` 0x02000BE4, `[SDK+NINTENDO:DWC3.1.30006.20090131.2222_DWC_3_1_PLUS6]` 0x02000BFC | strings in `extract/jpn/arm9/arm9.bin` |
| Code size | 1745356 bytes, 13291 functions over all modules (dsd analysis) | `build/jpn/report.json` |
| Build date | unknown (the DWC marker is dated 2009-01-31, which bounds the build from below only) | — |

Overlays (dsd analysis, `config/jpn/arm9/overlays/ov<NNN>/delinks.txt`):

| Overlay | `.text` end | `.bss` end | Functions |
|---|---|---|---|
| ov000 | 0x02223D44 | 0x02240BA0 | 2073 |
| ov001 | 0x0221549C | 0x02231960 | 1994 |
| ov002 | 0x021CD2DC | 0x021CD340 | 59 (DS Protect) |
| ov003 | 0x021D81C0 | 0x021DF040 | 251 |
| ov004 | 0x021FD4DC | 0x0220CCC0 | 2805 |
| ov005 | 0x021CE09C | 0x021CF260 | 98 |

Main module: 5859 functions; ITCM: 151 (counts of `kind:function` in `symbols.txt`).

Game files: 3793 files in the NitroFS root (game tables such as `AbilityTbl.bin`,
`.chr` / `.pal` / `.scrn` 2D data, `.nsbmd` / `.nsbtx` NitroSystem 3D data, and a
`dwc/` folder). Their roles are not analysed.

## Other versions

The project knows two versions; only `jpn` is enabled. `eur` stays in
`DISABLED_VERSIONS` (`tools/configure.py`, which refuses it) until the owner decides
to support it.

| Name | Release | Game code / maker | ROM SHA-1 | Difference from `jpn` | Status |
|---|---|---|---|---|---|
| `jpn` | Dragon Quest Monsters: Joker 2 (Japan) | `CJRJ` / `GD` | `fa7da80d…` | — | enabled, reference version |
| `eur` | Dragon Quest Monsters: Joker 2 (Europe) | `CJRP` / `01` | `513ac63c7d67211007da6ba7050b179dfafb362a` | separate build: ARM9 main 0x89F40 bytes in the ROM (0x14D4 more), title `DQM:JOKER2`; 6 ARM9 overlays too | disabled |

The `eur` ROM has not been extracted or analysed (`dsd init` not run). DQMJ2
Professional is a separate game (own ROM, `DQMJ2P-decomp` folder), not a version of
this project.

Model (after `Yotona/twewy`, as in ts2-castaway):

- `tools/configure.py`: `VERSIONS` and `DISABLED_VERSIONS`; the compiler gets
  `REGION_<NAME>` (`REGION_JPN`, `REGION_EUR`) for `#if` in the shared sources, used
  only where a version differs.
- Per version: `extract/baserom_dqmj2_<name>.nds`, `config/<name>/` (only
  `build.sha1` while disabled; `arm9/` from `dsd init` once enabled),
  `progress/<name>/`, a CI matrix entry and its ROM in the build image.
- The scripts in `tools/` take `--version` (default `jpn`).

## Toolchain

Evidence and the candidate analysis go in `notes/COMPILER.md`.

- ds-decomp (`dsd`) **v0.12.1**: extract, analysis (`dsd init`), delink, linker script,
  ROM rebuild (overlay compression, DS Protect re-encryption), checks, objdiff config.
- objdiff-cli **v3.8.1** (report, diff with the unarm disassembler), objdiff GUI.
- mwccarm / mwldarm from `decomp.aetias.com/files/mwccarm.zip` (1.2, 2.0 and DSi
  families in `tools/mwccarm/`). **Compiler not identified**: `configure.py` uses
  2.0/sp1p5 with twewy's flags (without `-ipa file`) as a provisional choice. The
  all-assembly build does not depend on it.
- Linker flags: `-proc arm946e -interworking -dead -nostdlib -m Entry`, as in
  ts2-castaway. The all-assembly build links with them; whether the original link
  stripped dead code is not known yet (`notes/COMPILER.md`).
- Optional: Ghidra 11.2.1 with the dsd-ghidra v0.7.0 extension, outside the repository
  (`tools/ghidra_sync.py` pushes the dsd symbols to a Ghidra project).

## Acceptance criteria

- Every build ends with `build\jpn\dqmj2_jpn.nds: OK` (`ninja`), after `dsd check
  modules` (main, ITCM, DTCM, overlays 0-5 OK) and `dsd check symbols`.
- The ROM check uses `config/jpn/build.sha1` (the original ROM) when `arm7_bios.bin`
  is in the project root, and `config/jpn/build_nobios.sha1` otherwise. Without the
  BIOS, dsd cannot encrypt the secure area, so exactly four bytes differ from the
  original: the secure area CRC (0x6C-0x6D) and the header CRC (0x15E-0x15F); every
  other byte is identical (checked 2026-11-08 with `cmp`). With the owner's ARM7 BIOS
  dump the rebuilt ROM is identical to the original (checked 2026-11-08). BIOS dumps
  are never versioned or pushed anywhere.
- A file in `delinks.txt` is `complete` only when objdiff reports 100 % for all its
  functions and data and the build still matches. Anything else stays not
  `complete`, with the remaining gap written above each unfinished function.
- A delink that builds proves the bytes, not the translation unit: a TU boundary is
  proven only once the unit is decompiled and matches (`notes/SPLITS.md`).
- Every name, compiler fact or structure layout rests on evidence (strings with their
  offset, library signatures, symbols of another project on the same library, an
  objdiff diff, a build result). Without evidence it is labelled a hypothesis. Names
  given in Ghidra, or found in another Dragon Quest decompilation, are not evidence by
  themselves.
- Reused code from another project is logged with its commit and license in
  `notes/PROVENANCE.md`.

## Naming conventions

- dsd default names stay until proven: `func_<addr>`, `data_<addr>`; in overlays,
  dsd's own names (`func_ov<NNN>_<addr>`, `data_ov<NNN>_<addr>`).
- Game units: `src/main/unit_<start address>.cpp` for the main module and
  `src/ov<NNN>/unit_<start address>.cpp` for overlays, while real file names are
  unknown; the unit table with bounds and contents is in `notes/SPLITS.md`.
- Unknown classes and structs: `Unk<Name>` or `Unk<address>`; unknown methods keep
  the address (`func_<addr>`, mangled as a member when the unit is C++).
- SDK and library code under `libs/<lib>/{include,src}` with the real names of the
  library once identified by signature or reference project (naming policy of
  ts2-castaway: khdays-decomp's NitroSDK / NitroSystem API names first, then twewy's,
  for functions found byte-identical by `tools/compiler_sweep.py`).
- Code, comments, notes and commit messages are in English.

## Layout

```
README.md SPEC.md LICENSE
config/jpn/               build.sha1, build_nobios.sha1, arm9/ (dsd configs:
                          config.yaml, delinks.txt, symbols.txt, relocs.txt;
                          itcm/, dtcm/, overlays/ov000 ... ov005/)
config/eur/               build.sha1 only (disabled version)
extract/                  baserom_dqmj2_<name>.nds and dsd extraction (git-ignored)
build/                    build output (git-ignored)
src/  include/  libs/     sources and headers (game, SDK, MSL), when added
tools/                    configure.py and scripts
progress/jpn/             progress badges and history
notes/                    reference documentation
.github/workflows/        CI (prepared, inactive until a repository exists)
```

## Build

```
pip install -r tools/requirements.txt
python tools/configure.py # generate build.ninja (first run: then `ninja` downloads the tools)
ninja                     # delink, compile, link, check modules and symbols, rebuild
                          # the ROM, check its SHA-1, write build/jpn/report.json
```

Put the ROM at `extract/baserom_dqmj2_jpn.nds`. Useful targets: `ninja objdiff`
(objdiff.json for the GUI), `ninja report`, `ninja dis` (disassembly in
`build/jpn/asm/`), `ninja apply` (names from the built ELF back into `symbols.txt`).
On Windows use native tools, not WSL.
