/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_Terminate(void);

extern void CARD_TerminateForPulledOut(void);

extern int data_020ce660;

void CARDi_PulledOutCallback(int arg0, int arg1) {
    if ((arg1 & 0x3f) == 0x11) {
        if (data_020ce660 != 0) return;
        data_020ce660 = 1;
        {
            int (*fn)(void) = *(int (**)(void))((char *)&data_020ce660 + 4);
            int r = 1;
            if (fn != 0) r = fn();
            if (r != 0) CARD_TerminateForPulledOut();
        }
    } else {
        OS_Terminate();
    }
}
