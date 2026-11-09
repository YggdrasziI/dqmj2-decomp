/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

#include "nitro/fx_types.h"

#include "nitro/mi.h"

#include "nitro/pxi.h"

#include "nitro/gx.h"

#include "nitro/os_types.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/wm.h"

typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;

typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);

typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);

fx32 func_0200235c(fx32 numer, fx32 denom);

inline void * NNS_G3dGetResDataByIdx(const NNSG3dResDict * dict, u32 idx);

inline NNSG3dResMatData * NNS_G3dGetMatDataByIdx(const NNSG3dResMat * mat, u32 idx);

inline const NNSG3dResName * NNS_G3dGetResNameByIdx(const NNSG3dResDict * dict, u32 idx);

void * NNS_G3dGetResDataByName(const NNSG3dResDict * dict, const NNSG3dResName * name);

inline NNSG3dResMat * NNS_G3dGetMat(const NNSG3dResMdl * mdl);

inline NNSG3dResDictTexData * NNS_G3dGetTexDataByName(const NNSG3dResTex * tex, const NNSG3dResName * name);

extern void bindMdlTex_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictTexToMatIdxData * pBindData, const NNSG3dResTex * pTex, const NNSG3dResDictTexData * pTexData);

extern void releaseMdlTex_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictTexToMatIdxData * pData);

inline NNSG3dResDictPlttData * NNS_G3dGetPlttDataByName(const NNSG3dResTex * tex, const NNSG3dResName * name);

extern void bindMdlPltt_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictPlttToMatIdxData * pBindData, const NNSG3dResTex * pTex, const NNSG3dResDictPlttData * pPlttData);

BOOL NNS_G3dBindMdlTex(NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex);

BOOL NNS_G3dBindMdlPltt(NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex);

inline NNSG3dResMdl * NNS_G3dGetMdlByIdx(const NNSG3dResMdlSet * mdlSet, u32 idx);

extern BOOL NNS_G3dBindMdlTex (NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex);

extern BOOL NNS_G3dBindMdlPltt (NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex);

void NNS_G3dReleaseMdlTex(NNSG3dResMdl * pMdl);

void NNS_G3dReleaseMdlPltt(NNSG3dResMdl * pMdl);

extern void NNS_G3dReleaseMdlTex (NNSG3dResMdl * pMdl);

extern void NNS_G3dReleaseMdlPltt (NNSG3dResMdl * pMdl);

inline u32 NNS_GfdGetTexKeyAddr (NNSGfdTexKey memKey)
{
    return (u32)(((0x0000FFFF & memKey)) << 3 );
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

inline NNSG3dResMatData * NNS_G3dGetMatDataByIdx (const NNSG3dResMat * mat, u32 idx)
{
    NNSG3dResDictMatData * data;
    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL ;
}

inline const NNSG3dResName * NNS_G3dGetResNameByIdx (const NNSG3dResDict * dict, u32 idx)
{
    NNSG3dResDictEntryHeader * hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (NNSG3dResName *)((u8 *)hdr +
                                 hdr->ofsName +
                                 sizeof(NNSG3dResName) * idx);
    } else {
        return NULL ;
    }
}

inline NNSG3dResMat * NNS_G3dGetMat (const NNSG3dResMdl * mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL ;
}

inline NNSG3dResDictTexData * NNS_G3dGetTexDataByName (const NNSG3dResTex * tex, const NNSG3dResName * name)
{
    if (tex)
        return (NNSG3dResDictTexData *)NNS_G3dGetResDataByName(&tex->dict, name);
    else
        return NULL ;
}

inline NNSG3dResDictPlttData * NNS_G3dGetPlttDataByName (const NNSG3dResTex * tex, const NNSG3dResName * name)
{
    NNSG3dResDict * dict;
    if (tex && tex->plttInfo.ofsDict != 0) {
        dict = (NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict);
        return (NNSG3dResDictPlttData *)NNS_G3dGetResDataByName(dict, name);
    } else {
        return NULL ;
    }
}

inline NNSG3dResMdl * NNS_G3dGetMdlByIdx (const NNSG3dResMdlSet * mdlSet, u32 idx)
{
    NNSG3dResDictMdlSetData * data;
    if (mdlSet) {
        data = (NNSG3dResDictMdlSetData *)NNS_G3dGetResDataByIdx(&mdlSet->dict, idx);
        if (data) {
            return (NNSG3dResMdl *)((u8 *)mdlSet + data->offset);
        }
    }
    return NULL ;
}

NNSG3dPlttKey NNS_G3dPlttReleasePlttKey (NNSG3dResTex * pTex)
{
    u32 rval;

    pTex->plttInfo.flag &= ~NNS_G3D_RESPLTT_LOADED;

    rval = pTex->plttInfo.vramKey;
    pTex->plttInfo.vramKey = 0;

    return rval;
}

void bindMdlTex_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictTexToMatIdxData * pBindData, const NNSG3dResTex * pTex, const NNSG3dResDictTexData * pTexData)
{
    u8 * base = (u8 *)pMat + pBindData->offset;
    u32 vramOffset;
    u32 j;

    if ((pTexData->texImageParam & REG_G3_TEXIMAGE_PARAM_TEXFMT_MASK) !=
        (GX_TEXFMT_COMP4x4 << REG_G3_TEXIMAGE_PARAM_TEXFMT_SHIFT)) {
        vramOffset = NNS_GfdGetTexKeyAddr(pTex->texInfo.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT;
    } else {
        vramOffset = NNS_GfdGetTexKeyAddr(pTex->tex4x4Info.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT;
    }

    for (j = 0; j < pBindData->numIdx; ++j) {
        s32 w, h;

        NNSG3dResMatData * matData = NNS_G3dGetMatDataByIdx(pMat, *(base + j));

        matData->texImageParam |= (pTexData->texImageParam + vramOffset);
        w = (s32)(((pTexData->extraParam) & NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_MASK) >> NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_SHIFT);
        h = (s32)(((pTexData->extraParam) & NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_MASK) >> NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_SHIFT);

        matData->magW = (w != matData->origWidth) ?
                        func_0200235c(w << FX32_SHIFT, matData->origWidth << FX32_SHIFT) :
                        FX32_ONE;
        matData->magH = (h != matData->origHeight) ?
                        func_0200235c(h << FX32_SHIFT, matData->origHeight << FX32_SHIFT) :
                        FX32_ONE;
    }

    pBindData->flag |= 1;
}

void releaseMdlTex_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictTexToMatIdxData * pData)
{
    u8 * base = (u8 *)pMat + pData->offset;
    u32 j;

    for (j = 0; j < pData->numIdx; ++j) {

        NNSG3dResMatData * matData = NNS_G3dGetMatDataByIdx(pMat, *(base + j));

        matData->texImageParam &= REG_G3_TEXIMAGE_PARAM_TGEN_MASK |
                                  REG_G3_TEXIMAGE_PARAM_FT_MASK | REG_G3_TEXIMAGE_PARAM_FS_MASK |
                                  REG_G3_TEXIMAGE_PARAM_RT_MASK | REG_G3_TEXIMAGE_PARAM_RS_MASK;
        matData->magH = matData->magW = FX32_ONE;
    }

    pData->flag &= ~1;
}

BOOL NNS_G3dBindMdlTex (NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex)
{
    NNSG3dResMat * mat;
    NNSG3dResDict * dictTex;
    u32 i;
    BOOL result = TRUE;

    mat = NNS_G3dGetMat(pMdl);
    dictTex = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictTexToMatList);

    for (i = 0; i < dictTex->numEntry; ++i) {
        const NNSG3dResName * name = NNS_G3dGetResNameByIdx(dictTex, i);
        const NNSG3dResDictTexData * texData = NNS_G3dGetTexDataByName(pTex, name);

        if (texData) {
            NNSG3dResDictTexToMatIdxData * data =
                (NNSG3dResDictTexToMatIdxData *) NNS_G3dGetResDataByIdx(dictTex, i);

            if (!(data->flag & 1)) {
                bindMdlTex_Internal_(mat, data, pTex, texData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}

void NNS_G3dReleaseMdlTex (NNSG3dResMdl * pMdl)
{
    NNSG3dResMat * mat;
    NNSG3dResDict * dictTex;
    u32 i;

    mat = NNS_G3dGetMat(pMdl);
    dictTex = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictTexToMatList);

    for (i = 0; i < dictTex->numEntry; ++i) {
        NNSG3dResDictTexToMatIdxData * data =
            (NNSG3dResDictTexToMatIdxData *) NNS_G3dGetResDataByIdx(dictTex, i);

        if (data->flag & 1) {
            releaseMdlTex_Internal_(mat, data);
        }
    }
}

void bindMdlPltt_Internal_ (NNSG3dResMat * pMat, NNSG3dResDictPlttToMatIdxData * pBindData, const NNSG3dResTex * pTex, const NNSG3dResDictPlttData * pPlttData)
{
    u8 * base = (u8 *)pMat + pBindData->offset;
    u16 plttBase = pPlttData->offset;
    u16 vramOffset = (u16)(NNS_GfdGetTexKeyAddr(pTex->plttInfo.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT);
    u32 j;

    if (!(pPlttData->flag & 1)) {
        plttBase >>= 1;
        vramOffset >>= 1;
    }

    for (j = 0; j < pBindData->numIdx; ++j) {
        NNSG3dResMatData * matData = NNS_G3dGetMatDataByIdx(pMat, *(base + j));
        matData->texPlttBase = (u16)(plttBase + vramOffset);
    }

    pBindData->flag |= 1;
}

BOOL NNS_G3dBindMdlPltt (NNSG3dResMdl * pMdl, const NNSG3dResTex * pTex)
{
    NNSG3dResMat * mat;
    NNSG3dResDict * dictPltt;
    u32 i;
    BOOL result = TRUE;

    mat = NNS_G3dGetMat(pMdl);
    dictPltt = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictPlttToMatList);

    for (i = 0; i < dictPltt->numEntry; ++i) {
        const NNSG3dResName * name = NNS_G3dGetResNameByIdx(dictPltt, i);
        const NNSG3dResDictPlttData * plttData = NNS_G3dGetPlttDataByName(pTex, name);

        if (plttData) {
            NNSG3dResDictPlttToMatIdxData * data;
            data = (NNSG3dResDictPlttToMatIdxData *) NNS_G3dGetResDataByIdx(dictPltt, i);

            if (!(data->flag & 1)) {
                bindMdlPltt_Internal_(mat, data, pTex, plttData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}

void NNS_G3dReleaseMdlPltt (NNSG3dResMdl * pMdl)
{
    NNSG3dResMat * mat;
    NNSG3dResDict * dictPltt;
    u32 i;

    mat = NNS_G3dGetMat(pMdl);
    dictPltt = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictPlttToMatList);
    for (i = 0; i < dictPltt->numEntry; ++i) {
        NNSG3dResDictPlttToMatIdxData * data =
            (NNSG3dResDictPlttToMatIdxData *) NNS_G3dGetResDataByIdx(dictPltt, i);

        if (data->flag & 1) {
            data->flag &= ~1;
        }
    }
}

BOOL NNS_G3dBindMdlSet (NNSG3dResMdlSet * pMdlSet, const NNSG3dResTex * pTex)
{
    u32 i;
    BOOL result = TRUE;

    for (i = 0; i < pMdlSet->dict.numEntry; ++i) {
        NNSG3dResMdl * mdl = NNS_G3dGetMdlByIdx(pMdlSet, i);

        result &= NNS_G3dBindMdlTex(mdl, pTex);
        result &= NNS_G3dBindMdlPltt(mdl, pTex);
    }
    return result;
}

void NNS_G3dReleaseMdlSet (NNSG3dResMdlSet * pMdlSet)
{
    u32 i;

    for (i = 0; i < pMdlSet->dict.numEntry; ++i) {
        NNSG3dResMdl * mdl = NNS_G3dGetMdlByIdx(pMdlSet, i);

        NNS_G3dReleaseMdlTex(mdl);
        NNS_G3dReleaseMdlPltt(mdl);
    }
}
