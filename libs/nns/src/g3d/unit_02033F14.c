/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

void * NNS_G3dGetResDataByName(const NNSG3dResDict * dict, const NNSG3dResName * name);

inline NNSG3dResDictPlttData * NNS_G3dGetPlttDataByName(const NNSG3dResTex * tex, const NNSG3dResName * name);

inline u32 NNS_GfdGetTexKeyAddr (NNSGfdTexKey memKey)
{
    return (u32)(((0x0000FFFF & memKey)) << 3 );
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

void SetPlttParamaters_ (const NNSG3dResTex * pTex, const NNSG3dResName * pPlttName, NNSG3dMatAnmResult * pResult)
{

    {

        const NNSG3dResDictPlttData * pPlttData = NNS_G3dGetPlttDataByName(pTex, pPlttName);
        u16 plttBase = pPlttData->offset;
        u16 vramOffset = (u16)(NNS_GfdGetTexKeyAddr(pTex->plttInfo.vramKey) >> NNS_GFD_TEXKEY_ADDR_SHIFT);

        if (!(pPlttData->flag & 1)) {

            plttBase >>= 1;
            vramOffset >>= 1;
        }

        pResult->prmTexPltt = (u32)(plttBase + vramOffset);
    }
}
