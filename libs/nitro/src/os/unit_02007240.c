/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void OSi_DequeueItem(int *r0, int *r1)
{
    int *r2 = (int *)r1[4];
    int *next = (int *)r1[5];

    if (r2 == 0) {
        r0[35] = (int)next;
    } else {
        r2[5] = (int)next;
    }

    if (next == 0) {
        r0[34] = (int)r2;
    } else {
        next[4] = (int)r2;
    }
}
