/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g3d.h"

void NNS_G3dTexSetTexKey (NNSG3dResTex * pTex, NNSG3dTexKey texKey, NNSG3dTexKey tex4x4Key)
{
    if (texKey > 0) {
        pTex->texInfo.vramKey = texKey;
    }

    if (tex4x4Key > 0) {
        pTex->tex4x4Info.vramKey = tex4x4Key;
    }
}
