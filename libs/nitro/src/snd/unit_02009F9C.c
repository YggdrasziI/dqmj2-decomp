/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct Node {
    char pad0[4];
    struct Node *next; 
    char pad1[0x10];
    struct Node *link; 
};

struct Slot {
    struct Node *head;
    void *repl;
};

struct Mgr {
    char pad0[0x18];
    struct Slot list[4]; 
};

extern void DC_StoreRange(void *addr, unsigned size);

extern void func_020094ec(void);

extern void func_02009500(void);

void SND_DestroyBank(struct Mgr *mgr) {
    struct Node *sentinel;
    int i;
    struct Node *node;
    struct Node *p;
    struct Node *q;

    func_020094ec();
    sentinel = (struct Node *)&mgr->list[0];
    for (i = 0; i < 4; i++) {
        node = mgr->list[i].head;
        if (node != 0) {
            p = node->link;
            if (sentinel == p) {
                node->link = (struct Node *)mgr->list[i].repl;
                DC_StoreRange(node, 0x3c);
            } else {
                if (p != 0) {
                    do {
                        q = p->next;
                        if (sentinel == q) break;
                        p = q;
                    } while (q != 0);
                }
                p->next = (struct Node *)mgr->list[i].repl;
                DC_StoreRange(p, 8);
            }
        }
        sentinel = (struct Node *)((char *)sentinel + 8);
    }
    func_02009500();
}
