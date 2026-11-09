/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);

extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);

extern int data_020c5ca4[];

extern char *data_020cbc20[];

void GX_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int len) {
    char *base = data_020cbc20[1];
    if (data_020c5ca4[0] != -1) {
        MI_DmaCopy32Async(data_020c5ca4[0], src, base + offset, len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, base + offset, len);
}
