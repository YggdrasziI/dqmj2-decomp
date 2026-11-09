/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

extern NNSSndPlayer data_020dd638[ 32 ];

void NNS_SndPlayerSetAllocatableChannel (int playerNo, u32 chBitFlag)
{

    data_020dd638[ playerNo ].allocChBitFlag = chBitFlag;
}
