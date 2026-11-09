/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void CpuSet(const void *src, void *dst, unsigned ctrl);

extern int OS_GetLockID(void);

extern int data_020d4cbc;

extern struct { char _pad[6]; unsigned short lockid; } data_020d4cb8;

void CTRDGi_InitCommon(void) {
    int zero = 0;
    CpuSet(&zero, &data_020d4cbc, 0x05000001);
    data_020d4cb8.lockid = (unsigned short)OS_GetLockID();
}
