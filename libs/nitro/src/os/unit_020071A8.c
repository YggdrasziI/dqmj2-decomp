/* NitroSDK; built from twewy (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

/* twewy's headers name this build's OS_DisableInterrupts and OS_RestoreInterrupts
 * OS_DisableIRQ and OS_RestoreIRQ, and give their names to other declarations:
 * those are set aside while the headers are read */
#define OS_DisableInterrupts twewy_OS_DisableInterrupts
#define OS_RestoreInterrupts twewy_OS_RestoreInterrupts
/* names used by the headers' inline functions */
#define ThreadInfo data_020cbce4

#include <nitro/os/cpustat.h>

#include <nitro/os/mutex.h>

#undef OS_DisableInterrupts
#undef OS_RestoreInterrupts
u32 OS_DisableInterrupts(void);
u32 OS_RestoreInterrupts(u32 state);
#define OS_DisableIRQ OS_DisableInterrupts
#define OS_RestoreIRQ OS_RestoreInterrupts


static void OSi_EnqueueTail(OSThread* thread, OSMutex* mutex);

static void OS_RemoveThreadMutex(OSThread* thread, OSMutex* mutex);

void OS_InitMutex(OSMutex* mutex);

void OS_LockMutex(OSMutex* mutex);

void OS_UnlockMutex(OSMutex* mutex);

void OS_UnlockAllQueuedThreadMutex(OSThread* thread);

void OSi_EnqueueTail(OSThread* thread, OSMutex* mutex);

void OS_RemoveThreadMutex(OSThread* thread, OSMutex* mutex);

BOOL OS_TryLockMutex(OSMutex* mutex) {
    ENTER_CRITICAL_SECTION();

    BOOL couldLock = FALSE;

    OSThread* currentThread = OS_GetCurrentThread();

    if (mutex->thread == NULL) {
        mutex->thread = currentThread;
        mutex->count++;
        OSi_EnqueueTail(currentThread, mutex);
        couldLock = TRUE;
    } else if (mutex->thread == currentThread) {
        mutex->count++;
        couldLock = TRUE;
    } else {
        couldLock = FALSE;
    }

    LEAVE_CRITICAL_SECTION();
    return couldLock;
}
