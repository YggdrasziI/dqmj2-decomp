/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern char data_020cdcd0;

void TP_WaitBusy(unsigned int mask) {
    while (*(volatile unsigned short *)(&data_020cdcd0 + 0x3a) & mask) {
    }
}
