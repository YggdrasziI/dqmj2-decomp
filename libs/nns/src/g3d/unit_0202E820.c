/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

u32 NNS_G3dTexGetRequiredSize (const NNSG3dResTex * pTex)
{

    if (pTex) {
        return (u32)(pTex->texInfo.sizeTex << 3);
    } else {
        return 0;
    }
}
