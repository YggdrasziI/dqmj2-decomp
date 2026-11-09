/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_SndPlayerSetInitialVolume(NNSSndHandle * handle, int volume);

void NNS_SndPlayerSetChannelPriority(NNSSndHandle * handle, int priority);

void NNS_SndPlayerSetSeqArcNo(NNSSndHandle * handle, int seqArcNo, int index);

void NNSi_SndPlayerStartSeq(NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const struct SNDBankData * bank);

NNSSndSeqPlayer * NNSi_SndPlayerAllocSeqPlayer(NNSSndHandle * handle, int playerNo, int prio);

void func_02038104(NNSSndSeqPlayer * seqPlayer);

NNSSndHeapHandle NNSi_SndPlayerAllocHeap(int playerNo, NNSSndSeqPlayer * seqPlayer);

NNSSndArcLoadResult NNSi_SndArcLoadBank(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);

BOOL StartSeqArc (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndSeqArcSeqInfo * sound, const NNSSndSeqArc * seqArc, int seqArcNo, int index)
{
    NNSSndSeqPlayer * player;
    NNSSndHeapHandle heap;
    SNDBankData * bank;
    NNSSndArcLoadResult result;

    player = NNSi_SndPlayerAllocSeqPlayer(handle, playerNo, playerPrio);
    if (player == NULL) return FALSE;

    heap = NNSi_SndPlayerAllocHeap(playerNo, player);

    result = NNSi_SndArcLoadBank(bankNo, NNS_SND_ARC_LOAD_BANK | NNS_SND_ARC_LOAD_WAVE, heap, FALSE, &bank);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        func_02038104(player);
        return FALSE;
    }

    NNSi_SndPlayerStartSeq(
        player,
        (u8 *)seqArc + seqArc->baseOffset,
        sound->offset,
        bank
        );

    NNS_SndPlayerSetInitialVolume(handle, sound->param.volume);
    NNS_SndPlayerSetChannelPriority(handle, sound->param.channelPrio);
    NNS_SndPlayerSetSeqArcNo(handle, seqArcNo, index);

    return TRUE;
}
