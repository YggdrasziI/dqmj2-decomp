/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void SND_ClearChannelBit(int alarmNo);

extern NNSFndList data_020de984;

void ShutdownStrm (NNSSndStrm * stream)
{
    SND_ClearChannelBit(stream->alarmNo);
    NNS_FndRemoveListObject(&data_020de984, stream);

    stream->activeFlag = FALSE;
}
