/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern int CTRDG_IsOptionCartridge(void);

extern void OS_SetDPermissionsForProtectionRegion(int region, int perms);

extern int data_020d4cb8;

void CTRDG_Enable(int enable) {
    int enabled = OS_DisableInterrupts();
    int perms;
    data_020d4cb8 = enable;
    if (CTRDG_IsOptionCartridge() == 0) {
        if (enable != 0) {
            perms = 0x1000;
        } else {
            perms = 0x5000;
        }
        OS_SetDPermissionsForProtectionRegion(0xf000, perms);
    }
    OS_RestoreInterrupts(enabled);
}
