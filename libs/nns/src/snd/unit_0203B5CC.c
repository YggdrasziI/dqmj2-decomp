/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

extern NNSSndStrmChannel data_020de9d0[ 16 ];

extern void * data_020de990[ NNS_SND_STRM_CHANNEL_MAX ];

void StrmCallback (NNSSndStrm * stream, NNSSndStrmCallbackStatus status)
{
    const unsigned long blockSize = stream->chBufLen / stream->interval;
    const unsigned long offset = blockSize * stream->curBuffer;
    int index;
    int chNo;

    for (index = 0; index < stream->numChannels; index++) {
        chNo = stream->channelNo[index];

        data_020de990[index] = (u8 *)(data_020de9d0[chNo].buffer) + offset;
    }

    stream->callback(
        status,
        stream->numChannels,
        data_020de990,
        blockSize,
        stream->format,
        stream->callbackArg
        );

    stream->curBuffer++;
    if (stream->curBuffer >= stream->interval) stream->curBuffer = 0;
}
