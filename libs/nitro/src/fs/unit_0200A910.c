/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef int (*ArcRead)(void *arc, void *dst, int off, int len);

int FSi_ReadFileCommand(char *f) {
    char *arc = *(char **)(f + 8);
    int off = *(int *)(f + 0x2c);
    int len = *(int *)(f + 0x38);
    void *dst = *(void **)(f + 0x30);
    *(int *)(f + 0x2c) = off + len;
    return (*(ArcRead *)(arc + 0x48))(arc, dst, off, len);
}
