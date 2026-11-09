/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int FSi_SendCommand(char *file, int flags);

int FS_OpenFileDirect(char *file, void *arc, unsigned int top, unsigned int bottom, unsigned int id) {
    *(void **)(file + 8) = arc;
    *(unsigned int *)(file + 0x38) = id;
    *(unsigned int *)(file + 0x30) = top;
    *(unsigned int *)(file + 0x34) = bottom;
    if (FSi_SendCommand(file, 7) == 0) {
        return 0;
    }
    *(int *)(file + 0xc) = (*(int *)(file + 0xc) | 0x10) & ~0x20;
    return 1;
}
