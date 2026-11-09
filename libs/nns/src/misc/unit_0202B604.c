/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void SetFirstObject(void *list, void *obj);

void NNS_FndAppendListObject(char *list, char *obj) {
    unsigned short off;
    char *tail;
    if (*(void **)list == 0) {
        SetFirstObject(list, obj);
        return;
    }
    off = *(unsigned short *)(list + 0xa);
    *(void **)(obj + off) = *(void **)(list + 4);
    *(void **)(obj + off + 4) = 0;
    tail = *(char **)(list + 4) + *(unsigned short *)(list + 0xa);
    *(void **)(tail + 4) = obj;
    *(void **)(list + 4) = obj;
    *(unsigned short *)(list + 8) = (unsigned short)(*(unsigned short *)(list + 8) + 1);
}
