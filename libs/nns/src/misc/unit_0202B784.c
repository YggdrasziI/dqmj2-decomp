/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void *NNS_FndGetPrevListObject(char *base, char *table)
{
    if (table == 0) {
        return *(void **)(base + 4);
    }
    return *(void **)(table + *(unsigned short *)(base + 0xa));
}
