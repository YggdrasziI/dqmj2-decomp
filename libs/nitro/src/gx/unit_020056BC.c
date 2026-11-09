/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void MI_WaitDma(int ch);

extern void GX_SetBankForTex(int mask);

extern int data_020c5ca4[];

extern int data_020cbc3c[];

void GX_EndLoadTex(void) {
    if (data_020c5ca4[0] != -1) {
        MI_WaitDma(data_020c5ca4[0]);
    }
    GX_SetBankForTex(data_020cbc3c[5]);
    data_020cbc3c[7] = 0;
    data_020cbc3c[6] = 0;
    data_020cbc3c[1] = 0;
    data_020cbc3c[5] = 0;
}
