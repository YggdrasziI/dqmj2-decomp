/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void NNS_SndHeapDestroy(NNSSndHeapHandle heap);

extern NNSSndPlayer data_020dd638[ 32 ];

void PlayerHeapDisposeCallback (void * mem, u32, u32, u32)
{
    NNSSndPlayerHeap * heap = (NNSSndPlayerHeap *)mem;
    NNSSndSeqPlayer * seqPlayer;

    if (heap->handle == NNS_SND_HEAP_INVALID_HANDLE) return;

    NNS_SndHeapDestroy(heap->handle);

    seqPlayer = heap->player;
    if (seqPlayer != NULL) {
        seqPlayer->heap = NULL;
    } else {
        NNS_FndRemoveListObject(&data_020dd638[ heap->playerNo ].heapList, heap);
    }
}
