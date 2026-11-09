/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_Terminate(void);

extern void CTRDG_TerminateForPulledOut(void);

extern int data_020d4cc0[];

void CTRDGi_PulledOutCallback(int param_1, unsigned param_2) {
    if ((param_2 & 0x3f) == 0x11) {
        int result;
        int (*fn)(void);
        if (data_020d4cc0[3] != 0) return;
        result = 0;
        fn = (int (*)(void))data_020d4cc0[6];
        if (fn != 0) result = fn();
        if (result != 0) CTRDG_TerminateForPulledOut();
        data_020d4cc0[3] = 1;
    } else {
        OS_Terminate();
    }
}
