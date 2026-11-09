/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_WaitDma(int ch);

extern void GX_SetBankForBGExtPltt(int mask);

extern int data_020c5ca4[];

extern int data_020cbc20[];

void GX_EndLoadBGExtPltt(void) {
    if (data_020c5ca4[0] != -1) {
        MI_WaitDma(data_020c5ca4[0]);
    }
    GX_SetBankForBGExtPltt(data_020cbc20[5]);
    data_020cbc20[5] = 0;
    data_020cbc20[4] = 0;
    data_020cbc20[3] = 0;
}
