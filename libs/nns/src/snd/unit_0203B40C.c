/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);

void func_0200f218(PMSleepCallbackInfo * info);

void func_0200f230(PMSleepCallbackInfo * info);

void NNS_SndStrmStart (NNSSndStrm * stream)
{

    SND_StartTimer(
        stream->chBitMask,
        0,
        (u32)(1 << stream->alarmNo),
        0
        );

    if (!stream->startFlag) {
        func_0200f218(&stream->preSleepInfo);
        func_0200f230(&stream->postSleepInfo);

        stream->startFlag = TRUE;
    }
}
