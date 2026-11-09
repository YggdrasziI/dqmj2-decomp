# Provenance of reused code

Every file or function taken from another project, with the project, its commit
(`git -C <clone> rev-parse HEAD`), its license (or its absence and the owner's
approval, see `notes/REFERENCES.md`) and the changes made.

## Build system and scripts (`tools/`)

Source: `E:\Projets\Dev\ts2-castaway` (sibling project, same owner), commit
`1984fd46992d809b66cf83f64c134900d19b1806`, copied on 2026-11-08. Its build files
come from [Yotona/twewy](https://github.com/Yotona/twewy) (**CC0-1.0**; ts2-castaway
took them at twewy commit `0026d7347107415cbfbf2cd218f5859ae00b69a7`, see its own
`notes/PROVENANCE.md`); its other scripts are the owner's.

| Our file | Changes |
|---|---|
| `tools/configure.py` | `GAME = "dqmj2"`, versions `jpn` (default) and `eur` (disabled); game flags without ts2's `-avoid_byte strb`; `COMPILER_CONFIGS` empty |
| `tools/lcf_keep.py` | ts2's NitroSDK absolute symbols removed (`ABSOLUTE_SYMBOLS` empty) |
| `tools/progress_badges.py` | title; `REGIONS` empty until the region map exists |
| `tools/download_tool.py`, `get_platform.py`, `ninja_syntax.py`, `transform_dep.py`, `m2ctx.py`, `mangle.py`, `sha1.py`, `objdiff_prune.py`, `requirements.txt` | none |
| `tools/report_diff.py`, `asm_compare.py`, `compiler_sweep.py`, `unit_candidates.py`, `ghidra_sync.py`, `gdb_trace.py`, `decl_search.py`, `why_diff.py`, `mwcc_blocks.py`, `mwcc_irdump.py`, `mwcc_sched.py`, `permute.py`, `rewrite_sweep.py` | default version `jpn`, paths `build/jpn`, `config/jpn`, `extract/jpn`, `REGION_JPN`; Ghidra project path and name; no `-avoid_byte strb` in the copied flags. Not yet checked on overlays |

Downloaded binaries (`dsd.exe` 0.12.1, `objdiff-cli.exe` 3.8.1, `tools/mwccarm/`) were
copied from ts2-castaway's local copies, same versions as `configure.py` downloads.

## Project documents

`SPEC.md`, `notes/`, `.vscode/tasks.json`, `.github/workflows/build.yml`,
`.gitignore`, `.gitattributes` and `LICENSE` (CC0-1.0) follow ts2-castaway (same
commit), rewritten for this ROM.

## Library and game code

Library sources `libs/{nitro,nns,msl}/src/**/unit_*.c` (2026-11-09, written by
`tools/lib_unit_gen.py`): khdays-decomp (CC0, commit
`93535afd7ca082f3d856bbf1cadae65be16d44ba`) per-function sources of
`libs/{msl,nitro,nns}`, and twewy (CC0, commit
`3f916f1a2d31f29bd7ec6fd89f3a87b696e79b9b`) `libs/nitro/src` where khdays has no
match, merged per unit: declarations written once, functions of other units turned
into declarations, variable definitions into `extern` declarations, `static`
removed from the unit's functions, the reference's names of callees, data and the
unit's own functions replaced by this ROM's (read from the relocations). Each
file's header names its references.

Headers `libs/nitro/include/{nitro,nnsys}/*.h`: khdays-decomp (CC0, same commit)
`include/{nitro,nnsys}`, copied unchanged.


Library function names (`config/jpn/arm9/symbols.txt`, `itcm/symbols.txt`, written
by `tools/sweep_names.py` on 2026-11-09): names of functions compiled from
[Yokimitsuro/khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp) (CC0, local
clone at `93535afd7ca082f3d856bbf1cadae65be16d44ba`) `libs/{msl,nitro,nns}` and
[Yotona/twewy](https://github.com/Yotona/twewy) (CC0, local clone at
`3f916f1a2d31f29bd7ec6fd89f3a87b696e79b9b`) `libs/nitro/src` that are byte-identical
to this ROM's functions; names only, no code. The folder of each library unit
(`libs/<lib>/src/<folder>/`) is the reference's folder.
