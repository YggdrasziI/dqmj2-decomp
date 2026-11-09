/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();

extern void OS_RestoreInterrupts(int mask);

extern unsigned int data_020cc080[];

int SND_IsFinishedCommandTag(unsigned int target) {
    int mask;
    int result;
    unsigned int current;
    mask = OS_DisableInterrupts();
    current = data_020cc080[1];
    if (target > current) {
        if ((target - current) < 0x80000000u) {
            result = 0;
        } else {
            result = 1;
        }
    } else {
        if ((current - target) < 0x80000000u) {
            result = 1;
        } else {
            result = 0;
        }
    }
    OS_RestoreInterrupts(mask);
    return result;
}
