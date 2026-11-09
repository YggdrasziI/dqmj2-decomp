/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nitro/gx.h"

#include "nnsys/g3d.h"

fx32 func_0200235c(fx32 numer, fx32 denom);

void * NNS_G3dGetResDataByName(const NNSG3dResDict * dict, const NNSG3dResName * name);

inline NNSG3dResDictTexData * NNS_G3dGetTexDataByName(const NNSG3dResTex * tex, const NNSG3dResName * name);

inline u32 NNS_GfdGetTexKeyAddr (NNSGfdTexKey memKey)
{
    return (u32)(((0x0000FFFF & memKey)) << 3 );
}

inline NNSG3dResDictTexData * NNS_G3dGetTexDataByName (const NNSG3dResTex * tex, const NNSG3dResName * name)
{
    if (tex)
        return (NNSG3dResDictTexData *)NNS_G3dGetResDataByName(&tex->dict, name);
    else
        return NULL ;
}

void SetTexParamaters_ (const NNSG3dResTex * pTex, const NNSG3dResName * pTexName, NNSG3dMatAnmResult * pResult)
{
    {

        const NNSG3dResDictTexData * pData = NNS_G3dGetTexDataByName(pTex, pTexName);

        {
            const u32 vramOffset = ((pData->texImageParam & REG_G3_TEXIMAGE_PARAM_TEXFMT_MASK) !=
                                    (GX_TEXFMT_COMP4x4 << REG_G3_TEXIMAGE_PARAM_TEXFMT_SHIFT)) ?
                                   NNS_GfdGetTexKeyAddr(pTex->texInfo.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT :
                                   NNS_GfdGetTexKeyAddr(pTex->tex4x4Info.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT;

            pResult->prmTexImage &= REG_G3_TEXIMAGE_PARAM_TGEN_MASK |
                                    REG_G3_TEXIMAGE_PARAM_FT_MASK | REG_G3_TEXIMAGE_PARAM_FS_MASK |
                                    REG_G3_TEXIMAGE_PARAM_RT_MASK | REG_G3_TEXIMAGE_PARAM_RS_MASK;
            pResult->prmTexImage |= pData->texImageParam + vramOffset;

            pResult->origWidth = (u16)((pData->extraParam & NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_MASK) >>
                                       NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_SHIFT);
            pResult->origHeight = (u16)((pData->extraParam & NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_MASK) >>
                                        NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_SHIFT);

            {
                const s32 w = (s32)(((pData->extraParam) & NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_MASK) >> NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_SHIFT);
                const s32 h = (s32)(((pData->extraParam) & NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_MASK) >> NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_SHIFT);

                pResult->magW = (w != pResult->origWidth) ?
                                func_0200235c(w << FX32_SHIFT, pResult->origWidth << FX32_SHIFT) :
                                FX32_ONE;
                pResult->magH = (h != pResult->origHeight) ?
                                func_0200235c(h << FX32_SHIFT, pResult->origHeight << FX32_SHIFT) :
                                FX32_ONE;
            }
        }
    }
}
