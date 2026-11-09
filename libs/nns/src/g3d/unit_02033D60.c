/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/g3d.h"

void MIi_CpuClear16(u16 data, void * destp, u32 size);

extern NNSG3dFuncAnmMat data_020c66e4;

inline const NNSG3dResName * NNS_G3dGetResNameByIdx(const NNSG3dResDict * dict, u32 idx);

int NNS_G3dGetResDictIdxByName(const NNSG3dResDict * dict, const NNSG3dResName * name);

inline int NNS_G3dGetMatIdxByName(const NNSG3dResMat * mat, const NNSG3dResName * name);

inline NNSG3dResMat * NNS_G3dGetMat(const NNSG3dResMdl * mdl);

static inline void MI_CpuFill16 (void * dest, u16 data, u32 size)
{
    MIi_CpuClear16(data, dest, size);
}

static inline void MI_CpuClear16 (void * dest, u32 size)
{
    MI_CpuFill16(dest, 0, size);
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

inline int NNS_G3dGetMatIdxByName (const NNSG3dResMat * mat, const NNSG3dResName * name)
{
    if (mat)
        return NNS_G3dGetResDictIdxByName(&mat->dict, name);
    else
        return -1;
}

inline NNSG3dResMat * NNS_G3dGetMat (const NNSG3dResMdl * mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL ;
}

void NNSi_G3dAnmObjInitNsBtp (NNSG3dAnmObj * pAnmObj, void * pResAnm, const NNSG3dResMdl * pResMdl)
{
    u32 i;
    NNSG3dResTexPatAnm * tpAnm = (NNSG3dResTexPatAnm *)pResAnm;
    const NNSG3dResMat * mat = NNS_G3dGetMat(pResMdl);

    pAnmObj->funcAnm = (void *) data_020c66e4;
    pAnmObj->numMapData = pResMdl->info.numMat;
    pAnmObj->resAnm = tpAnm;

    MI_CpuClear16(&pAnmObj->mapData[0], sizeof(u16) * pAnmObj->numMapData);

    for (i = 0; i < tpAnm->dict.numEntry; ++i) {
        const NNSG3dResName * name = NNS_G3dGetResNameByIdx(&tpAnm->dict, i);
        int idx = NNS_G3dGetMatIdxByName(mat, name);
        if (!(idx < 0)) {

            pAnmObj->mapData[idx] = (u16)(i | NNS_G3D_ANMOBJ_MAPDATA_EXIST);
        }
    }
}
