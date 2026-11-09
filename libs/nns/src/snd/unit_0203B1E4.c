/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

BOOL NNS_SndLockChannel(u32 chBitFlag);

BOOL NNS_SndStrmAllocChannel (NNSSndStrm * stream, int numChannels, const u8 chNoList[])
{
    u32 chBitMask;
    int i;

    chBitMask = 0;
    for (i = 0; i < numChannels; i++) {

        stream->channelNo[ i ] = chNoList[ i ];
        chBitMask |= (1 << chNoList[ i ]);
    }

    if (!NNS_SndLockChannel(chBitMask)) {
        return FALSE;
    }

    stream->numChannels = numChannels;
    stream->chBitMask = chBitMask;

    return TRUE;
}
