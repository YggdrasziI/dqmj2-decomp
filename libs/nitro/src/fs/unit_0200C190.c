/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct FSFile {
    char pad[0x24];
    int imageTop;      
    int imageBot;       
    int curOffset;       
} FSFile;

int FS_SeekFile(FSFile *file, int offset, int origin) {
    switch (origin) {
    case 0:
        offset = offset + file->imageTop;
        break;
    case 1:
        offset = offset + file->curOffset;
        break;
    case 2:
        offset = offset + file->imageBot;
        break;
    default:
        return 0;
    }

    if (offset < file->imageTop) offset = file->imageTop;
    if (offset > file->imageBot) offset = file->imageBot;
    file->curOffset = offset;
    return 1;
}
