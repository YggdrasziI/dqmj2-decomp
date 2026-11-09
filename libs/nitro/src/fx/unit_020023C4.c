/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

int FX_GetDivResult(void) {
    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    return (int)((*(volatile long long *)0x040002a0 + 0x80000) >> 20);
}
