/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020cc028[];

extern unsigned short data_020cc02c[];

void OSi_InitVramExclusive(void) {
    int i = 0;
    int z = i;
    data_020cc028[0] = z;
    do {
        data_020cc02c[i] = (unsigned short)z;
        i = i + 1;
    } while (i < 9);
}
