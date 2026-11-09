/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *GX_VRAMCNT_SetLCDC_();

extern unsigned short data_020cbc04;

void *GX_SetBankForLCDC(int bank) {
    data_020cbc04 = (unsigned short)(data_020cbc04 | bank);
    return GX_VRAMCNT_SetLCDC_(bank);
}
