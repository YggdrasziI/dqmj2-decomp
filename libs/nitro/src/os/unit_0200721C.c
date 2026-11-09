/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void OSi_EnqueueTail(void **list, void **node)
{
    void **tail = list[0x8c / 4];

    if (tail == 0) {
        list[0x88 / 4] = node;
    } else {
        tail[0x10 / 4] = node;
    }

    node[0x14 / 4] = tail;
    node[0x10 / 4] = 0;
    list[0x8c / 4] = node;
}
