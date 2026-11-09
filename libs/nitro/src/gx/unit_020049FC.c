/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_DmaCopy32(int ch, const void *src, void *dst, unsigned int len);

extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);

extern int data_020c5ca4[];

void GX_LoadOAM(const void *src, unsigned int offset, unsigned int len) {
    if (data_020c5ca4[0] != -1 && len > 0x30) {
        MI_DmaCopy32(data_020c5ca4[0], src, (void *)(offset + 0x7000000), len);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x7000000), len);
}
