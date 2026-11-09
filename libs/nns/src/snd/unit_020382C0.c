/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndInsertListObject(NNSFndList * list, void * target, void * object);

void * NNS_FndGetNextListObject(NNSFndList * list, void * object);

extern NNSFndList data_020dd1ec;

void InsertPrioList (NNSSndSeqPlayer * seqPlayer)
{
    NNSSndSeqPlayer * next = NULL;
    while ((next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020dd1ec, next)) != NULL) {
        if (seqPlayer->prio < next->prio) break;
    }

    NNS_FndInsertListObject(&data_020dd1ec, next, seqPlayer);
}
