/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void FS_InitFile(void *file);

extern void *FSi_FindPath(void *file, const char *path, void *idOut, int dir);

int FS_ConvertPathToFileID(void *idOut, const char *path) {
    char file[0x48];
    FS_InitFile(file);
    return FSi_FindPath(file, path, idOut, 0) != 0;
}
