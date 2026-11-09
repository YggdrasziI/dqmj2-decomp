/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void SND_PauseSeq(int playerNo, BOOL flag);

void NNSi_SndPlayerPause (NNSSndSeqPlayer * seqPlayer, BOOL flag)
{
    if (seqPlayer == NULL) return;

    if (flag != seqPlayer->pauseFlag) {
        SND_PauseSeq(seqPlayer->playerNo, flag);
        seqPlayer->pauseFlag = (u8)flag;
    }
}
