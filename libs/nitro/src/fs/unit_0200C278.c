/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int CARDi_ReadRom(int a, int b, int c, int d, int e, int f, int g);

extern int FSi_OnRomReadDone();

extern int *data_020cdc5c[];

int FSi_ReadRomCallback(int a, int b, int c, int d) {
    CARDi_ReadRom((int)data_020cdc5c[1], c, b, d, (int)FSi_OnRomReadDone, a, 1);
    return 6;
}
