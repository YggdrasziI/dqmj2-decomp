/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/os_types.h"

extern OSIntrMode OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(OSIntrMode state);

extern void OSi_RescheduleThread(void);

void OS_RescheduleThread(void)
{
    OSIntrMode nLast = OS_DisableInterrupts();

    OSi_RescheduleThread();
    OS_RestoreInterrupts(nLast);
}
