/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OSi_RescheduleThread(void);

void OS_WakeupThreadDirect(char *thread) {
    int enabled = OS_DisableInterrupts();
    *(int *)(thread + 0x64) = 1;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(enabled);
}
