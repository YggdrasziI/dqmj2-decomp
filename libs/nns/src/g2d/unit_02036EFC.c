/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/fx_types.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/wm.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

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

typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);

typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);

void MIi_CpuClear16(u16 data, void * destp, u32 size);

static inline void MI_CpuFill16 (void * dest, u16 data, u32 size)
{
    MIi_CpuClear16(data, dest, size);
}

void NNSi_G2dSrtcSetInitialValue (NNSG2dSRTControl * pCtrl)
{

    MI_CpuFill16(&pCtrl->srtData, 0, sizeof(NNSG2dSRTData));

    pCtrl->srtData.scale.x = FX32_ONE;
    pCtrl->srtData.scale.y = FX32_ONE;
}
