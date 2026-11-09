/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern int func_02006ddc(void);

int IsCommandAvailable(void) {
    volatile unsigned int *reg = (volatile unsigned int *)0x04fff200;
    int enabled;
    unsigned int busy;
    if (func_02006ddc() == 0) {
        return 1;
    }
    enabled = OS_DisableInterrupts();
    *reg = 0x10;
    busy = *reg;
    OS_RestoreInterrupts(enabled);
    return busy != 0;
}
