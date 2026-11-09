/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void GetRegionOfMBlock(void **out, char *node)
{
    unsigned short offset = (*(unsigned short *)(node + 2) >> 8) & 0x7f;
    char *base = node + 0x10;

    out[0] = node - offset;
    out[1] = (void *)(*(int *)(node + 4) + (int)base);
}
