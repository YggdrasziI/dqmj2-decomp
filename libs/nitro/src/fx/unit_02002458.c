/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void FX_DivAsync(int numer, int denom) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    div[4] = 0;
    div[5] = (unsigned)numer;
    div[6] = (unsigned)denom;
    div[7] = 0;
}
