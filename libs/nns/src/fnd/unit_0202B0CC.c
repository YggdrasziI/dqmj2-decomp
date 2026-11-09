/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;

typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSiFndHeapHead NNSiFndHeapHead;

struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void * heapStart;
    void * heapEnd;
    u32 attribute;
};

typedef NNSiFndHeapHead * NNSFndHeapHandle;

typedef struct NNSiFndExpHeapMBlockHead NNSiFndExpHeapMBlockHead;

struct NNSiFndExpHeapMBlockHead {
    u16 signature;
    u16 attribute;
    u32 blockSize;
    NNSiFndExpHeapMBlockHead * pMBHeadPrev;
    NNSiFndExpHeapMBlockHead * pMBHeadNext;
};

typedef struct NNSiFndExpMBlockList NNSiFndExpMBlockList;

struct NNSiFndExpMBlockList {
    NNSiFndExpHeapMBlockHead * head;
    NNSiFndExpHeapMBlockHead * tail;
};

typedef struct NNSiFndExpHeapHead NNSiFndExpHeapHead;

struct NNSiFndExpHeapHead {
    NNSiFndExpMBlockList mbFreeList;
    NNSiFndExpMBlockList mbUsedList;
    u16 groupID;
    u16 feature;
};

typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);

typedef u32 NNSiUIntPtr;

typedef struct NNSiMemRegion NNSiMemRegion;

struct NNSiMemRegion {
    void * start;
    void * end;
};

extern void GetRegionOfMBlock (NNSiMemRegion * region, NNSiFndExpHeapMBlockHead * block);

extern NNSiFndExpHeapMBlockHead * RemoveMBlock (NNSiFndExpMBlockList * list, NNSiFndExpHeapMBlockHead * block);

extern BOOL func_0202ad8c (NNSiFndExpHeapHead * pEHHead, const NNSiMemRegion * pRegion);

inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}

inline void* AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}

inline void* SubU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) - val );
}

static inline NNSiFndExpHeapHead * GetExpHeapHeadPtrFromHeapHead (NNSiFndHeapHead * pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}

static inline NNSiFndExpHeapHead * GetExpHeapHeadPtrFromHandle (NNSFndHeapHandle heap)
{
    return GetExpHeapHeadPtrFromHeapHead(heap);
}

static inline NNSiFndExpHeapMBlockHead * GetMBlockHeadPtr (void * memBlock)
{
    return SubU32ToPtr(memBlock, sizeof(NNSiFndExpHeapMBlockHead));
}

void NNS_FndFreeToExpHeap (NNSFndHeapHandle heap, void * memBlock)
{

    {
        NNSiFndHeapHead * pHeapHd = heap;
        NNSiFndExpHeapHead * pExpHeapHd = GetExpHeapHeadPtrFromHandle(pHeapHd);
        NNSiFndExpHeapMBlockHead * pMBHead = GetMBlockHeadPtr(memBlock);
        NNSiMemRegion region;

        GetRegionOfMBlock(&region, pMBHead);
        (void)RemoveMBlock(&pExpHeapHd->mbUsedList, pMBHead);
        (void)func_0202ad8c(pExpHeapHd, &region);
    }
}
