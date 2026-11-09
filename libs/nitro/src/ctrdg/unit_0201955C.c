/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_Terminate(void);

extern unsigned short data_020d4cbc;

void CTRDGi_InitCallback(int unused, int status) {
    if ((status & 0x3f) == 1) {
        data_020d4cbc = 1;
        return;
    }
    OS_Terminate();
}
