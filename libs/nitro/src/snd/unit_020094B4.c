/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/snd.h"

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

#define initialized data_020cc060

#define sSndMutex data_020cc064

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern void OS_InitMutex(OSMutex *mutex);

extern void func_02009514(void);

extern void SND_AlarmInit(void);

extern BOOL data_020cc060;

extern OSMutex data_020cc064;

void SND_Init(void)
{
    {
        if (initialized)
            return;
        initialized = TRUE;
    }

    OS_InitMutex(&sSndMutex);
    func_02009514();
    SND_AlarmInit();
}
