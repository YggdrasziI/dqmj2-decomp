/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void * NNS_FndGetNextListObject(NNSFndList * list, void * object);

void NNS_SndHeapClear(NNSSndHeapHandle heap);

extern NNSSndPlayer data_020dd638[ 32 ];

NNSSndHeapHandle NNSi_SndPlayerAllocHeap (int playerNo, NNSSndSeqPlayer * seqPlayer)
{
    NNSSndPlayer * player;
    NNSSndPlayerHeap * heap;

    player = &data_020dd638[ playerNo ];

    heap = (NNSSndPlayerHeap *)NNS_FndGetNextListObject(&player->heapList, NULL);
    if (heap == NULL) return NULL;

    NNS_FndRemoveListObject(&player->heapList, heap);

    heap->player = seqPlayer;
    seqPlayer->heap = heap;

    NNS_SndHeapClear(heap->handle);

    return heap->handle;
}
