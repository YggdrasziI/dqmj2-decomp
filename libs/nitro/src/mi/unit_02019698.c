/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_CpuFill8(void *dest, unsigned char val, unsigned int size);

void MIi_CpuFill24(void *dest)
{
    MI_CpuFill8(dest, 0, 0x24);
}
