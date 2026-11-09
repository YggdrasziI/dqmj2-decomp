/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_SleepThread(void *queue);

extern int FSi_ExecuteSyncCommand(void *file);

static inline int FSi_IsBusy(char *file) {
    return (*(volatile int *)(file + 0xc) & 1) != 0;
}

static inline int FSi_IsSucceeded(char *file) {
    return *(int *)(file + 0x14) == 0;
}

int FS_WaitAsync(char *file) {
    int owner = 0;
    int enabled = OS_DisableInterrupts();
    if (FSi_IsBusy(file)) {
        owner = (*(volatile int *)(file + 0xc) & 0x44) == 0;
        if (owner != 0) {
            *(volatile int *)(file + 0xc) |= 4;
            do {
                OS_SleepThread(file + 0x18);
            } while ((*(volatile int *)(file + 0xc) & 0x40) == 0);
        } else {
            do {
                OS_SleepThread(file + 0x18);
            } while (FSi_IsBusy(file));
        }
    }
    OS_RestoreInterrupts(enabled);
    if (owner != 0) {
        return FSi_ExecuteSyncCommand(file);
    }
    return FSi_IsSucceeded(file);
}
