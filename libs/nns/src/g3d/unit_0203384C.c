/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/g3d.h"

extern s32 FX_Whole(fx32 v);

inline void * NNS_G3dGetResDataByIdx(const NNSG3dResDict * dict, u32 idx);

extern u16 func_02033524 (const NNSG3dResMatCAnm * pAnm, u32 info, u32 frame);

extern u16 GetMatColAnmuAlphaValue_ (const NNSG3dResMatCAnm * pAnm, u32 info, u32 frame);

extern fx32 GetTexSRTAnmVectorVal_ (const NNSG3dResTexSRTAnm * pTexAnm, u32 info, u32 data, u32 frame);

extern u32 GetTexSRTAnmSinCosVal_ (const NNSG3dResTexSRTAnm * pTexAnm, u32 info, u32 data, u32 frame);

static inline s32 FX_Whole (fx32 v)
    {
        return (s32)(v >> 12 );
    }

inline void * NNS_G3dGetResDataByIdx (const NNSG3dResDict * dict, u32 idx)
{
    NNSG3dResDictEntryHeader * hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL ;
    }
}

static inline void GetMatColAnm_ (const NNSG3dResMatCAnm * pAnm, u16 idx, u32 frame, NNSG3dMatAnmResult * pResult)
{
    {
        u16 diffuse, ambient, emission, specular, polygon_alpha;
        const NNSG3dResDictMatCAnmData * pAnmData =
            (const NNSG3dResDictMatCAnmData *)NNS_G3dGetResDataByIdx(&pAnm->dict, idx);
        diffuse = func_02033524(pAnm, pAnmData->diffuse, frame);
        ambient = func_02033524(pAnm, pAnmData->ambient, frame);
        pResult->prmMatColor0 = ((u32)((diffuse) | (( ambient) << 16) | ((( (pResult->prmMatColor0 & 0x00008000)) != 0) << 15)))
                                                      ;
        emission = func_02033524(pAnm, pAnmData->emission, frame);
        specular = func_02033524(pAnm, pAnmData->specular, frame);
        pResult->prmMatColor1 = ((u32)((specular) | (( emission) << 16) | ((( (pResult->prmMatColor1 & 0x00008000)) != 0) << 15)))
                                                      ;
        polygon_alpha = GetMatColAnmuAlphaValue_(pAnm, pAnmData->polygon_alpha, frame);
        pResult->prmPolygonAttr = (pResult->prmPolygonAttr & ~0x001f0000 ) |
                                  (polygon_alpha << 16 );
    }
}

void NNSi_G3dAnmCalcNsBma (NNSG3dMatAnmResult * pResult, const NNSG3dAnmObj * pAnmObj, u32 dataIdx)
{
    {
        const NNSG3dResMatCAnm * pMatAnm = (const NNSG3dResMatCAnm *)pAnmObj->resAnm;
        GetMatColAnm_(pMatAnm,
                      (u16)dataIdx,
                      (u32)FX_Whole(pAnmObj->frame),
                      pResult);
    }
}

fx32 GetTexSRTAnmVectorVal_ (const NNSG3dResTexSRTAnm * pTexAnm, u32 info, u32 data, u32 frame)
{
    u32 idx, idx_sub;
    u32 last_interp;
    const void * pDataHead;

    if (info & NNS_G3D_TEXSRTANM_ELEM_CONST) {
        return (fx32)data;
    }

    pDataHead = (const void *)((u8 *)pTexAnm + data);

    if (!(info & NNS_G3D_TEXSRTANM_ELEM_STEP_MASK)) {
        idx = frame;
        goto TEXSRT_VAL_NONINTERP;
    }

    last_interp = (NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_MASK & info) >>
                  NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_SHIFT;

    if (info & NNS_G3D_TEXSRTANM_ELEM_STEP_2) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto TEXSRT_VAL_NONINTERP;
            } else {
                idx = frame >> 1;
                goto TEXSRT_VAL_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto TEXSRT_VAL_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto TEXSRT_VAL_NONINTERP;
            }

            if (frame & 1) {
                fx32 v, v_sub;
                if (frame & 2) {
                    idx_sub = (frame >> 2);
                    idx = idx_sub + 1;
                } else {
                    idx = (frame >> 2);
                    idx_sub = idx + 1;
                }

                if (info & NNS_G3D_TEXSRTANM_ELEM_FX16) {
                    v = *((const fx16 *)pDataHead + idx);
                    v_sub = *((const fx16 *)pDataHead + idx_sub);
                } else {
                    v = *((const fx32 *)pDataHead + idx);
                    v_sub = *((const fx32 *)pDataHead + idx_sub);
                }
                return (v + v + v + v_sub) >> 2;
            } else {
                idx = frame >> 2;
                goto TEXSRT_VAL_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto TEXSRT_VAL_NONINTERP;
        }
    }
TEXSRT_VAL_NONINTERP:
    if (info & NNS_G3D_TEXSRTANM_ELEM_FX16) {
        return *((const fx16 *)pDataHead + idx);
    } else {
        return *((const fx32 *)pDataHead + idx);
    }
TEXSRT_VAL_INTERP_2:
    {
        fx32 v0, v1;
        if (info & NNS_G3D_TEXSRTANM_ELEM_FX16) {
            v0 = *((const fx16 *)pDataHead + idx);
            v1 = *((const fx16 *)pDataHead + idx + 1);
        } else {
            v0 = *((const fx32 *)pDataHead + idx);
            v1 = *((const fx32 *)pDataHead + idx + 1);
        }
        return ((v0 + v1) >> 1);
    }
}

u32 GetTexSRTAnmSinCosVal_ (const NNSG3dResTexSRTAnm * pTexAnm, u32 info, u32 data, u32 frame)
{
    u32 idx, idx_sub;
    u32 last_interp;
    const void * pDataHead;

    if (info & NNS_G3D_TEXSRTANM_ELEM_CONST) {
        return data;
    }

    pDataHead = (const void *)((u8 *)pTexAnm + data);

    if (!(info & NNS_G3D_TEXSRTANM_ELEM_STEP_MASK)) {
        idx = frame;
        goto TEXSRT_SINCOS_NONINTERP;
    }

    last_interp = (NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_MASK & info) >>
                  NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_SHIFT;

    if (info & NNS_G3D_TEXSRTANM_ELEM_STEP_2) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto TEXSRT_SINCOS_NONINTERP;
            } else {
                idx = frame >> 1;
                goto TEXSRT_SINCOS_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto TEXSRT_SINCOS_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto TEXSRT_SINCOS_NONINTERP;
            }

            if (frame & 1) {
                fx32 s, s_sub;
                fx32 c, c_sub;

                if (frame & 2) {
                    idx_sub = (frame >> 2);
                    idx = idx_sub + 1;
                } else {
                    idx = (frame >> 2);
                    idx_sub = idx + 1;
                }

                s = *((const fx16 *)((const u32 *)pDataHead + idx));
                c = *((const fx16 *)((const u32 *)pDataHead + idx) + 1);
                s_sub = *((const fx16 *)((const u32 *)pDataHead + idx_sub));
                c_sub = *((const fx16 *)((const u32 *)pDataHead + idx_sub) + 1);

                s = (s + s + s + s_sub) >> 2;
                c = (c + c + c + c_sub) >> 2;
                return (u32)((s & 0xffff) | (c << 16));
            } else {
                idx = frame >> 2;
                goto TEXSRT_SINCOS_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto TEXSRT_SINCOS_NONINTERP;
        }
    }
TEXSRT_SINCOS_NONINTERP:
    return *((const u32 *)pDataHead + idx);
TEXSRT_SINCOS_INTERP_2:
    {
        fx32 s0, s1;
        fx32 c0, c1;
        s0 = *((const fx16 *)((const u32 *)pDataHead + idx));
        c0 = *((const fx16 *)pDataHead + 2 * idx + 1);

        s1 = *((const fx16 *)pDataHead + 2 * idx + 2);
        c1 = *((const fx16 *)pDataHead + 2 * idx + 3);

        return (u32)((((s0 + s1) >> 1) & 0xffff) | (((c0 + c1) >> 1) << 16));
    }
}

void GetTexSRTAnm_ (const NNSG3dResTexSRTAnm * pTexAnm, u16 idx, u32 frame, NNSG3dMatAnmResult * pResult)
{

    {
        const NNSG3dResDictTexSRTAnmData * pAnmData =
            (const NNSG3dResDictTexSRTAnmData *)NNS_G3dGetResDataByIdx(&pTexAnm->dict, idx);
        NNSG3dMatAnmResultFlag flag = pResult->flag;

        {
            fx32 transS, transT;

            transS = GetTexSRTAnmVectorVal_(pTexAnm,
                                            pAnmData->transS,
                                            pAnmData->transSEx,
                                            frame);
            transT = GetTexSRTAnmVectorVal_(pTexAnm,
                                            pAnmData->transT,
                                            pAnmData->transTEx,
                                            frame);

            if (transS == 0 && transT == 0) {
                flag |= NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO;
            } else {
                flag &= ~NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO;
                pResult->transS = transS;
                pResult->transT = transT;
            }
        }

        {

            u32 data = GetTexSRTAnmSinCosVal_(pTexAnm,
                                              pAnmData->rot,
                                              pAnmData->rotEx,
                                              frame);

            if (data == ((FX32_ONE << 16) | 0)) {
                flag |= NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO;
            } else {
                pResult->sinR = (fx16)(data & 0x0000FFFF);
                pResult->cosR = (fx16)(data >> 16);
                flag &= ~NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO;
            }
        }

        {
            fx32 scaleS, scaleT;

            scaleS = GetTexSRTAnmVectorVal_(pTexAnm,
                                            pAnmData->scaleS,
                                            pAnmData->scaleSEx,
                                            frame);
            scaleT = GetTexSRTAnmVectorVal_(pTexAnm,
                                            pAnmData->scaleT,
                                            pAnmData->scaleTEx,
                                            frame);

            if (scaleS == FX32_ONE && scaleT == FX32_ONE) {
                flag |= NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE;
            } else {
                flag &= ~NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE;
                pResult->scaleS = scaleS;
                pResult->scaleT = scaleT;
            }
        }

        pResult->flag = flag;
    }
}
