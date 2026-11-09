/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef struct OSThread {
    u8 _reserved0[0x70];
    u32 priority;              
    u8 _reserved74[0x8];
    struct OSThread *prev;     
    struct OSThread *next;     
} OSThread;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *pAfter;
    OSThread *pBefore;

    for (pAfter = queue->head;
         pAfter != NULL && pAfter->priority <= thread->priority;
         pAfter = pAfter->next) {
        if (pAfter == thread) {
            return;
        }
    }

    if (pAfter == NULL) {
        pBefore = queue->tail;
        if (pBefore == NULL) {
            queue->head = thread;
        } else {
            pBefore->next = thread;
        }
        thread->prev = pBefore;
        thread->next = NULL;
        queue->tail = thread;
        return;
    }

    pBefore = pAfter->prev;
    if (pBefore == NULL) {
        queue->head = thread;
    } else {
        pBefore->next = thread;
    }
    thread->prev = pBefore;
    thread->next = pAfter;
    pAfter->prev = thread;
}
