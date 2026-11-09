/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_Terminate(void);

extern unsigned short data_020cc024;

void OSi_CommonCallback(int unused, int status) {
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        data_020cc024 = 1;
        return;
    }
    OS_Terminate();
}
