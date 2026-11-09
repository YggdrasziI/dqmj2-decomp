/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

extern NNSSndPlayer data_020dd638[ 32 ];

void NNS_SndPlayerSetPlayableSeqCount (int playerNo, int seqCount)
{

    data_020dd638[ playerNo ].playableSeqCount = (u16)seqCount;
}
