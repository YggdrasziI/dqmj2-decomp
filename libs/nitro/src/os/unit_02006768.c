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

extern OSIntrMode OS_DisableInterrupts(void);

extern void OSi_ExitThread_Destroy(void);

extern void OSi_ExitThread_Destroy (void);











void OSi_ExitThread (void * arg)
{
    OSThread * currentThread = OSi_GetCurrentThread();
    OSThreadDestructor destructor;

    destructor = currentThread->destructor;
    if (destructor) {
        currentThread->destructor = NULL;
        destructor(arg);
        (void)OS_DisableInterrupts();
    }

    OSi_ExitThread_Destroy();
}
