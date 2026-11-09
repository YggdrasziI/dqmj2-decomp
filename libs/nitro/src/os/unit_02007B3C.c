/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

int OS_GetTickLo(void) {
    return *(volatile unsigned short *)0x04000100;
}
