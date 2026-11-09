/* NitroSDK; built from twewy (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include <nitro/fx/fx_division.h>

#include <nitro/fx/fx_vector.h>

void Vec_Add(const Vec* a, const Vec* b, Vec* dest);

void Vec_Sub(const Vec* a, const Vec* b, Vec* dest);

s32 Vec_DotProduct(const Vec* a, const Vec* b);

void Vec_CrossProduct(const Vec* a, const Vec* b, Vec* dest);

s32 Vec_Magnitude(const Vec* v);

void Vec_MultAdd(s32 a, const Vec* v1, const Vec* v2, Vec* pDest);

s32 Vec_Distance(const Vec* v1, const Vec* v2);

void Vec_Normalize(const Vec* src, Vec* dest) {
    s64 temp = (s64)src->x * src->x;
    temp += (s64)src->y * src->y;
    temp += (s64)src->z * src->z;

    REG_DIV_CNT = 2;
    SetDiv_Numer64Denom64(1LL << 56, temp);

    REG_SQRT_CNT   = 1;
    REG_SQRT_PARAM = (temp << 2);

    while (REG_SQRT_CNT & 0x8000) {
    }
    s32 sqrt = REG_SQRT_RESULT;

    while (REG_DIV_CNT & 0x8000) {
    }
    s64 div = REG_DIV_RESULT;

    div *= sqrt;

    dest->x = (div * src->x + (1LL << 44)) >> 45;
    dest->y = (div * src->y + (1LL << 44)) >> 45;
    dest->z = (div * src->z + (1LL << 44)) >> 45;
}
