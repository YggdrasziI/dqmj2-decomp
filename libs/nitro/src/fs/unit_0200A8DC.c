/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *FSi_TranslateCommand();

void *FSi_SeekDirDirect(char *file, unsigned short id) {
    *(int *)(file + 0xc) |= 4;
    *(int *)(file + 0x30) = *(int *)(file + 8);
    *(int *)(file + 0x38) = 0;
    *(unsigned short *)(file + 0x36) = 0;
    *(unsigned short *)(file + 0x34) = id;
    return FSi_TranslateCommand(file, 2);
}
