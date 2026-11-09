/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/hw.h"

#define OS_TIMER_0 0

#define OS_TIMER_PRESCALER_64 (1UL << 0)

#define OSi_TICK_TIMERCONTROL  (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

#define OSi_TICK_TIMER         OS_TIMER_0

#define OSi_NeedResetTimer data_020cbff4.needResetTimer

#define OSi_TickCounter data_020cbff4.tickCounter

typedef void *OSMessage;

typedef int OSTimer;

extern struct { u16 useTick; u16 pad; BOOL needResetTimer; volatile u64 tickCounter; } data_020cbff4;

extern void OSi_EnterTimerCallback(int timerNo, void (*callback)(void *), void *arg);

static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    *((vu16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    *((vu16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}

void OSi_CountUpTick(void)
{
    OSi_TickCounter++;

    if (OSi_NeedResetTimer) {
        OS_SetTimerControl(OSi_TICK_TIMER, 0);
        OS_SetTimerCount((OSTimer)OSi_TICK_TIMER, (u16)0);
        OS_SetTimerControl(OSi_TICK_TIMER, (u16)OSi_TICK_TIMERCONTROL);

        OSi_NeedResetTimer = FALSE;
    }

    OSi_EnterTimerCallback(OSi_TICK_TIMER, (void (*)(void *))OSi_CountUpTick, 0);
}
