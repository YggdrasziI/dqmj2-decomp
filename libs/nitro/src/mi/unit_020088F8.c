/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void MIi_CheckDma0SourceAddress(unsigned int channel, void *src, int count, int flag);

extern void MI_WaitDma(unsigned int channel);

extern void *OS_GetIrqFunction(unsigned int mask);

extern void OS_SetIrqFunction(unsigned int mask, void *fn);

extern void OS_EnableIrqMask(unsigned int mask);

extern void MIi_FIFOCallback(void);

extern char data_020cc040;

void MI_SendGXCommandAsync(unsigned int channel, void *src, int count,
                           void (*callback)(void *), void *arg) {
    int enabled;
    if (count == 0) {
        if (callback == 0) {
            return;
        }
        callback(arg);
        return;
    }
    while (*(volatile int *)&data_020cc040 != 0) {
    }
    while ((((*(volatile unsigned int *)0x04000600 & 0x7000000) >> 0x18) & 2) == 0) {
    }
    *(volatile int *)&data_020cc040 = 1;
    *(unsigned int *)((char *)&data_020cc040 + 4) = channel;
    *(void **)((char *)&data_020cc040 + 8) = src;
    *(int *)((char *)&data_020cc040 + 0xc) = count;
    *(void **)((char *)&data_020cc040 + 0x10) = (void *)callback;
    *(void **)((char *)&data_020cc040 + 0x14) = arg;
    MIi_CheckDma0SourceAddress(channel, src, count, 0);
    MI_WaitDma(channel);
    enabled = OS_DisableInterrupts();
    *(unsigned int *)((char *)&data_020cc040 + 0x18) = (*(volatile unsigned int *)0x04000600 & 0xc0000000) >> 0x1e;
    *(void **)((char *)&data_020cc040 + 0x1c) = OS_GetIrqFunction(0x200000);
    *(volatile int *)0x04000600 = (*(volatile int *)0x04000600 & ~0xc0000000) | 0x40000000;
    OS_SetIrqFunction(0x200000, (void *)&MIi_FIFOCallback);
    OS_EnableIrqMask(0x200000);
    MIi_FIFOCallback();
    OS_RestoreInterrupts(enabled);
}
