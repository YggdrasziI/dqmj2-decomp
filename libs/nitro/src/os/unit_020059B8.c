/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define DTCM ((char *)&data_027e0000)

extern OSIntrMode OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(OSIntrMode state);

extern void OS_SleepThread(void *queue);

extern u32 data_027e0000;

extern u32 data_027e0060;

void OS_WaitIrq(BOOL clear, u32 irqFlags)
{
    OSIntrMode last = OS_DisableInterrupts();

    if (clear) {
        OSi_IrqCheckFlags &= ~irqFlags;
    }
    OS_RestoreInterrupts(last);

    
    {
        char *const dtcm = DTCM;

        if (irqFlags & *(volatile u32 *)(dtcm + 0x3ff8)) {
            return;
        }
        {
            volatile u32 *flags = (volatile u32 *)(dtcm + 0x3ff8);

            do {
                OS_SleepThread(&data_027e0060);
            } while ((irqFlags & *flags) == 0);
        }
    }
}
