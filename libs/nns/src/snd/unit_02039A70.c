/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

#define BLOCK_SIZE 512

#define BLOCK_NUM 4

void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

const NNSSndArcStrmPlayerInfo * NNS_SndArcGetStrmPlayerInfo(int playerNo);

extern NNSSndStrmPlayer data_020de1a0[4 ];

extern void func_0203a160(NNSSndStrmPlayer * player);

extern void func_0203a444(void * mem, u32 size, u32 data1, u32 data2);

extern void func_0203a160 (NNSSndStrmPlayer * player);

extern void func_0203a444 (void * mem, u32, u32 data1, u32);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

BOOL NNS_SndArcStrmSetupPlayer (NNSSndHeapHandle heap)
{
    int playerNo;
    const NNSSndArcStrmPlayerInfo * playerInfo;
    NNSSndStrmPlayer * player;
    void * buffer;
    u32 bufSize;
    int i;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; ++playerNo) {
        player = &data_020de1a0[ playerNo ];

        playerInfo = NNS_SndArcGetStrmPlayerInfo(playerNo);
        if (playerInfo == NULL) continue;

        player->numChannels = playerInfo->numChannels;
        for (i = 0; i < playerInfo->numChannels; i++) {
            player->chNoList[ i ] = playerInfo->chNoList[ i ];
        }

        if (heap != NNS_SND_HEAP_INVALID_HANDLE) {
            bufSize = (unsigned long)(BLOCK_SIZE * BLOCK_NUM * player->numChannels);
            buffer = NNS_SndHeapAlloc(heap, bufSize, func_0203a444, (u32)player, 0);
            if (buffer == NULL) return FALSE;

            func_0203a160(player);

            player->buffer = buffer;
            player->bufSize = bufSize;
        }
    }

    return TRUE;
}
