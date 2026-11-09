/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#define OS_IRQ_DMA0_BIT 8

typedef void (*OSIrqFunction)(void *arg);

typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_020cbc5c[];

extern u32 OS_EnableIrqMask(u32 mask);

void OSi_EnterDmaCallback(u32 dmaNo, OSIrqFunction function, void *arg)
{
    u32 mask = 1 << (dmaNo + OS_IRQ_DMA0_BIT);

    data_020cbc5c[dmaNo].pfnHandler = function;
    data_020cbc5c[dmaNo].pArg = arg;
    data_020cbc5c[dmaNo].bKeepEnabled = OS_EnableIrqMask(mask) & mask;
}
