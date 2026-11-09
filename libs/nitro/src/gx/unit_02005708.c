/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int func_02003b78(void);

extern int data_020cbc3c[];

extern unsigned short data_020c0f14[];

void GX_BeginLoadTexPltt(void) {
    int mask = func_02003b78();
    data_020cbc3c[3] = mask;
    data_020cbc3c[2] = data_020c0f14[mask >> 4] << 12;
}
