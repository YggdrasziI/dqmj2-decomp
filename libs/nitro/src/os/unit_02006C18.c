/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *OS_WakeupThreadDirect();

void *OSi_SleepAlarmCallback(char **slot) {
    char *thread = *slot;
    *slot = 0;
    *(int *)(thread + 0xb0) = 0;
    return OS_WakeupThreadDirect(thread);
}
