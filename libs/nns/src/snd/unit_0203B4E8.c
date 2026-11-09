/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void SND_SetChannelPan(u32 chBitMask, int pan);

void NNS_SndStrmSetChannelPan (NNSSndStrm * stream, int chNo, int pan)
{

    if (chNo > stream->numChannels - 1) return;

    SND_SetChannelPan((u32)(1 << stream->channelNo[ chNo ]), pan);
}
