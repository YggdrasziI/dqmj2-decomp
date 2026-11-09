/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void *NNS_FndGetNextListObject(void *list, void *obj) {
    if (obj == 0) {
        return *(void **)list;
    }
    return *(void **)((char *)obj + *(unsigned short *)((char *)list + 0xa) + 4);
}
