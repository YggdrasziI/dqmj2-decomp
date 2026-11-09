/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_SleepThread(void *queue);

extern char data_020cde00;

int CARDi_WaitAsync(void) {
    char *card = (char *)&data_020cde00;
    int enabled = OS_DisableInterrupts();
    goto test;
loop:
    OS_SleepThread(card + 0x10c);
test:
    if ((*(volatile int *)(card + 0x114) & 4) != 0) {
        goto loop;
    }
    OS_RestoreInterrupts(enabled);
    return **(int **)card == 0;
}
