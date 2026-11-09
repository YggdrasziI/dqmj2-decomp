/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

typedef struct {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

extern fx32 func_0200235c(fx32 numerator, fx32 denominator);

extern fx64c FX_GetDivResultFx64c(void);

extern fx64c func_02025b70(fx64c numerator, fx64c denom);

extern fx32 FX_GetDivResult(void);

static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline fx32 RoundFx64cToFx32(u64 v)
{
    return (fx32)((v + 0x80000000ULL) >> 32);
}

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((fx64c)a * b + 0x800) >> 12);
}

void Camera_BuildProjectionMtx(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 near, fx32 far,
                   fx32 scaleW, MtxFx44 *mtx)
{
    fx64c recipDepth;
    fx32 fovCot;

    fovCot = func_0200235c(fovyCos, fovySin);
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(near - far));
    if (scaleW != 0x1000)
        fovCot = (fovCot * scaleW) / 0x1000;

    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_11 = fovCot;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = -scaleW;
    mtx->_30 = 0;
    mtx->_31 = 0;
    mtx->_33 = 0;

    recipDepth = FX_GetDivResultFx64c();
    CP_SetDivImm64_64_NS_((u64)fovCot << 32, (u64)(u32)aspect);
    if (scaleW != 0x1000)
        recipDepth = func_02025b70(recipDepth * scaleW, 0x1000);

    mtx->_22 = RoundFx64cToFx32((u64)(recipDepth * (far + near)));
    mtx->_32 = RoundFx64cToFx32((u64)(recipDepth * FX_Mul(near * 2, far)));
    mtx->_00 = FX_GetDivResult();
}
