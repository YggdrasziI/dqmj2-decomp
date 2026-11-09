/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void NNS_SndUnlockChannel(u32 chBitFlag);

void NNS_SndStrmFreeChannel (NNSSndStrm * stream)
{

    if (stream->chBitMask == 0) return;

    NNS_SndUnlockChannel(stream->chBitMask);

    stream->chBitMask = 0;
    stream->numChannels = 0;
}
