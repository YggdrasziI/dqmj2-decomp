/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void CARD_LockRom(int lockId);

extern void CARD_UnlockRom(int lockId);

extern int *data_020cdc5c[];

int FSi_RomArchiveProc(void *arc, int command, void *param) {
    switch (command) {
    case 9:
        CARD_LockRom((unsigned short)(int)data_020cdc5c[0]);
        return 0;
    case 10:
        CARD_UnlockRom((unsigned short)(int)data_020cdc5c[0]);
        return 0;
    case 1:
        return 4;
    default:
        return 8;
    }
}
