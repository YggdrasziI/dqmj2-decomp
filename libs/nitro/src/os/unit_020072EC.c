/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/hw.h"

asm void DC_StoreRange (register const void * startAddr, register u32 nBytes)
{
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r0, c7, c10, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}
