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

All overlays share one load address, so only one is resident at a time. The role of
each overlay (battle, field, menus...) is not known.

## Region map

To do (Step 4): crt0 and NitroSDK, NitroSystem, WiFi / DWC / SSL, MSL and runtime,
game code, per module.

First clues (2026-11-09, hypotheses):

- Main: library functions found by `tools/compiler_sweep.py` all lie in
  0x02000950-0x0203C0C8 (NitroSDK, MSL 0x0201AD84-0x020266D8, NitroSystem
  0x0202A1D8-0x0203C044; `notes/COMPILER.md`); ARM game code follows up to
  0x02084870; then Thumb code 0x02084880-0x020B3280 (WiFi / DWC / SSL?) and ARM
  0x020B4AF8-0x020BCB7C.
- ov004: ARM 0x021CB360-0x021E1154, Thumb 0x021E116C-0x021FA014, ARM
  0x021FA028-0x021FD484. The other overlays are all ARM.

## Units

None yet.
