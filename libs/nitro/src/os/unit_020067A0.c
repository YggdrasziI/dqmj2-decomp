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

void OS_Terminate();

extern void OS_Terminate(void);

void OS_RescheduleThread(void);

void OS_WakeupThread(OSThreadQueue * queue);

u32 OS_DisableScheduler(void);

u32 OS_EnableScheduler(void);

void OSi_UnlockAllMutex(OSThread * thread);

extern void OSi_RemoveThreadFromList(OSThread * thread);

extern OSThread * OSi_RemoveSpecifiedLinkFromQueue (OSThreadQueue * queue, OSThread * thread);

extern void OSi_RemoveThreadFromList (OSThread * thread);

extern void OS_WakeupThread (OSThreadQueue * queue);

extern void OS_RescheduleThread (void);

extern u32 OS_DisableScheduler (void);

extern u32 OS_EnableScheduler (void);











void OSi_ExitThread_Destroy (void)
{
    OSThread * currentThread = OSi_GetCurrentThread();

#ifdef SDK_THREAD_INFINITY
    (void)OS_DisableScheduler();
#endif

#ifndef SDK_THREAD_INFINITY

#endif

    OSi_UnlockAllMutex(currentThread);

    if (currentThread->queue) {
        (void)OSi_RemoveSpecifiedLinkFromQueue(currentThread->queue, currentThread);
    }

    OSi_RemoveThreadFromList(currentThread);

#ifndef SDK_THREAD_INFINITY
    data_020cbcc0.threadInfo.entry[currentThread->id] = NULL;
#endif
    currentThread->state = OS_THREAD_STATE_TERMINATED;

#ifndef SDK_THREAD_INFINITY
    OS_WakeupThread(&currentThread->joinQueue);
#else
    OS_WakeupThread(&currentThread->joinQueue);
#endif

#ifdef SDK_THREAD_INFINITY
    (void)OS_EnableScheduler();
#endif

    OS_RescheduleThread();
    OS_Terminate();
}
