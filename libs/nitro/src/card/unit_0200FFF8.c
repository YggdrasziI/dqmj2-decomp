/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int func_0200ffe8(void);

extern void OS_Terminate(void);

void CARD_CheckEnabled(void) {
    if (func_0200ffe8() == 0) {
        OS_Terminate();
    }
}
