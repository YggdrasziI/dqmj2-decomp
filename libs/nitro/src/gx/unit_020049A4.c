/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_DmaCopy16(int ch, const void *src, void *dst, unsigned int len);

extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int len);

extern int data_020c5ca4[];

void GXS_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020c5ca4[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020c5ca4[0], src, (void *)(offset + 0x600 + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x600 + 0x5000000), len);
}
