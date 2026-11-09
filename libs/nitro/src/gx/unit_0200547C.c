/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);

extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);

extern int data_020c5ca4[];

void GXS_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020c5ca4[0] != -1) {
        MI_DmaCopy32Async(data_020c5ca4[0], src, (void *)(offset + 0x8a0000 + 0x6000000), len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x8a0000 + 0x6000000), len);
}
