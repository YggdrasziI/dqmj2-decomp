/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();

extern void OS_RestoreInterrupts(int mask);

extern int data_020cc080[];

int SND_GetCurrentCommandTag(void) {
    int mask;
    int result;
    mask = OS_DisableInterrupts();
    if (data_020cc080[2] == 0) {
        result = data_020cc080[1];
    } else {
        result = data_020cc080[8];
    }
    OS_RestoreInterrupts(mask);
    return result;
}
