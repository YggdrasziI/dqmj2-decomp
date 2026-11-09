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


#define offsetof(type, member) ((u32)&(((type *)0)->member))











void OSi_RemoveThreadFromList (OSThread * thread)
{
    OSThread * t = data_020cbcc0.threadInfo.list;
    OSThread * pre = NULL;

    while (t && t != thread) {
        pre = t;
        t = t->next;
    }

    if (!pre) {
        data_020cbcc0.threadInfo.list = thread->next;
    } else {
        pre->next = thread->next;
    }
}
