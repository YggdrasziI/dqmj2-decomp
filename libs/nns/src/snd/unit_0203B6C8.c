/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

void SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);

extern void StrmCallback(NNSSndStrm * stream, NNSSndStrmCallbackStatus status);

extern void StrmCallback (NNSSndStrm * stream, NNSSndStrmCallbackStatus status);

void EndSleep (void * arg)
{
    NNSSndStrm * stream = (NNSSndStrm *)arg;

    if (!stream->startFlag) return;

    while (stream->curBuffer != 0) {
        OSIntrMode old = OS_DisableInterrupts();

        StrmCallback(stream, NNS_SND_STRM_CALLBACK_INTERVAL);

        (void)OS_RestoreInterrupts(old);
    }

    SND_StartTimer(
        stream->chBitMask,
        0,
        (u32)(1 << stream->alarmNo),
        0
        );
}
