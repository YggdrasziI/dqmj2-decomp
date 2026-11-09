/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *FindContainHeap(void *list, void *heap);

extern char data_020d6878;

void *FindListContainHeap(void *heap) {
    char *list = &data_020d6878;
    void *found = FindContainHeap(list, heap);
    if (found != 0) {
        list = (char *)found + 0xc;
    }
    return list;
}
