/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void CARDi_PulledOutCallback(int a, int b, int c);

void CARDi_CheckPulledOutCore(int id) {
    volatile int stored;
    int enabled;
    int *src;
    if (*(unsigned short *)0x027ffc10 == 0) {
        src = (int *)0x027ff800;
    } else {
        src = (int *)0x027ffc00;
    }
    stored = *src;
    if (id != stored) {
        enabled = OS_DisableInterrupts();
        CARDi_PulledOutCallback(0xe, 0x11, 0);
        OS_RestoreInterrupts(enabled);
    }
}
