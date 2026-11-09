/* NitroSDK; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

/* The thread functions' static data: one block in this build, read from its start */
extern struct {
    u32 unused0;                  /* 0x00 */
    u32 rescheduleCount;          /* 0x04: OSi_RescheduleCount */
    OSThread **currentThreadPtr;  /* 0x08: OSi_CurrentThreadPtr */
    BOOL isThreadInitialized;     /* 0x0c: OSi_IsThreadInitialized */
    u32 unused10[3];              /* 0x10 */
    void *stackForDestructor;     /* 0x1c: OSi_StackForDestructor */
    u32 threadIdCount;            /* 0x20: OSi_ThreadIdCount */
    OSThreadInfo threadInfo;      /* 0x24: OSi_ThreadInfo */
} data_020cbcc0;
#define OSi_CurrentThreadPtr data_020cbcc0.currentThreadPtr


#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define SDK_THREAD_INFINITY 1

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern void OSi_RescheduleThread(void);

extern void OSi_InsertLinkToQueue (OSThreadQueue * queue, OSThread * thread);

extern void OSi_RescheduleThread (void);











void OS_SleepThread (OSThreadQueue * queue)
{
    OSIntrMode enable;
    OSThread * currentThread;

    enable = OS_DisableInterrupts();
#ifndef SDK_THREAD_INFINITY
    {
        currentThread = OSi_GetCurrentThread();

        if (queue) {
            *queue |= (OSThreadQueue)(1UL << currentThread->id);
        }

        currentThread->state = OS_THREAD_STATE_WAITING;
        OSi_RescheduleThread();
    }
#else
    {
        currentThread = OSi_GetCurrentThread();

        if (queue) {
            currentThread->queue = queue;
            OSi_InsertLinkToQueue(queue, currentThread);
        }

        currentThread->state = OS_THREAD_STATE_WAITING;
        OSi_RescheduleThread();
    }
#endif
    (void)OS_RestoreInterrupts(enable);

}
