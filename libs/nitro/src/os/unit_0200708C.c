/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OSi_EnqueueTail(void *thread, void *mutex);

extern void OS_SleepThread(void *queue);

extern char data_020cbce4;

void OS_LockMutex(char *mutex) {
    int enabled = OS_DisableInterrupts();
    char *self = *(char **)((char *)&data_020cbce4 + 4);
    char *none = 0;
    char *owner;
    for (;;) {
        owner = *(char **)(mutex + 8);
        if (owner == 0) {
            *(char **)(mutex + 8) = self;
            *(int *)(mutex + 0xc) = *(int *)(mutex + 0xc) + 1;
            OSi_EnqueueTail(self, mutex);
            break;
        }
        if (owner == self) {
            *(int *)(mutex + 0xc) = *(int *)(mutex + 0xc) + 1;
            break;
        }
        *(char **)(self + 0x84) = mutex;
        OS_SleepThread(mutex);
        *(char **)(self + 0x84) = none;
    }
    OS_RestoreInterrupts(enabled);
}
