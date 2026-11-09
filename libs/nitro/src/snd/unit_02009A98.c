/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();

extern void OS_RestoreInterrupts(int mask);

extern int *data_020cc080[];

int func_02009a98(void) {
    int mask;
    int count;
    int *p;
    mask = OS_DisableInterrupts();
    count = 0;
    p = data_020cc080[2];
    if (p != 0) {
        do {
            p = (int *)*p;
            count++;
        } while (p != 0);
    }
    OS_RestoreInterrupts(mask);
    return count;
}
