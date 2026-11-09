/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int *data_020cde00;

extern void CARDi_LockResource(int id, int resource);

extern void func_02006074(int id);

extern void func_02006090(int id);

extern void CARDi_UnlockResource(int id, int resource);

int CARD_GetResultCode(void) {
    return *data_020cde00;
}

void CARD_LockRom(int id) {
    CARDi_LockResource(id, 1);
    func_02006074(id);
}

void CARD_UnlockRom(int id) {
    func_02006090(id);
    CARDi_UnlockResource(id, 1);
}
