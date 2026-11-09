/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/hw.h"

asm void DC_FlushAll (void)
{
    mov r12, #0
    mov r1, #0
@1:
    mov r0, #0
@2:
    orr r2, r1, r0
    mcr p15, 0, r12, c7, c10, 4
    mcr p15, 0, r2, c7, c14, 2
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, #HW_DCACHE_SIZE / 4
    blt @2
    add r1, r1, #1 << HW_C7_CACHE_SET_NO_SHIFT
    cmp r1, #0
    bne @1
    bx lr
}
