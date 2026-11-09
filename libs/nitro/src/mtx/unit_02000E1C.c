/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/fx_types.h"

#include "nitro/fx.h"

extern void MTX_ScaleApply33(const int *src, int *dst, int sx, int sy, int sz);

extern void FX_InvAsync(fx32 x);

extern fx32 FX_GetDivResult(void);

extern void MI_Copy48B(const void *src, void *dst);

extern void Vec_Normalize(const VecFx32 *src, VecFx32 *dst);

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab)
{
    MtxFx33 tmp;
    MtxFx33 *p;
    register fx32 x, y, z;
    register fx32 xx, yy, zz;

    if (ab == b) {
        p = &tmp;
    } else {
        p = ab;
    }

    x = a->_00;
    y = a->_01;
    z = a->_02;
    p->_00 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> 12);
    p->_01 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    xx = b->_02;
    yy = b->_12;
    zz = b->_22;
    p->_02 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_10;
    y = a->_11;
    z = a->_12;
    p->_12 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_11 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    xx = b->_00;
    yy = b->_10;
    zz = b->_20;
    p->_10 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_20;
    y = a->_21;
    z = a->_22;
    p->_20 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_21 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    p->_22 = (fx32)(((fx64)x * b->_02 + (fx64)y * b->_12 + (fx64)z * b->_22) >> 12);

    if (p == &tmp) {
        *ab = tmp;
    }
}

void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst)
{
    register fx32 x, y, z;

    x = vec->x;
    y = vec->y;
    z = vec->z;

    dst->x = (fx32)(((fx64)x * m->_00 + (fx64)y * m->_10 + (fx64)z * m->_20) >> 12);
    dst->y = (fx32)(((fx64)x * m->_01 + (fx64)y * m->_11 + (fx64)z * m->_21) >> 12);
    dst->z = (fx32)(((fx64)x * m->_02 + (fx64)y * m->_12 + (fx64)z * m->_22) >> 12);
}

asm void MTX_Identity43_(int *p)
{
    mov r2, #0x1000
    mov r3, #0
    stmia r0!, {r2, r3}
    mov r1, #0
    stmia r0!, {r1, r3}
    stmia r0!, {r2, r3}
    stmia r0!, {r1, r3}
    stmia r0!, {r2, r3}
    stmia r0!, {r1, r3}
    bx lr
}

asm void MTX_Copy43To44_(void *src, void *dst)
{
    stmdb sp!, {r4}
    mov ip, #0
    ldmia r0!, {r2, r3, r4}
    stmia r1!, {r2, r3, r4, ip}
    ldmia r0!, {r2, r3, r4}
    stmia r1!, {r2, r3, r4, ip}
    ldmia r0!, {r2, r3, r4}
    stmia r1!, {r2, r3, r4, ip}
    mov ip, #0x1000
    ldmia r0!, {r2, r3, r4}
    stmia r1!, {r2, r3, r4, ip}
    ldmia sp!, {r4}
    bx lr
}

void MTX_ScaleApply43(const int *src, int *dst, int sx, int sy, int sz) {
    MTX_ScaleApply33(src, dst, sx, sy, sz);
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
}

int MTX_Inverse43(const MtxFx43 *src, MtxFx43 *dst)
{
    MtxFx43 tmp;
    MtxFx43 *p;
    fx32 det;
    fx32 det00, det10, det20;
    fx32 tmp01, tmp02, tmp11, tmp12;
    fx32 tmp21, tmp22;

    if (src == dst) {
        p = &tmp;
    } else {
        p = dst;
    }

    det00 = (fx32)(((fx64)src->_11 * src->_22 -
                    (fx64)src->_12 * src->_21 + (fx64)(0x1000 >> 1)) >> 12);

    det10 = (fx32)(((fx64)src->_10 * src->_22 -
                    (fx64)src->_12 * src->_20 + (fx64)(0x1000 >> 1)) >> 12);

    det20 = (fx32)(((fx64)src->_10 * src->_21 -
                    (fx64)src->_11 * src->_20 + (fx64)(0x1000 >> 1)) >> 12);

    det = (fx32)(((fx64)src->_00 * det00 -
                  (fx64)src->_01 * det10 +
                  (fx64)src->_02 * det20 + (fx64)(0x1000 >> 1)) >> 12);

    if (0 == det) {
        return -1;
    }

    FX_InvAsync(det);

    tmp01 = (fx32)(((fx64)src->_01 * src->_22 - (fx64)src->_21 * src->_02) >> 12);
    tmp02 = (fx32)(((fx64)src->_01 * src->_12 - (fx64)src->_11 * src->_02) >> 12);
    tmp11 = (fx32)(((fx64)src->_00 * src->_22 - (fx64)src->_20 * src->_02) >> 12);
    tmp12 = (fx32)(((fx64)src->_00 * src->_12 - (fx64)src->_10 * src->_02) >> 12);

    det = FX_GetDivResult();
    p->_00 = (fx32)(((fx64)det * det00) >> 12);
    p->_01 = -(fx32)(((fx64)det * tmp01) >> 12);
    p->_02 = (fx32)(((fx64)det * tmp02) >> 12);

    p->_10 = -(fx32)(((fx64)det * det10) >> 12);
    p->_11 = (fx32)(((fx64)det * tmp11) >> 12);
    p->_12 = -(fx32)(((fx64)det * tmp12) >> 12);

    p->_20 = (fx32)(((fx64)det * det20) >> 12);

    tmp21 = (fx32)(((fx64)src->_00 * src->_21 - (fx64)src->_20 * src->_01) >> 12);
    p->_21 = -(fx32)(((fx64)det * tmp21) >> 12);

    tmp22 = (fx32)(((fx64)src->_00 * src->_11 - (fx64)src->_10 * src->_01) >> 12);
    p->_22 = (fx32)(((fx64)det * tmp22) >> 12);

    p->_30 = -(fx32)(((fx64)p->_00 * src->_30 +
                      (fx64)p->_10 * src->_31 + (fx64)p->_20 * src->_32) >> 12);

    p->_31 = -(fx32)(((fx64)p->_01 * src->_30 +
                      (fx64)p->_11 * src->_31 + (fx64)p->_21 * src->_32) >> 12);

    p->_32 = -(fx32)(((fx64)p->_02 * src->_30 +
                      (fx64)p->_12 * src->_31 + (fx64)p->_22 * src->_32) >> 12);

    if (p == &tmp) {
        MI_Copy48B(&tmp, dst);
    }

    return 0;
}

void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab)
{
    MtxFx43 tmp;
    MtxFx43 *p;

    register fx32 x, y, z;
    register fx32 xx, yy, zz;

    if (ab == b) {
        p = &tmp;
    } else {
        p = ab;
    }

    x = a->_00;
    y = a->_01;
    z = a->_02;

    p->_00 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> 12);
    p->_01 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);

    xx = b->_02;
    yy = b->_12;
    zz = b->_22;

    p->_02 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_10;
    y = a->_11;
    z = a->_12;

    p->_12 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_11 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);

    xx = b->_00;
    yy = b->_10;
    zz = b->_20;

    p->_10 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_20;
    y = a->_21;
    z = a->_22;

    p->_20 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_21 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    xx = b->_02;
    yy = b->_12;
    zz = b->_22;

    p->_22 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_30;
    y = a->_31;
    z = a->_32;

    p->_32 = (fx32)((((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12) + b->_32);
    p->_31 = (fx32)((((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12) + b->_31);
    p->_30 = (fx32)((((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> 12) + b->_30);

    if (p == &tmp) {
        *ab = tmp;
    }
}

void MTX_MultVec43(const VecFx32 *vec, const MtxFx43 *m, VecFx32 *dst)
{
    register fx32 x, y, z;

    x = vec->x;
    y = vec->y;
    z = vec->z;

    dst->x = (fx32)(((fx64)x * m->_00 + (fx64)y * m->_10 + (fx64)z * m->_20) >> 12);
    dst->x += m->_30;

    dst->y = (fx32)(((fx64)x * m->_01 + (fx64)y * m->_11 + (fx64)z * m->_21) >> 12);
    dst->y += m->_31;

    dst->z = (fx32)(((fx64)x * m->_02 + (fx64)y * m->_12 + (fx64)z * m->_22) >> 12);
    dst->z += m->_32;
}

void MTX_LookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx)
{
    VecFx32 vLook, vRight, vUp;

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;

    Vec_Normalize(&vLook, &vLook);
    VEC_CrossProduct(camUp, &vLook, &vRight);
    Vec_Normalize(&vRight, &vRight);
    VEC_CrossProduct(&vLook, &vRight, &vUp);

    mtx->_00 = vRight.x;
    mtx->_01 = vUp.x;
    mtx->_02 = vLook.x;
    mtx->_10 = vRight.y;
    mtx->_11 = vUp.y;
    mtx->_12 = vLook.y;
    mtx->_20 = vRight.z;
    mtx->_21 = vUp.z;
    mtx->_22 = vLook.z;
    mtx->_30 = -VEC_DotProduct(camPos, &vRight);
    mtx->_31 = -VEC_DotProduct(camPos, &vUp);
    mtx->_32 = -VEC_DotProduct(camPos, &vLook);
}

asm void MTX_Identity44_(int *mtx)
{
    mov r2, #0x1000
    mov r3, #0
    stmia r0!, {r2, r3}
    mov r1, #0
    stmia r0!, {r1, r3}
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r3}
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r3}
    stmia r0!, {r1, r2}
    bx lr
}

asm void MTX_Copy44To43_(void *src, void *dst)
{
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    bx lr
}
