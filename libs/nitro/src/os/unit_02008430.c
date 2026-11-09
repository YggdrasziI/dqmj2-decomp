/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_DisableInterrupts(void);

extern void OS_Halt(void);

void OS_Terminate(void) {
    for (;;) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
