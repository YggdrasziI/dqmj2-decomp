/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct Node {
    char pad[0x68];
    struct Node *next;  
    int pad2;           
    int value;          
} Node;

typedef struct {
    char pad[0x2c];
    Node *head;         
} ListHead;

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int);

extern void OSi_InsertThreadByPriority(void *);

extern void OSi_RescheduleThread(void);

extern ListHead data_020cbcc0;

extern Node data_020cbcf4;

int OSi_WaitOnExitProc(Node *target, int newval)
{
    Node *cur;
    Node *prev;
    int intr;

    prev = 0;
    cur = data_020cbcc0.head;
    intr = OS_DisableInterrupts();
    while (cur != 0 && cur != target) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == 0 || cur == &data_020cbcf4) {
        OS_RestoreInterrupts(intr);
        return 0;
    }
    if (cur->value != newval) {
        if (prev == 0) {
            data_020cbcc0.head = target->next;
        } else {
            prev->next = target->next;
        }
        target->value = newval;
        OSi_InsertThreadByPriority(target);
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(intr);
    return 1;
}
