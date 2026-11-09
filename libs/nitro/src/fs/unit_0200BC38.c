/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void FS_SetArchiveProc(char *arc, void *proc, unsigned int flags) {
    if (flags == 0) {
        proc = 0;
    } else if (proc == 0) {
        flags = 0;
    }
    *(void **)(arc + 0x54) = proc;
    *(unsigned int *)(arc + 0x58) = flags;
}
