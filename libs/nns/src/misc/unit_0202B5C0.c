/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void NNS_FndInitList(void *list, unsigned short offset)
{
    ((int *)list)[0] = 0;
    ((int *)list)[1] = 0;
    ((unsigned short *)list)[4] = 0;
    ((unsigned short *)list)[5] = offset;
}
