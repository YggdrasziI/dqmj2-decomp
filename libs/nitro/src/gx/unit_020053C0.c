/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);

extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);

extern int data_020c5ca4[];

extern void MI_WaitDma(int ch);

extern void GX_SetBankForSubBGExtPltt(int mask);

extern int data_020cbc20[];

void GXS_LoadBGExtPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020c5ca4[0] != -1) {
        MI_DmaCopy32Async(data_020c5ca4[0], src, (void *)(offset + 0x98000 + 0x6800000), len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x98000 + 0x6800000), len);
}

void GXS_EndLoadBGExtPltt(void) {
    if (data_020c5ca4[0] != -1) {
        MI_WaitDma(data_020c5ca4[0]);
    }
    GX_SetBankForSubBGExtPltt(data_020cbc20[0]);
    data_020cbc20[0] = 0;
}
