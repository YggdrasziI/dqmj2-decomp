/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern char *data_020d52b4;

void FS_EndOverlay(char *overlay) {
    char *collected;
    char *last;
    unsigned int start;
    unsigned int end;
    char *prev;
    char *listHead;
    char *node;
    char *next;
    int enabled;
    for (;;) {
        start = *(unsigned int *)(overlay + 4);
        end = start + (*(int *)(overlay + 8) + *(int *)(overlay + 0xc));
        collected = 0;
        last = collected;
        enabled = OS_DisableInterrupts();
        prev = collected;
        listHead = *(char **)&data_020d52b4;
        node = listHead;
        while (node != 0) {
            unsigned int arg = *(unsigned int *)(node + 8);
            unsigned int fn;
            next = *(char **)node;
            fn = *(unsigned int *)(node + 4);
            if ((arg == 0 && fn >= start && fn < end) || (arg >= start && arg < end)) {
                if (last != 0) {
                    *(char **)last = node;
                } else {
                    collected = node;
                }
                if (listHead == node) {
                    *(char **)&data_020d52b4 = next;
                    listHead = next;
                }
                *(char **)node = 0;
                last = node;
                if (prev != 0) {
                    *(char **)prev = next;
                }
            } else {
                prev = node;
            }
            node = next;
        }
        OS_RestoreInterrupts(enabled);
        if (collected == 0) {
            return;
        }
        do {
            void (*fn)(void *) = *(void (**)(void *))(collected + 4);
            next = *(char **)collected;
            if (fn != 0) {
                fn(*(void **)(collected + 8));
            }
            collected = next;
        } while (next != 0);
    }
}
