/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef struct OSThread {
    u8 reserved_00[0x68];
    struct OSThread *next;
    u32 id;
    u32 priority;
} OSThread;

typedef struct OSThreadInfo {
    u8 reserved_00[0x2c];
    OSThread *list;
} OSThreadInfo;

extern OSThreadInfo data_020cbcc0;

void OSi_InsertThreadByPriority(OSThread *thread)
{
    OSThread *current = data_020cbcc0.list;
    OSThread *previous = 0;

    while (current != 0 && current->priority < thread->priority) {
        previous = current;
        current = current->next;
    }

    if (previous == 0) {
        thread->next = data_020cbcc0.list;
        data_020cbcc0.list = thread;
    } else {
        thread->next = previous->next;
        previous->next = thread;
    }
}
