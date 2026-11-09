/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

unsigned FX_GetSqrtResult(void) {
    while (*(volatile unsigned short *)0x040002b0 & 0x8000) {
    }
    return (*(volatile unsigned *)0x040002b4 + 0x200) >> 10;
}
