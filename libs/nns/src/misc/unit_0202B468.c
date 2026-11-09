/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *FindContainHeap(void *list, char *p) {
    char *heap = NNS_FndGetNextListObject(list, 0);
    while (heap != 0) {
        if (*(char **)(heap + 0x18) <= p && p < *(char **)(heap + 0x1c)) {
            char *inner = FindContainHeap(heap + 0xc, p);
            if (inner == 0) {
                inner = heap;
            }
            return inner;
        }
        heap = NNS_FndGetNextListObject(list, heap);
    }
    return 0;
}
