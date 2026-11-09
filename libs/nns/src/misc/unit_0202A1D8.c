/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef void *(*AllocFn)(void *allocator, unsigned int size);

void *NNS_FndAllocFromAllocator(void *allocator, unsigned int size) {
    AllocFn *vt = *(AllocFn **)allocator;
    return vt[0](allocator, size);
}
