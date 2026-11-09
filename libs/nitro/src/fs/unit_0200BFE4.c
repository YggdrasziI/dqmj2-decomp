/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct FileID {
    unsigned int arc;
    unsigned int id;
};

extern int FS_ConvertPathToFileID(struct FileID *id, const char *path);

extern int FS_OpenFileFast(void *file, struct FileID id);

int FS_OpenFile(void *file, const char *path) {
    struct FileID id;
    if (FS_ConvertPathToFileID(&id, path) == 0) {
        goto no;
    }
    if (FS_OpenFileFast(file, id) != 0) {
        return 1;
    }
no:
    return 0;
}
