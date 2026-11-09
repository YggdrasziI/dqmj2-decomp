/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *func_0202b1f8(void *hh, unsigned size, unsigned align);

extern void *func_0202b178(void *hh, unsigned size, unsigned align);

void *NNS_FndAllocFromFrmHeapEx(void *heap, unsigned size, int align) {
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    heap = (char *)heap + 0x24;
    if (align >= 0) {
        return func_0202b178(heap, size, (unsigned)align);
    } else {
        return func_0202b1f8(heap, size, (unsigned)-align);
    }
}
