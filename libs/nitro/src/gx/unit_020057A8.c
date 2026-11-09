/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_WaitDma(int ch);

extern void GX_SetBankForTexPltt(int mask);

extern int data_020c5ca4[];

extern int data_020cbc3c[];

void GX_EndLoadTexPltt(void) {
    if (data_020c5ca4[0] != -1) {
        MI_WaitDma(data_020c5ca4[0]);
    }
    GX_SetBankForTexPltt(data_020cbc3c[3]);
    data_020cbc3c[3] = 0;
    data_020cbc3c[2] = 0;
}
