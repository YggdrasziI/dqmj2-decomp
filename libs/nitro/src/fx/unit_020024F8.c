/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/fx_types.h"

fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b)
{
    long long sum = (long long)a->x * b->x
                  + (long long)a->y * b->y
                  + (long long)a->z * b->z;

    return (fx32)((sum + 0x800) >> 12);
}
