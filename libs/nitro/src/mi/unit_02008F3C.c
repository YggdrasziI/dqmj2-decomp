/* NitroSDK; built from twewy (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include <nitro/mi/cpumem.h>

asm void MI_CpuFillU16(register u16 value, register u16* dest, register u32 count);

asm void MI_CpuCopyU16(register const u16* src, register u16* dest, register u32 count);

asm void MI_CpuFillU32(register u32 value, register u32* dest, register u32 count);

asm void MI_CpuCopyU32(register const u32* src, register u32* dest, register u32 count);

asm void MI_CpuFillFromSrc(register const u32* src, register u32* dest, register u32 count);

asm void MI_CpuFill(register u32 value, register void* dest, register u32 count);

asm void MI_CpuCopy(register const u32* src, register u32* dest, register u32 count);

asm void MI_CpuCopy36(register const u32* src, register u32* dest);

asm void MI_CpuCopy48(register const u32* src, register u32* dest);

asm void MI_CpuCopy64(register const u32* src, register u32* dest);

asm void MI_CpuSet(register void* dest, register u8 value, register u32 count);

asm void MI_CpuCopyU8(register const void* src, register void* dest, register u32 count);

asm u32 MI_CpuSwap(register u32 value, register u32* addr);

#pragma thumb on
asm void MI_CpuClear24(register u32* dest) {
    mov    r1, #0x0
    mov    r2, #0x0
    mov    r3, #0x0
    stmia     r0!, {r1, r2, r3}
    stmia     r0!, {r1, r2, r3}
    stmia     r0!, {r1, r2, r3}
    bx      lr
}
#pragma thumb off
