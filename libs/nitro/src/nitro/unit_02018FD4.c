/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int CTRDG_IsExisting(void);

extern int CTRDGi_IsAgbCartridgeAtInit(void);

int CTRDG_IsOptionCartridge(void) {
    if (CTRDG_IsExisting() == 0) {
        goto no;
    }
    if (CTRDGi_IsAgbCartridgeAtInit() == 0) {
        return 1;
    }
no:
    return 0;
}
