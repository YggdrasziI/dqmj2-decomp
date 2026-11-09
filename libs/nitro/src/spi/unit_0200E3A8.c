/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020cdcd0;

int TP_CheckError(int arg0) {
    return *(unsigned short *)((char *)&data_020cdcd0 + 0x38) & arg0;
}
