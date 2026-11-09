/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

asm void MIi_CpuCopy16(register const void *source,
                       register void *destination, register u32 size)
{
    mov     ip, #0
copyNextHalfword:
    cmp     ip, r2
    ldrlth  r3, [r0, ip]
    strlth  r3, [r1, ip]
    addlt   ip, ip, #2
    blt     copyNextHalfword
    bx      lr
}
