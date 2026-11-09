/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/hw.h"

typedef unsigned int OSIntrMode;

asm OSIntrMode OS_DisableInterrupts_IrqAndFiq (void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_IRQ_FIQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_FIQ_DISABLE
    bx lr
}
