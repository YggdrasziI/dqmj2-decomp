/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct Node {
    void *x0;
    int x4;
    int x8;
    int xc;
};

struct Q {
    char _0[0x10];
    int x10;
};

extern int IsVramTransferTaskQueueFull_(void *q);

extern void *NNSi_GfdGetEndVramTransferTaskQueue(void *q);

extern void NNSi_GfdPushVramTransferTaskQueue(void *q);

extern char data_020dea60[];

int GFXi_EnqueueCommand(void *a, int b, int c, int d)
{
    struct Node *n;
    struct Q *q = (struct Q *)data_020dea60;
    if (IsVramTransferTaskQueueFull_(q) != 0) return 0;
    n = (struct Node *)NNSi_GfdGetEndVramTransferTaskQueue(q);
    n->x0 = a;
    n->x4 = c;
    n->x8 = b;
    n->xc = d;
    NNSi_GfdPushVramTransferTaskQueue(q);
    q->x10 = q->x10 + n->xc;
    return 1;
}
