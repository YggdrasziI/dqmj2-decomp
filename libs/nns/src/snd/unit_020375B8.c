/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define NNS_FndCreateFrmHeap(startAddress, size) func_0202b324(startAddress, size, 0)

#define ROUNDUP(value, align) (((u32)(value) + ((align) - 1)) & ~((align) - 1))

#define HEAP_ALIGN 32

int NNSi_SndFaderGet(const NNSSndFader * fader);

extern int NNSi_SndFaderGet (const NNSSndFader * fader);

NNSFndHeapHandle func_0202b324(void * startAddress, u32 size, int optFlag);

void func_0202b35c(NNSFndHeapHandle heap);

extern BOOL InitHeap(NNSSndHeap * heap, NNSFndHeapHandle handle);

extern BOOL InitHeap (NNSSndHeap * heap, NNSFndHeapHandle handle);

void NNS_SndHeapClear(NNSSndHeapHandle heap);

extern void NNS_SndHeapClear (NNSSndHeapHandle heap);

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void * NNS_FndGetPrevListObject(NNSFndList * list, void * object);

void NNS_FndFreeToFrmHeap(NNSFndHeapHandle heap, int mode);

extern BOOL NewSection(NNSSndHeap * heap);

extern void EraseSync(void);

extern BOOL NewSection (NNSSndHeap * heap);

extern void EraseSync (void);

void NNS_FndAppendListObject(NNSFndList * list, void * object);

void * NNS_FndAllocFromFrmHeapEx(NNSFndHeapHandle heap, u32 size, int alignment);

BOOL NNS_FndRecordStateForFrmHeap(NNSFndHeapHandle heap, u32 tagName);

BOOL NNS_FndFreeByStateToFrmHeap(NNSFndHeapHandle heap, u32 tagName);

void NNSi_SndFaderInit (NNSSndFader * fader)
{

    fader->origin = fader->target = 0;
    fader->counter = fader->frame = 0;
}

void NNSi_SndFaderSet (NNSSndFader * fader, int target, int frame)
{

    fader->origin = NNSi_SndFaderGet(fader);
    fader->target = target;
    fader->frame = frame;
    fader->counter = 0;

}

int NNSi_SndFaderGet (const NNSSndFader * fader)
{
    s64 value;

    if (fader->counter >= fader->frame) {
        return fader->target;
    }

    value = (fader->target - fader->origin)
            * fader->counter / fader->frame
            + fader->origin;

    return (int)value;
}

void NNSi_SndFaderUpdate (NNSSndFader * fader)
{

    if (fader->counter < fader->frame) {
        fader->counter++;
    }
}

BOOL NNSi_SndFaderIsFinished (const NNSSndFader * fader)
{

    return fader->counter >= fader->frame ? TRUE : FALSE;
}

NNSSndHeapHandle NNS_SndHeapCreate (void * startAddress, u32 size)
{
    NNSSndHeap * heap;
    void * endAddress;
    NNSFndHeapHandle handle;

    endAddress = (u8 *)startAddress + size;
    startAddress = (void *)ROUNDUP(startAddress, 4);

    if (startAddress > endAddress) return NNS_SND_HEAP_INVALID_HANDLE;

    size = (u32)((u8 *)endAddress - (u8 *)startAddress);
    if (size < sizeof(NNSSndHeap)) {
        return NNS_SND_HEAP_INVALID_HANDLE;
    }

    size -= sizeof(NNSSndHeap);

    heap = (NNSSndHeap *)startAddress;
    startAddress = heap + 1;

    handle = NNS_FndCreateFrmHeap(startAddress, size);
    if (handle == NNS_FND_HEAP_INVALID_HANDLE) {
        return NULL;
    }

    if (!InitHeap(heap, handle)) {
        func_0202b35c(handle);
        return NNS_SND_HEAP_INVALID_HANDLE;
    }

    return heap;
}

void NNS_SndHeapDestroy (NNSSndHeapHandle heap)
{

    NNS_SndHeapClear(heap);
    func_0202b35c(heap->handle);
}

void NNS_SndHeapClear (NNSSndHeapHandle heap)
{
    NNSSndHeapSection * section = NULL;
    void * object;
    BOOL result;
    BOOL doCallback = FALSE;

    while ((section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL)) != NULL) {

        object = NULL;
        while ((object = NNS_FndGetPrevListObject(&section->blockList, object)) != NULL) {
            NNSSndHeapBlock * block = (NNSSndHeapBlock *)object;
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }

        NNS_FndRemoveListObject(&heap->sectionList, section);
    }

    NNS_FndFreeToFrmHeap(heap->handle, NNS_FND_FRMHEAP_FREE_ALL);

    if (doCallback) EraseSync();

    result = NewSection(heap);
}

void * NNS_SndHeapAlloc (NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2)
{
    NNSSndHeapSection * section;
    NNSSndHeapBlock * block;

    block = (NNSSndHeapBlock *)NNS_FndAllocFromFrmHeapEx(
        heap->handle, sizeof(NNSSndHeapBlock) + ROUNDUP(size, HEAP_ALIGN), HEAP_ALIGN);
    if (block == NULL) return NULL;

    section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

    block->size = size;
    block->callback = callback;
    block->data1 = data1;
    block->data2 = data2;
    NNS_FndAppendListObject(&section->blockList, block);

    return block->buffer;
}

int NNS_SndHeapSaveState (NNSSndHeapHandle heap)
{
    BOOL result;

    if (!NNS_FndRecordStateForFrmHeap(heap->handle, heap->sectionList.numObjects)) {
        return -1;
    }

    if (!NewSection(heap)) {
        result = NNS_FndFreeByStateToFrmHeap(heap->handle, 0);
        return -1;
    }

    return heap->sectionList.numObjects - 1;
}

void NNS_SndHeapLoadState (NNSSndHeapHandle heap, int level)
{
    NNSSndHeapSection * section;
    void * object = NULL;
    BOOL result;
    BOOL doCallback = FALSE;

    if (level == 0) {
        NNS_SndHeapClear(heap);
        return;
    }

    while (level < heap->sectionList.numObjects) {
        section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

        while ((object = NNS_FndGetPrevListObject(&section->blockList, object)) != NULL) {
            NNSSndHeapBlock * block = (NNSSndHeapBlock *)object;
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }

        NNS_FndRemoveListObject(&heap->sectionList, section);
    }

    result = NNS_FndFreeByStateToFrmHeap(heap->handle, (u32)level);

    if (doCallback) EraseSync();

    result = NNS_FndRecordStateForFrmHeap(heap->handle, heap->sectionList.numObjects);

    result = NewSection(heap);
}
