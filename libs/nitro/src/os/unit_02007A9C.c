/* NitroSDK; adapted from khdays-decomp (CC0) OS_GetTick: this build reads the tick
 * counter through the file's data block (data_020cbff4 + 8), as OS_InitTick and
 * OSi_CountUpTick do. File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"
#include "nitro/os_types.h"

#define REG_TM0CNT_L_ADDR 0x04000100
#define reg_OS_IF (*(REGType32v *)0x04000214)
#define OS_IE_TIMER0 (1UL << 3)

typedef u16 REGType16;

typedef struct {
    u16 useTick;
    u16 pad;
    BOOL needResetTimer;
    vu64 tickCounter;
} OSiTickData;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern OSiTickData data_020cbff4;

OSTick OS_GetTick(void)
{
    vu16 countL;
    vu64 countH;

    OSIntrMode prev = OS_DisableInterrupts();

    countL = *(REGType16 *)((u32)REG_TM0CNT_L_ADDR);
    countH = data_020cbff4.tickCounter & 0xffffffffffffULL;

    if (reg_OS_IF & OS_IE_TIMER0 && !(countL & 0x8000)) {
        countH++;
    }

    (void)OS_RestoreInterrupts(prev);

    return (countH << 16) | countL;
}
