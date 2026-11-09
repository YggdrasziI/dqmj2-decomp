/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_SndPlayerSetInitialVolume(NNSSndHandle * handle, int volume);

void NNS_SndPlayerSetChannelPriority(NNSSndHandle * handle, int priority);

void NNS_SndPlayerSetSeqNo(NNSSndHandle * handle, int seqNo);

void NNSi_SndPlayerStartSeq(NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const struct SNDBankData * bank);

NNSSndSeqPlayer * NNSi_SndPlayerAllocSeqPlayer(NNSSndHandle * handle, int playerNo, int prio);

void func_02038104(NNSSndSeqPlayer * seqPlayer);

NNSSndHeapHandle NNSi_SndPlayerAllocHeap(int playerNo, NNSSndSeqPlayer * seqPlayer);

NNSSndArcLoadResult NNSi_SndArcLoadSeq(int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);

NNSSndArcLoadResult NNSi_SndArcLoadBank(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);

BOOL StartSeq (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndArcSeqInfo * info, int seqNo)
{
    NNSSndSeqPlayer * player;
    NNSSndHeapHandle heap;
    NNSSndSeqData * seq;
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

    result = NNSi_SndArcLoadSeq(seqNo, NNS_SND_ARC_LOAD_SEQ, heap, FALSE, &seq);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        func_02038104(player);
        return FALSE;
    }

    NNSi_SndPlayerStartSeq(
        player,
        (u8 *)seq + seq->baseOffset,
        0,
        bank
        );

    NNS_SndPlayerSetInitialVolume(handle, info->param.volume);
    NNS_SndPlayerSetChannelPriority(handle, info->param.channelPrio);
    NNS_SndPlayerSetSeqNo(handle, seqNo);

    return TRUE;
}
