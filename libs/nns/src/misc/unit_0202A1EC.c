/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef void (*FreeFn)(void *allocator, void *block);

void NNS_FndFreeToAllocator(void *allocator, void *block) {
    FreeFn *vt = *(FreeFn **)allocator;
    vt[1](allocator, block);
}
