/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int func_02010910(void);

extern void func_02010904(void);

extern void CARDi_UnlockResource(int resource, int kind);

void CARD_UnlockBackup(int resource) {
    if (func_02010910() == 0)
        func_02010904();
    CARDi_UnlockResource(resource, 2);
}
