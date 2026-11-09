/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern unsigned short data_020cbc00;

extern short data_020c5ca0;

void DispCnt_ApplyPendingMode(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    unsigned short v;
    data_020c5ca0 = 1;
    v = data_020cbc00;
    if (v != 0) {
        *reg_dispcnt = *reg_dispcnt & 0xfffcffff | (unsigned int)v << 0x10;
        return;
    }
    *reg_dispcnt = *reg_dispcnt | 0x10000;
}
