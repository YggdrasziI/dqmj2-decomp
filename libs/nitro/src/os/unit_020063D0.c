/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef struct OSContext {
    char dummy[1];
} OSContext;

typedef void (*OSSwitchThreadCallback)(void *from, void *to);

struct Globals {
     OSSwitchThreadCallback systemCallback;
     unsigned int rescheduleCount;
     void ***currentThreadPtr;
     char _pad[0x18];
     unsigned short isNeedRescheduling;
     unsigned short irqDepth;
     void *currentThread;
     void *list;
     OSSwitchThreadCallback switchCallback;
};

struct ThreadInfo2 {
     unsigned short isNeedRescheduling;
     unsigned short irqDepth;
     void *currentThread;
     void *list;
     OSSwitchThreadCallback switchCallback;
};

extern BOOL OS_SaveContext(OSContext *context);

extern void OS_LoadContext(OSContext *context);

extern int OS_GetProcMode(void);

extern void *OSi_SelectThread(void);

extern struct ThreadInfo2 data_020cbce4;

extern struct Globals data_020cbcc0;

void OSi_RescheduleThread(void) {
    struct ThreadInfo2 *info;
    void **curPtr;
    void *cur;
    void *next;
    OSSwitchThreadCallback cb;

    if (data_020cbcc0.rescheduleCount != 0) return;

    info = &data_020cbce4;
    if (data_020cbcc0.irqDepth != 0 || OS_GetProcMode() == 0x12) {
        info->isNeedRescheduling = 1;
        return;
    }

    curPtr = (void **)data_020cbcc0.currentThreadPtr;
    cur = *curPtr;
    next = OSi_SelectThread();

    if (cur == next || next == 0) return;

    if (*(int *)((char *)cur + 0x64) != 2) {
        if (OS_SaveContext((OSContext *)cur)) return;
    }

    cb = data_020cbcc0.systemCallback;
    if (cb != 0) {
        cb(cur, next);
    }

    cb = info->switchCallback;
    if (cb != 0) {
        cb(cur, next);
    }

    data_020cbcc0.currentThread = next;
    OS_LoadContext((OSContext *)next);
}
