# Progress

Milestones, newest last. Figures come from `build/jpn/report.json`.

| Date | Milestone | Code linked | Functions matched |
|---|---|---|---|
| 2026-11-08 | Step 1: all-assembly build, `dqmj2_jpn.nds: OK` (main, ITCM, DTCM, ov000-ov005; 1745356 bytes of code, 13291 functions) | 0 % | 0 / 13291 |
| 2026-11-09 | First complete game unit, `unit_02040BD8.cpp` (brightness fades, 1208 bytes); compiler family identified (2.0, libraries sp2p2 or later) | 0.07 % | 26 / 13291 |
| 2026-11-09 | 589 library units `complete` (NitroSDK, MSL, NitroSystem, from khdays-decomp and twewy sources, `tools/lib_unit_gen.py`) | 5.37 % | 812 / 13291 |
| 2026-11-09 | 649 library units `complete` (relocation fixes, edited drafts, twewy headers); 9 left without a source | 6.23 % | 873 / 13292 |
| 2026-11-09 | 655 library units `complete` (link-defined SDK values, units owning their `.bss`); 3 left without a source | 6.30 % | 879 / 13292 |
| 2026-11-09 | 657 library units `complete` (GFX queue data, SHA-1 constants as asm data); `CTRDGi_InitModuleInfo` left | 6.34 % | 881 / 13292 |
| 2026-11-09 | Second complete game unit, `unit_02041090.cpp` (model resource tables, 15 functions, 1468 bytes, its `.data` and `.bss`) | 6.42 % | 896 / 13292 |
