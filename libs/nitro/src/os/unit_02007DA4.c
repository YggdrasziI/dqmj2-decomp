/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_Terminate(void);

extern long long OS_GetTick(void);

extern void OSi_InsertAlarm(void *alarm, long long fire);

void OS_SetAlarm(char *alarm, long long delay, void *handler, void *arg) {
    int enabled;
    if (alarm == 0 || *(int *)alarm != 0) {
        OS_Terminate();
    }
    enabled = OS_DisableInterrupts();
    *(int *)(alarm + 0x1c) = 0;
    *(int *)(alarm + 0x20) = 0;
    *(void **)alarm = handler;
    *(void **)(alarm + 4) = arg;
    OSi_InsertAlarm(alarm, delay + OS_GetTick());
    OS_RestoreInterrupts(enabled);
}
