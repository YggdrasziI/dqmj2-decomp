/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/hw.h"

void OS_SetArenaHi(int i, int v){ *(int *)(0x27ff000 + (i << 2) + 3524) = v; }

void OS_SetArenaLo(int i, int v){ *(int *)(0x27ff000 + (i << 2) + 3488) = v; }

asm u32 OS_GetDTCMAddress (void)
{
    mrc p15, 0, r0, c9, c1, 0
    ldr r1, = OSi_TCM_REGION_BASE_MASK
    and r0, r0, r1
    bx lr
}

asm void OS_EnableProtectionUnit (void)
{
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #HW_C1_PROTECT_UNIT_ENABLE
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm void OS_DisableProtectionUnit (void)
{
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #HW_C1_PROTECT_UNIT_ENABLE
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm void OS_SetDPermissionsForProtectionRegion (register u32 setMask, register u32 flags)
{
    mrc p15, 0, r2, c5, c0, 2
    bic r2, r2, r0
    orr r2, r2, r1
    mcr p15, 0, r2, c5, c0, 2
    bx lr
}
