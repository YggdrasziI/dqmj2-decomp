/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int FSi_SendCommand(char *file, int flags);

int FS_CloseFile(char *file) {
    if (FSi_SendCommand(file, 8) == 0) {
        return 0;
    }
    *(int *)(file + 8) = 0;
    *(int *)(file + 0x10) = 0xe;
    *(int *)(file + 0xc) &= ~0x30;
    return 1;
}
