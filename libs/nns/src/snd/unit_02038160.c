/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNSi_SndFaderSet(NNSSndFader * fader, int target, int frame);

extern void ForceStopSeq(NNSSndSeqPlayer * seqPlayer);

extern void SetPlayerPriority(NNSSndSeqPlayer * seqPlayer, int priority);

extern void ForceStopSeq (NNSSndSeqPlayer * seqPlayer);

extern void SetPlayerPriority (NNSSndSeqPlayer * seqPlayer, int priority);

void NNSi_SndPlayerStopSeq (NNSSndSeqPlayer * seqPlayer, int fadeFrame)
{
    if (seqPlayer == NULL) return;
    if (seqPlayer->status == NNS_SND_SEQ_PLAYER_STATUS_STOP) return;

    if (fadeFrame == 0) {
        ForceStopSeq(seqPlayer);
        return;
    }

    NNSi_SndFaderSet(&seqPlayer->fader, 0, fadeFrame);
    SetPlayerPriority(seqPlayer, 0);

    seqPlayer->status = NNS_SND_SEQ_PLAYER_STATUS_FADEOUT;
}
