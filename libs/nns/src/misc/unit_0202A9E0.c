/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void *InitMBlock(void **list, unsigned short value)
{
    char *node = list[0];

    *(unsigned short *)node = value;
    *(unsigned short *)(node + 2) = 0;
    *(int *)(node + 4) = (char *)list[1] - (node + 0x10);
    *(int *)(node + 8) = 0;
    *(int *)(node + 0xc) = 0;

    return node;
}
