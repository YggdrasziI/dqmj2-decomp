/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx.h"

#include "nitro/os.h"

void blendScaleVec_ (VecFx32 * v0, const VecFx32 * v1, fx32 ratio, BOOL isV1One)
{
    if (isV1One) {

        v0->x += ratio;
        v0->y += ratio;
        v0->z += ratio;
    } else {
        v0->x += ratio * v1->x >> FX32_SHIFT;
        v0->y += ratio * v1->y >> FX32_SHIFT;
        v0->z += ratio * v1->z >> FX32_SHIFT;
    }
}
