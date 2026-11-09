/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void MI_WaitDma(unsigned int channel);

extern void OSi_EnterDmaCallback(unsigned int channel, void (*cb)(void *), void *arg);

extern void MIi_DmaSetChannelRegs(unsigned int channel, void *src, void *dest, unsigned int ctrl);

void MI_DmaFill32Async(unsigned int channel, void *dest, unsigned int data, unsigned int size,
                       void (*callback)(void *), void *arg) {
    int enabled;
    if (size == 0) {
        if (callback != 0) {
            callback(arg);
        }
        return;
    }
    MI_WaitDma(channel);
    if (callback != 0) {
        OSi_EnterDmaCallback(channel, callback, arg);
        enabled = OS_DisableInterrupts();
        *(volatile unsigned int *)(0x040000e0 + channel * 4) = data;
        MIi_DmaSetChannelRegs(channel, (void *)(0x040000e0 + channel * 4), dest,
                      (size >> 2) | 0xc5000000);
        OS_RestoreInterrupts(enabled);
    } else {
        enabled = OS_DisableInterrupts();
        *(volatile unsigned int *)(0x040000e0 + channel * 4) = data;
        MIi_DmaSetChannelRegs(channel, (void *)(0x040000e0 + channel * 4), dest,
                      (size >> 2) | 0x85000000);
        OS_RestoreInterrupts(enabled);
    }
}
