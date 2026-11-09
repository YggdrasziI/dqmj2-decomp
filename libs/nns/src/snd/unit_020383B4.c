/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndAppendListObject(NNSFndList * list, void * object);

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

extern NNSFndList data_020dd1ec;

extern NNSFndList data_020dd1e0;

void ShutdownPlayer (NNSSndSeqPlayer * seqPlayer)
{
    NNSSndPlayer * player;

    if (seqPlayer->handle != NULL) {
        seqPlayer->handle->player = NULL;
        seqPlayer->handle = NULL;
    }

    player = seqPlayer->player;
    NNS_FndRemoveListObject(&player->playerList, seqPlayer);
    seqPlayer->player = NULL;

    if (seqPlayer->heap != NULL) {
        NNS_FndAppendListObject(&player->heapList, seqPlayer->heap);
        seqPlayer->heap->player = NULL;
        seqPlayer->heap = NULL;
    }

    NNS_FndRemoveListObject(&data_020dd1ec, seqPlayer);
    NNS_FndAppendListObject(&data_020dd1e0, seqPlayer);

    seqPlayer->status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
}
