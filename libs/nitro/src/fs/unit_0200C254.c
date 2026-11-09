/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int func_02011268(void);

extern void FS_NotifyArchiveAsyncEnd(void *arc, int status);

void FSi_OnRomReadDone(void *arc) {
    int status = func_02011268() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(arc, status);
}
