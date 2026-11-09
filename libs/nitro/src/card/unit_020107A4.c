/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int *data_020cde00;

int CARD_GetBackupSectorSize(void) {
    return *(int *)((char *)data_020cde00 + 0x1c);
}
