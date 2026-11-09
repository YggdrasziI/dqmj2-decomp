/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct Thread02001ff0 {
    char _0[0x64];
    int field_64;
    struct Thread02001ff0 *next;
};

struct Globals02001ff0 {
    char _0[0x2c];
    struct Thread02001ff0 *list;
};

extern struct Globals02001ff0 data_020cbcc0;

void *OSi_SelectThread(void)
{
    struct Thread02001ff0 *t = data_020cbcc0.list;
    while (t != 0 && t->field_64 != 1)
        t = t->next;
    return t;
}
