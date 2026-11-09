/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/fx.h"

void MTX_ScaleApply22(const MtxFx22 *src, MtxFx22 *dst, int sx, int sy) {
    dst->_00 = (int)(((long long)sx * src->_00) >> 12);
    dst->_01 = (int)(((long long)sx * src->_01) >> 12);
    dst->_10 = (int)(((long long)sy * src->_10) >> 12);
    dst->_11 = (int)(((long long)sy * src->_11) >> 12);
}
