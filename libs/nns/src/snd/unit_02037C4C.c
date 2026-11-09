/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void NNS_FndAppendListObject(NNSFndList * list, void * object);

NNSSndHeapHandle NNS_SndHeapCreate(void * startAddress, u32 size);

void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

extern NNSSndPlayer data_020dd638[ 32 ];

extern void PlayerHeapDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);

extern void PlayerHeapDisposeCallback (void * mem, u32, u32, u32);

BOOL NNS_SndPlayerCreateHeap (int playerNo, NNSSndHeapHandle heap, u32 size)
{
    NNSSndHeapHandle playerHeapHandle;
    NNSSndPlayerHeap * playerHeap;
    void * buffer;

    buffer = NNS_SndHeapAlloc(heap, sizeof(NNSSndPlayerHeap) + size, PlayerHeapDisposeCallback, 0, 0);
    if (buffer == NULL) {
        return FALSE;
    }

    playerHeap = (NNSSndPlayerHeap *)buffer;

    playerHeap->player = NULL;
    playerHeap->playerNo = playerNo;
    playerHeap->handle = NNS_SND_HEAP_INVALID_HANDLE;

    playerHeapHandle = NNS_SndHeapCreate(
        (u8 *)buffer + sizeof(NNSSndPlayerHeap),
        size
        );
    if (playerHeapHandle == NNS_SND_HEAP_INVALID_HANDLE) {
        return FALSE;
    }

    playerHeap->handle = playerHeapHandle;
    NNS_FndAppendListObject(&data_020dd638[ playerNo ].heapList, playerHeap);

    return TRUE;
}
