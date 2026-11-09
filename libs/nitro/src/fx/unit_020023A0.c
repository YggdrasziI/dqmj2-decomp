/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

long long FX_GetDivResultFx64c(void) {
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    while (*reg_divcnt & 0x8000)
        ;
    return *(long long *)0x040002a0;
}
