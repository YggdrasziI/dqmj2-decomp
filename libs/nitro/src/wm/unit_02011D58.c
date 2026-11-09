/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void MI_CpuFill8(void *dst, int value, int size);

extern void OS_GetMacAddress(void *dst);

extern int func_020117d0(void);

extern char *func_020117c0(void);

extern unsigned short func_02011ce4(void);

extern int func_02011cb4(void);

int func_02011d58(unsigned short port, void (*callback)(void *), void *arg) {
    char event[0x44];
    char *state;
    int enabled;
    int err;
    if (callback != 0) {
        MI_CpuFill8(event, 0, 0x44);
        *(short *)event = 0x82;
        *(short *)(event + 2) = 0;
        *(short *)(event + 4) = 0x19;
        *(short *)(event + 6) = (short)port;
        *(int *)(event + 8) = 0;
        *(int *)(event + 0xc) = 0;
        *(short *)(event + 0x10) = 0;
        *(unsigned short *)(event + 0x1a) = 0xffff;
        *(void **)(event + 0x1c) = arg;
        *(short *)(event + 0x12) = 0;
        OS_GetMacAddress(event + 0x14);
    }
    enabled = OS_DisableInterrupts();
    err = func_020117d0();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    state = func_020117c0() + port * 4;
    *(void **)(state + 0xcc) = (void *)callback;
    *(void **)(state + 0x10c) = arg;
    if (callback != 0) {
        *(short *)(event + 0x22) = (short)func_02011ce4();
        *(short *)(event + 0x20) = (short)func_02011cb4();
        callback(event);
    }
    OS_RestoreInterrupts(enabled);
    return 0;
}
