/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_020094ec(void);

extern void func_02009500(void);

extern void DC_StoreRange(void *p, unsigned int len);

void SND_SetWaveDataAddress(char *table, int slot, void *addr) {
    func_020094ec();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    func_02009500();
}
