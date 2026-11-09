/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_EnableInterrupts(void);

extern void OS_Halt(void);

void OSi_IdleThreadProc(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
