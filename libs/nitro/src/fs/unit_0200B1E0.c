/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

int FSi_WriteMemCallback(char **arc, const void *src, unsigned int off, unsigned int len) {
    MI_CpuCopy8(src, arc[10] + off, len);
    return 0;
}
