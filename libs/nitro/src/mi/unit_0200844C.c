/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void MI_SetWramBank(unsigned char bank) {
    *(volatile unsigned char *)0x04000247 = bank;
}
