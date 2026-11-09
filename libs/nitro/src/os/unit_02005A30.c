/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#define DTCM ((char *)&data_027e0000)

#define OSi_IrqCheckFlags (*(volatile u32 *)(DTCM + 0x3ff8))

typedef void (*OSIrqFunction)(void *arg);

typedef struct {
    OSIrqFunction pfnHandler;
    volatile u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern void OS_DisableIrqMask(u32 mask);

extern OSiIrqSlot data_020cbc5c[];

extern u16 data_020c5ca8[];

extern u32 data_027e0000;

void OSi_IrqCallback(u32 slot)
{
    u32 mask = 1 << data_020c5ca8[slot];
    OSIrqFunction handler = data_020cbc5c[slot].pfnHandler;

    
    data_020cbc5c[slot].pfnHandler = 0;
    if (handler != 0) {
        handler(data_020cbc5c[slot].pArg);
    }

    {
        u32 flags = OSi_IrqCheckFlags | mask;
        u32 keep = data_020cbc5c[slot].bKeepEnabled;

        OSi_IrqCheckFlags = flags;

        if (keep == 0) {
            OS_DisableIrqMask(mask);
        }
    }
}
