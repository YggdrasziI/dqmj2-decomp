/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/g3d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void func_02008c14(u32 data, void * destp, u32 size);

extern NNSG3dFuncAnmBlendMat data_020c66f4;

extern NNSG3dFuncAnmBlendJnt data_020c66f0;

extern NNSG3dFuncAnmBlendVis data_020c66ec;

static inline void MI_CpuFill32 (void * dest, u32 data, u32 size)
{
    func_02008c14(data, dest, size);
}

static inline void MI_CpuClear32 (void * dest, u32 size)
{
    MI_CpuFill32(dest, 0, size);
}

void NNS_G3dRenderObjInit (NNSG3dRenderObj * pRenderObj, NNSG3dResMdl * pResMdl)
{

    MI_CpuClear32(pRenderObj, sizeof(NNSG3dRenderObj));

    pRenderObj->funcBlendMat = data_020c66f4;
    pRenderObj->funcBlendJnt = data_020c66f0;
    pRenderObj->funcBlendVis = data_020c66ec;

    pRenderObj->resMdl = pResMdl;
}
