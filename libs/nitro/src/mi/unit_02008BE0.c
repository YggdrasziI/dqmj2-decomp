/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

asm void MIi_CpuClear16(register u16 value, register void *destination,
                        register u32 size)
{
    mov     r3, #0
clearNextHalfword:
    cmp     r3, r2
    strlth  r0, [r1, r3]
    addlt   r3, r3, #2
    blt     clearNextHalfword
    bx      lr
}
