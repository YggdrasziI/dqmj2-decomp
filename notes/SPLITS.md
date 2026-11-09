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

## Units

None yet.
