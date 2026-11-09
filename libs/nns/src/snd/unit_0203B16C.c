/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void NNS_FndInitList(NNSFndList * list, u16 offset);

extern NNSFndList data_020de984;

extern void func_0203b67c(void * arg);

extern void EndSleep(void * arg);

extern void func_0203b67c (void * arg);

extern void EndSleep (void * arg);

extern BOOL data_020de980;

static inline void PM_SetSleepCallbackInfo (PMSleepCallbackInfo * info, PMSleepCallback callback, void * arg)
{
    info->callback = callback;
    info->arg = arg;
}

void NNS_SndStrmInit (NNSSndStrm * stream)
{

    {

        if (!data_020de980) {
            NNS_FND_INIT_LIST(&data_020de984, NNSSndStrm, link);
            data_020de980 = TRUE;
        }
    }

    PM_SetSleepCallbackInfo(&stream->preSleepInfo, func_0203b67c, stream);
    PM_SetSleepCallbackInfo(&stream->postSleepInfo, EndSleep, stream);

    stream->chBitMask = 0;
    stream->numChannels = 0;
    stream->activeFlag = FALSE;
    stream->startFlag = FALSE;
}
