/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef int (*ArcWrite)(void *arc, void *dst, int off, int len);

int FSi_WriteFileCommand(char *f) {
    char *arc = *(char **)(f + 8);
    int off = *(int *)(f + 0x2c);
    int len = *(int *)(f + 0x38);
    void *dst = *(void **)(f + 0x30);
    *(int *)(f + 0x2c) = off + len;
    return (*(ArcWrite *)(arc + 0x4c))(arc, dst, off, len);
}
