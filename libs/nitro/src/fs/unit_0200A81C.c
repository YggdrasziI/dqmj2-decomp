/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_SleepThread(void *queue);

static inline int FSi_IsTableBusy(char *arc) {
    return (*(volatile int *)(arc + 0x1c) & 0x200) != 0;
}

int FSi_ReadTable(char *ctx, void *dst, int len) {
    char *arc = *(char **)ctx;
    int r;
    int enabled;
    *(volatile int *)(arc + 0x1c) |= 0x200;
    r = (*(int (**)(void *, void *, void *, int))(arc + 0x50))(
            arc, dst, *(void **)(ctx + 4), len);
    switch (r) {
    case 0:
    case 1:
        *(volatile int *)(arc + 0x1c) &= ~0x200;
        break;
    case 6: {
        enabled = OS_DisableInterrupts();
        while (FSi_IsTableBusy(arc)) {
            OS_SleepThread(arc + 0xc);
        }
        OS_RestoreInterrupts(enabled);
        r = *(int *)(*(char **)(arc + 0x24) + 0x14);
        break;
    }
    }
    *(int *)(ctx + 4) = *(int *)(ctx + 4) + len;
    return r;
}
