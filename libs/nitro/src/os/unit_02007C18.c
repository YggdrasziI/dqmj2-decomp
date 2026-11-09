/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern u16 data_020cc004;

void func_0200798c(int timerNum);

void OS_EndAlarm (void)
{
    OSIntrMode enabled;

    enabled = OS_DisableInterrupts();

    if (data_020cc004) {

        func_0200798c(OSi_ALARM_TIMER);

        data_020cc004 = FALSE;
    }

    (void)OS_RestoreInterrupts(enabled);
}
