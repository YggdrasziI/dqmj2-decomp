/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndPlayerSetSeqNo (NNSSndHandle * handle, int seqNo)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->seqType = NNS_SND_PLAYER_SEQ_TYPE_SEQ;
    handle->player->seqNo = (u16)seqNo;
}

void NNS_SndPlayerSetSeqArcNo (NNSSndHandle * handle, int seqArcNo, int index)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->seqType = NNS_SND_PLAYER_SEQ_TYPE_SEQARC;
    handle->player->seqNo = (u16)seqArcNo;
    handle->player->seqArcIndex = (u16)index;
}
