/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

BOOL NNS_SndStrmAllocChannel(NNSSndStrm * stream, int numChannels, const u8 chNoList[]);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

BOOL AllocChannel (NNSSndStrmPlayer * player, int numChannels, const u8 chNoList[])
{

    if (player->allocChannelCount == 0) {
        if (!NNS_SndStrmAllocChannel(&player->stream, numChannels, chNoList)) {
            return FALSE;
        }
    }

    player->allocChannelCount++;

    return TRUE;
}
