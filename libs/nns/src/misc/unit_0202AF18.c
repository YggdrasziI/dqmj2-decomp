/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *AllocFromHead(void *heap, unsigned int size, int align);

extern void *AllocFromTail(void *heap, unsigned int size, int align);

void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int align) {
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3u;
    if (align >= 0) {
        return AllocFromHead(heap, size, align);
    }
    return AllocFromTail(heap, size, -align);
}
