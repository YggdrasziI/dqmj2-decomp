/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020cdcd0;

int TP_GetLatestIndexInAuto(void) {
    return *(unsigned short *)((int)&data_020cdcd0 + 0x10);
}
