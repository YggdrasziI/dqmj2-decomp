/* NitroSDK; built from twewy (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include <nitro/fx/fx_division.h>

#include <nitro/fx/fx_matrix.h>

#ifdef REGION_USA

#endif

asm void Mtx_Identity33(register Mtx33* matrix);

void Mtx_Scale33(const Mtx33* src, Mtx33* dest, s32 scaleX, s32 scaleY, s32 scaleZ);

asm void Mtx_Identity43(register Mtx43* matrix);

asm void Mtx_Copy43To44(register const Mtx43* src, register Mtx44* dest);

void Mtx_Scale43(const Mtx43* src, Mtx43* dest, s32 scaleX, s32 scaleY, s32 scaleZ);

s32 MTX_Inverse43(const Mtx43* src, Mtx43* dest);

void Mtx_Concat43(const Mtx43* a, const Mtx43* b, Mtx43* dest);

void Mtx_LookAt(const Vec* camPosition, const Vec* upDirection, const Vec* targetPosition, Mtx43* matrix);

asm void Mtx_Identity44(register Mtx44* matrix);

asm void Mtx_Copy44To43(register const Mtx44* src, register Mtx43* dest);

void Mtx_Concat44(const Mtx44* a, const Mtx44* b, Mtx44* dest);

void Mtx_OrthoW(s32 top, s32 bottom, s32 left, s32 right, s32 near, s32 far, s32 scale, Mtx44* mtx);

static inline s32 FX_Mul_32x64(s32 a, s64 b) {
    s64 temp = b * a + 0x80000000LL;
    return temp >> 32;
}

#pragma thumb on
asm void Mtx_YRot33(register Mtx33* matrix, register s32 sin, register s32 cos) {
    str     cos, [matrix, #0]
    str     cos, [matrix, #0x20]
    mov     r3, #0
    str     r3, [matrix, #0x4]
    str     r3, [matrix, #0xC]
    str     r3, [matrix, #0x14]
    str     r3, [matrix, #0x1C]
    neg     cos, sin
    mov     r3, #1
    lsl     r3, r3, #0xC
    str     sin, [matrix, #0x18]
    str     cos, [matrix, #0x8]
    str     r3, [matrix, #0x10]
    bx      lr
}
#pragma thumb off
