/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData * bank);

BOOL SND_GetNextInstData(const struct SNDBankData * bank, struct SNDInstData * inst, struct SNDInstPos * pos);

extern BOOL SndLoadWaveData(SNDWaveArc * waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap);

extern BOOL SndLoadWaveData (SNDWaveArc * waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap);

NNSSndArc * func_02038984(void);

const NNSSndArcPlayerInfo * NNS_SndArcGetPlayerInfo(int playerNo);

void NNS_SndPlayerSetPlayableSeqCount(int playerNo, int seqCount);

void NNS_SndPlayerSetAllocatableChannel(int playerNo, u32 chBitFlag);

BOOL NNS_SndPlayerCreateHeap(int playerNo, NNSSndHeapHandle heap, u32 size);

BOOL LoadSingleWaves (SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap)
{
    SNDInstPos pos = SND_GetFirstInstDataPos(bank);
    SNDInstData inst;

    if (bank == NULL) {
        return FALSE;
    }

    while (SND_GetNextInstData(bank, &inst, &pos)) {
        if (inst.type == SND_INST_PCM && waveArcNo == inst.param.wave[1]) {
            if (!SndLoadWaveData(waveArc, inst.param.wave[0], fileId, heap)) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL NNS_SndArcPlayerSetup (NNSSndHeapHandle heap)
{
    NNSSndArc * arc = func_02038984();
    int playerNo;
    const NNSSndArcPlayerInfo * playerInfo;

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_NUM; ++playerNo) {
        playerInfo = NNS_SndArcGetPlayerInfo(playerNo);
        if (playerInfo == NULL) continue;

        NNS_SndPlayerSetPlayableSeqCount(playerNo, playerInfo->seqMax);
        NNS_SndPlayerSetAllocatableChannel(playerNo, playerInfo->allocChBitFlag);

        if (playerInfo->heapSize > 0 && heap != NNS_SND_HEAP_INVALID_HANDLE) {
            int i;

            for (i = 0; i < playerInfo->seqMax; i++) {
                if (!NNS_SndPlayerCreateHeap(playerNo, heap, playerInfo->heapSize)) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}
