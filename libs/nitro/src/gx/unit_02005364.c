/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_WaitDma(int ch);

extern void GX_SetBankForOBJExtPltt(int mask);

extern int data_020c5ca4[];

extern int data_020cbc20[];

void GX_EndLoadOBJExtPltt(void) {
    if (data_020c5ca4[0] != -1) {
        MI_WaitDma(data_020c5ca4[0]);
    }
    GX_SetBankForOBJExtPltt(data_020cbc20[2]);
    data_020cbc20[2] = 0;
    data_020cbc20[1] = 0;
}
