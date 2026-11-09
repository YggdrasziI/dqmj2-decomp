/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

extern struct NNSiFndHeapHead;

extern struct NNSiFndHeapHead *InitExpHeap(
    void *startAddress,
    void *endAddress,
    u16 optionFlag);

static inline void *AddToPointer(void *pointer, u32 value)
{
    return (void *)(value + (u32)pointer);
}

static inline void *RoundDownPointer(void *pointer, u32 alignment)
{
    return (void *)((u32)pointer & ~(alignment - 1));
}

static inline void *RoundUpPointer(void *pointer, u32 alignment)
{
    return (void *)(((u32)pointer + (alignment - 1)) & ~(alignment - 1));
}

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

struct NNSiFndHeapHead *NNS_FndCreateExpHeapEx(
    void *startAddress,
    u32 size,
    u16 optionFlag)
{
    void *endAddress = RoundDownPointer(AddToPointer(startAddress, size), 4);
    startAddress = RoundUpPointer(startAddress, 4);
    if ((u32)startAddress > (u32)endAddress ||
        GetOffsetFromPointers(startAddress, endAddress) < 0x4c) {
        return 0;
    }
    return InitExpHeap(startAddress, endAddress, optionFlag);
}
