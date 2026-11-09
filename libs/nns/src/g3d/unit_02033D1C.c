/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

typedef enum {
    GX_TEXGEN_NONE        = 0,
    GX_TEXGEN_TEXCOORD    = 1,
    GX_TEXGEN_NORMAL      = 2,
    GX_TEXGEN_VERTEX      = 3
} GXTexGen;

extern s32 FX_Whole(fx32 v);

extern void GetTexSRTAnm_ (const NNSG3dResTexSRTAnm * pTexAnm, u16 idx, u32 frame, NNSG3dMatAnmResult * pResult);

static inline s32 FX_Whole (fx32 v)
    {
        return (s32)(v >> 12 );
    }

void NNSi_G3dAnmCalcNsBta (NNSG3dMatAnmResult * pResult, const NNSG3dAnmObj * pAnmObj, u32 dataIdx)
{

    {
        const NNSG3dResTexSRTAnm * pTexAnm
            = (const NNSG3dResTexSRTAnm *)pAnmObj->resAnm;

        GetTexSRTAnm_(pTexAnm,
                      (u16)dataIdx,
                      (u32)FX_Whole(pAnmObj->frame),
                      pResult);

        pResult->prmTexImage &= ~REG_G3_TEXIMAGE_PARAM_TGEN_MASK;
        pResult->prmTexImage |= GX_TEXGEN_TEXCOORD << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT;

        pResult->flag |= NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SET;

    }
}
