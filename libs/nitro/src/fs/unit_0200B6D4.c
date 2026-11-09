/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern unsigned int FSi_GetPackedName(const char *name, int len);

extern char *data_020cdc48;

void *FS_FindArchive(const char *name, int len) {
    unsigned int packed = FSi_GetPackedName(name, len);
    int enabled = OS_DisableInterrupts();
    char *arc = *(char **)&data_020cdc48;
    while (arc != 0 && *(unsigned int *)arc != packed) {
        arc = *(char **)(arc + 4);
    }
    OS_RestoreInterrupts(enabled);
    return arc;
}
