/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/g3d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

typedef enum {
    GX_POLYGONMODE_MODULATE    = 0,
    GX_POLYGONMODE_DECAL       = 1,
    GX_POLYGONMODE_TOON        = 2,
    GX_POLYGONMODE_SHADOW      = 3
} GXPolygonMode;

inline void * NNS_G3dGetResDataByIdx(const NNSG3dResDict * dict, u32 idx);

inline NNSG3dResMat * NNS_G3dGetMat(const NNSG3dResMdl * mdl);

inline NNSG3dResMatData * NNS_G3dGetMatDataByIdx(const NNSG3dResMat * mat, u32 idx);

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

inline NNSG3dResMat * NNS_G3dGetMat (const NNSG3dResMdl * mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL ;
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

void NNS_G3dMdlSetMdlPolygonMode (NNSG3dResMdl * pMdl, u32 matID, GXPolygonMode polyMode)
{
    NNSG3dResMatData * data;

    data = NNS_G3dGetMatDataByIdx(NNS_G3dGetMat(pMdl), matID);

    data->polyAttr = (data->polyAttr & ~REG_G3_POLYGON_ATTR_PM_MASK) |
                     (polyMode << REG_G3_POLYGON_ATTR_PM_SHIFT);
}
