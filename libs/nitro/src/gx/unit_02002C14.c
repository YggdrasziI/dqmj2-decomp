/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern unsigned short data_020c5ca0;

extern unsigned short data_020cbc00;

void GX_DispOff(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    unsigned int disp = *reg_dispcnt;
    data_020c5ca0 = 0;
    data_020cbc00 = (unsigned short)((disp & 0x30000) >> 0x10);
    *reg_dispcnt = disp & ~0x30000u;
}
