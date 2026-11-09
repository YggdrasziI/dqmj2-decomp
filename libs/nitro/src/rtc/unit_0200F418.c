/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int mask);

extern int func_0200fb80(void);

extern int data_020cdd38[];

int RTC_GetTimeAsync(void *time, void *callback, void *arg) {
    int mask;

    mask = OS_DisableInterrupts();
    if (data_020cdd38[3] != 0) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    data_020cdd38[3] = 1;
    OS_RestoreInterrupts(mask);
    data_020cdd38[8] = 1;
    data_020cdd38[9] = 0;
    data_020cdd38[5] = (int)time;
    data_020cdd38[4] = (int)callback;
    data_020cdd38[7] = (int)arg;
    if (func_0200fb80() != 0) {
        return 0;
    }
    return 3;
}
