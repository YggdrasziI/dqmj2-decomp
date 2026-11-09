/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

typedef int PXIFifoTag;

extern OSIntrMode OS_DisableInterrupts(void);

extern void SNDi_CallAlarmHandler(int data);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err)
{
    OSIntrMode enabled;
    (void)tag;
    (void)err;
    enabled = OS_DisableInterrupts();
    SNDi_CallAlarmHandler((int)data);
    (void)OS_RestoreInterrupts(enabled);
}
