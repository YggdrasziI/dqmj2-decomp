/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#define MIi_DmaSetParams_wait func_01ff85d0

#define MIi_GXDmaParams data_020446b0

extern void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);

extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);

extern void MIi_DmaSetParams(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

extern void func_01ff85d0(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

extern void MI_WaitDma(u32 dmaNo);

extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);

extern u32 OS_ResetRequestIrqMask(u32 intr);

extern void OS_Terminate(void);

extern MIiGXDmaParams data_020446b0;

extern void MIi_DMACallback(void *arg);

extern void MIi_DMAFastCallback(void *arg);

static inline void MIi_CallCallback(MIDmaCallback callback, void *arg)
{
    if (callback) {
        (callback)(arg);
    }
}

void MI_DmaCopy32Async (u32 dmaNo, const void * src, void * dest, u32 size, MIDmaCallback callback, void * arg)
{

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_INC);

    if (size == 0) {
        MIi_CallCallback(callback, arg);
    } else {
        MI_WaitDma(dmaNo);

        if (callback) {
            OSi_EnterDmaCallback(dmaNo, callback, arg);
            MIi_DmaSetParams(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32_IF(size));
        } else {
            MIi_DmaSetParams(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32(size));
        }
    }
}
