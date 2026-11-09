/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void * NNS_FndGetNextListObject(NNSFndList * list, void * object);

extern NNSFndList data_020dd1ec;

extern NNSFndList data_020dd1e0;

extern void ForceStopSeq(NNSSndSeqPlayer * seqPlayer);

extern void InsertPrioList(NNSSndSeqPlayer * seqPlayer);

extern void InsertPrioList (NNSSndSeqPlayer * seqPlayer);

extern void ForceStopSeq (NNSSndSeqPlayer * seqPlayer);

NNSSndSeqPlayer * AllocSeqPlayer (int prio)
{
    NNSSndSeqPlayer * seqPlayer;

    seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020dd1e0, NULL);
    if (seqPlayer == NULL) {
        seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020dd1ec, NULL);

        if (prio < seqPlayer->prio) return NULL;

        ForceStopSeq(seqPlayer);
    }
    NNS_FndRemoveListObject(&data_020dd1e0, seqPlayer);

    seqPlayer->prio = (u8)prio;

    InsertPrioList(seqPlayer);

    return seqPlayer;
}
