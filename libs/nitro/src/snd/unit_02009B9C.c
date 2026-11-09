/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();

extern void OS_RestoreInterrupts(int mask);

extern int *data_020cc080[];

int *SND_PopFreeCommand(void) {
    int mask;
    int *h;
    int *n;
    mask = OS_DisableInterrupts();
    h = data_020cc080[0];
    if (h == 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    n = (int *)*h;
    data_020cc080[0] = n;
    if (n == 0) data_020cc080[4] = 0;
    OS_RestoreInterrupts(mask);
    return h;
}
