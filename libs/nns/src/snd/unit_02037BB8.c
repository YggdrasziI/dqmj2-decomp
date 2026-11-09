/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#define SND_COMMAND_BLOCK (1 << 0)

BOOL SND_FlushCommand(u32 flags);

void SND_WaitForCommandProc(u32 tag);

u32 SND_GetCurrentCommandTag(void);

void SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);

void func_020374d4(void);

void BeginSleep (void *)
{
    u32 commandTag;

    func_020374d4();

    SND_StopTimer(0, 0, 0, 0);

    commandTag = SND_GetCurrentCommandTag();
    (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
