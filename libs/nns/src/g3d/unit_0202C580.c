/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

typedef struct {
    char pad00[0x20];
    s16 sinR;           
    s16 cosR;           
    fx32 transS;        
    fx32 transT;        
    u16 width;          
    u16 height;         
} TexSRTAnm;

typedef struct {
    char pad0[0x20];
    s16 sinR;       
    s16 cosR;       
    char pad24[0x2c - 0x24];
    u16 origW;      
    u16 origH;      
} TexRotAnm;

typedef struct {
    fx32 m00;
    fx32 m01;
    char pad08[0x10 - 0x08];
    fx32 m10;
    fx32 m11;
    char pad18[0x30 - 0x18];
    fx32 m30;
    fx32 m31;
} TexMtxView;

void FX_DivAsync(fx32 numer, fx32 denom);

fx32 FX_GetDivResult(void);

extern void FX_DivAsync(fx32 numer, fx32 denom);

extern fx32 FX_GetDivResult(void);

extern void FX_DivAsync(fx32 num, fx32 denom);

static inline fx32 FxOneMinus(fx32 x)
{
    x = -x;
    return x + 0x1000;
}

void texmtxCalc_flag_ (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 ss_sin, ss_cos;
    fx32 st_sin, st_cos;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    ss_sin = (fx32)((fx64)anm->scaleS * anm->sinR >> FX32_SHIFT);
    ss_cos = (fx32)((fx64)anm->scaleS * anm->cosR >> FX32_SHIFT);
    st_sin = (fx32)((fx64)anm->scaleT * anm->sinR >> FX32_SHIFT);
    st_cos = (fx32)((fx64)anm->scaleT * anm->cosR >> FX32_SHIFT);

    m->_00 = ss_cos;
    m->_11 = st_cos;

    m->_01 = -st_sin * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    m->_30 = ((-ss_sin - ss_cos + anm->scaleS) * anm->origWidth << 3) -
             (fx32)((fx64)anm->scaleS * anm->transS >> (FX32_SHIFT - 4)) * anm->origWidth;

    m->_31 = ((st_sin - st_cos - anm->scaleT + FX32_ONE * 2) * anm->origHeight << 3) +
             (fx32)((fx64)anm->scaleT * anm->transT >> (FX32_SHIFT - 4)) * anm->origHeight;

    m->_10 = ss_sin * FX_GetDivResult() >> FX32_SHIFT;
}

void texmtxCalc_flagS_(MtxFx44 *m, const TexSRTAnm *anm)
{
    fx32 w = anm->width << 12;
    fx32 h = anm->height << 12;

    FX_DivAsync(h, w);
    m->m[0][0] = anm->cosR;
    m->m[1][1] = anm->cosR;
    m->m[0][1] = (-anm->sinR * FX_GetDivResult()) >> 12;
    FX_DivAsync(w, h);
    m->m[3][0] = (FxOneMinus(anm->sinR + anm->cosR) * anm->width << 3) - ((anm->transS * anm->width) << 4);
    m->m[3][1] = ((anm->sinR - anm->cosR + 0x1000) * anm->height << 3) + ((anm->transT * anm->height) << 4);
    m->m[1][0] = (anm->sinR * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagR_ (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = anm->scaleS;
    m->_11 = anm->scaleT;

    m->_01 = 0;

    m->_30 = -(fx32)((fx64)anm->scaleS * anm->transS >> (FX32_SHIFT - 4)) * anm->origWidth;
    m->_31 = ((-anm->scaleT - anm->scaleT + FX32_ONE * 2) * anm->origHeight << 3) +
             (fx32)((fx64)anm->scaleT * anm->transT >> (FX32_SHIFT - 4)) * anm->origHeight;

    m->_10 = 0;
}

void texmtxCalc_flagRS_ (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = FX32_ONE;
    m->_11 = FX32_ONE;

    m->_01 = 0;

    m->_30 = -(anm->transS * anm->origWidth) << 4;
    m->_31 = (anm->transT * anm->origHeight) << 4;

    m->_10 = 0;
}

void texmtxCalc_flagT_ (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 ss_sin, ss_cos;
    fx32 st_sin, st_cos;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    ss_sin = (fx32)((fx64)anm->scaleS * anm->sinR >> FX32_SHIFT);
    ss_cos = (fx32)((fx64)anm->scaleS * anm->cosR >> FX32_SHIFT);
    st_sin = (fx32)((fx64)anm->scaleT * anm->sinR >> FX32_SHIFT);
    st_cos = (fx32)((fx64)anm->scaleT * anm->cosR >> FX32_SHIFT);

    m->_00 = ss_cos;
    m->_11 = st_cos;

    m->_01 = -st_sin * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    m->_30 = ((-ss_sin - ss_cos + anm->scaleS) * anm->origWidth << 3);
    m->_31 = ((st_sin - st_cos - anm->scaleT + FX32_ONE * 2) * anm->origHeight << 3);

    m->_10 = ss_sin * FX_GetDivResult() >> FX32_SHIFT;
}

void texmtxCalc_flagTS_(TexMtxView *out, TexRotAnm *in)
{
    fx32 a = (fx32)in->origW << 12;
    fx32 b = (fx32)in->origH << 12;

    FX_DivAsync(b, a);
    out->m00 = in->cosR;
    out->m11 = in->cosR;
    out->m01 = (-(fx32)in->sinR * FX_GetDivResult()) >> 12;

    FX_DivAsync(a, b);
    out->m30 = ((fx32)in->origW * ((fx32)(-((fx32)in->sinR + (fx32)in->cosR)) + 0x1000)) << 3;
    out->m31 = ((fx32)in->origH * (((fx32)in->sinR - (fx32)in->cosR) + 0x1000)) << 3;
    out->m10 = ((fx32)in->sinR * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagTR_ (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = anm->scaleS;
    m->_11 = anm->scaleT;

    m->_01 = 0;

    m->_30 = 0;
    m->_31 = ((-2 * anm->scaleT + FX32_ONE * 2) * anm->origHeight << 3);

    m->_10 = 0;
}
