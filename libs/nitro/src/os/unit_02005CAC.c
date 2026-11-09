/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#define OS_IRQ_TIMER0_BIT  3

#define OSi_TimerSlots     (&data_020cbc5c[4])

typedef void (*OSIrqFunction)(void *arg);

typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_020cbc5c[];

extern u32 OS_EnableIrqMask(u32 mask);

void OSi_EnterTimerCallback(u32 timerNo, OSIrqFunction function, void *arg)
{
    OSi_TimerSlots[timerNo].pfnHandler = function;
    OSi_TimerSlots[timerNo].pArg = arg;

    OS_EnableIrqMask(1 << (timerNo + OS_IRQ_TIMER0_BIT));

    OSi_TimerSlots[timerNo].bKeepEnabled = 1;
}
