/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_0202b4f8(void *hh, unsigned magic, void *start, void *end, int opt);

void *NNSi_FndInitExpHeap(void *hh_void, void *end, int opt) {
    char *hh = (char*)hh_void;
    func_0202b4f8(hh, 0x46524D48, hh + 0x30, end, opt);
    *(int*)(hh + 0x24) = *(int*)(hh + 0x18);
    *(int*)(hh + 0x28) = *(int*)(hh + 0x1c);
    *(int*)(hh + 0x2c) = 0;
    return hh;
}
