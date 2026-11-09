/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void SND_StopSeq(int playerNo);

void SND_SetPlayerVolume(int playerNo, int volume);

extern void ShutdownPlayer(NNSSndSeqPlayer * seqPlayer);

extern void ShutdownPlayer (NNSSndSeqPlayer * seqPlayer);

void ForceStopSeq (NNSSndSeqPlayer * seqPlayer)
{
    if (seqPlayer->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) {
        SND_SetPlayerVolume(seqPlayer->playerNo, SND_VOLUME_DB_MIN);
    }
    SND_StopSeq(seqPlayer->playerNo);
    ShutdownPlayer(seqPlayer);
}
