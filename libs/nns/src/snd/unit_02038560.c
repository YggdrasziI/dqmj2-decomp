/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

extern u32 sAlarmLock;

extern u32 data_020ddab8;

extern u32 sChannelLock;

void NNS_SndUnlockCapture (u32 capBitFlag)
{
    data_020ddab8 &= ~capBitFlag;
}
