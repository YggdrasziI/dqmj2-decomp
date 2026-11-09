/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct S {
    char _0[0x110];
    int flags;
    char _114[0x168 - 0x114];
    void (*x168)(void *);
};

extern void FreeChannel(void *p);

extern void RemoveCommandByPlayer(void *list, void *node);

extern void FreePlayer(void *p);

extern char data_020de194[];

extern char *data_020ddb04[];

void OSi_DestroyThread(struct S *p)
{
    char *q;
    if (((p->flags << 31) >> 31) == 0) return;
    FreeChannel(p);
    p->x168(p);
    RemoveCommandByPlayer(data_020de194, p);
    q = data_020ddb04[1];
    if (q != 0) {
        RemoveCommandByPlayer(q + 0x4e0, p);
    }
    FreePlayer(p);
}
