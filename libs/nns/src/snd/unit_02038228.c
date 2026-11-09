/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define FADER_SHIFT 8

void NNSi_SndFaderInit(NNSSndFader * fader);

void NNSi_SndFaderSet(NNSSndFader * fader, int target, int frame);

void InitPlayer (NNSSndSeqPlayer * seqPlayer)
{

    seqPlayer->pauseFlag = FALSE;
    seqPlayer->startFlag = FALSE;
    seqPlayer->prepareFlag = FALSE;

    seqPlayer->seqType = NNS_SND_PLAYER_SEQ_TYPE_INVALID;

    seqPlayer->volume = 0;

    seqPlayer->initVolume = 127;
    seqPlayer->extVolume = 127;

    NNSi_SndFaderInit(&seqPlayer->fader);
    NNSi_SndFaderSet(&seqPlayer->fader, 127 << FADER_SHIFT, 1);
}
