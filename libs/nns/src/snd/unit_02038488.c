/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

extern NNSFndList data_020dd1ec;

extern void InsertPlayerList(NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer);

extern void InsertPrioList(NNSSndSeqPlayer * seqPlayer);

extern void InsertPlayerList (NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer);

extern void InsertPrioList (NNSSndSeqPlayer * seqPlayer);

void SetPlayerPriority (NNSSndSeqPlayer * seqPlayer, int priority)
{
    NNSSndPlayer * player;

    player = seqPlayer->player;

    if (player != NULL) {
        NNS_FndRemoveListObject(&player->playerList, seqPlayer);
        seqPlayer->player = NULL;
    }

    NNS_FndRemoveListObject(&data_020dd1ec, seqPlayer);

    seqPlayer->prio = (u8)priority;

    if (player != NULL) {
        InsertPlayerList(player, seqPlayer);
    }

    InsertPrioList(seqPlayer);
}
