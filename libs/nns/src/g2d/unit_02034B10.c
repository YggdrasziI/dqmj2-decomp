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

extern BOOL SetAnimCtrlCurrentFrameImpl_ (NNSG2dAnimController * pAnimCtrl, u16 index);

void NNS_G2dInitAnimCallBackFunctor(NNSG2dAnimCallBackFunctor * pCallBack);

extern void NNS_G2dInitAnimCallBackFunctor (NNSG2dCallBackFunctor * pCallBack);

BOOL func_0203495c(NNSG2dAnimController * pAnimCtrl, fx32 frames);

extern BOOL func_0203495c (NNSG2dAnimController * pAnimCtrl, fx32 frames);

void NNS_G2dResetAnimCtrlState(NNSG2dAnimController * pAnimCtrl);

extern void NNS_G2dResetAnimCtrlState (NNSG2dAnimController * pAnimCtrl);

static inline const NNSG2dAnimFrame * GetFrameEnd_ (const NNSG2dAnimSequence * pSequence)
{
    return pSequence->pAnmFrameArray + (pSequence->numFrames);
}

static inline const NNSG2dAnimFrame * GetFrameLoopBegin_ (const NNSG2dAnimSequence * pSequence)
{
    return pSequence->pAnmFrameArray + pSequence->loopStartFrameIdx;
}

static inline BOOL IsAnimCtrlMovingForward_ (const NNSG2dAnimController * pAnimCtrl)
{
    return (pAnimCtrl->speed > 0) ^ (pAnimCtrl->bReverse) ? 1 : 0 ;
}

BOOL NNS_G2dSetAnimCtrlCurrentFrame (NNSG2dAnimController * pAnimCtrl, u16 index)
{
    {
        const BOOL result = SetAnimCtrlCurrentFrameImpl_(pAnimCtrl, index);

        if ( result ) {
            pAnimCtrl->currentTime = 0;
        }

        return result;
    }
}

void NNS_G2dInitAnimCtrl (NNSG2dAnimController * pAnimCtrl)
{

    NNS_G2dInitAnimCallBackFunctor(&pAnimCtrl->callbackFunctor);

    pAnimCtrl->pCurrent = NULL;
    pAnimCtrl->pActiveCurrent = NULL;

    pAnimCtrl->bReverse = FALSE;
    pAnimCtrl->bActive = TRUE;

    pAnimCtrl->currentTime = 0;
    pAnimCtrl->speed = FX32_ONE;

    pAnimCtrl->overriddenPlayMode = NNS_G2D_ANIMATIONPLAYMODE_INVALID;
    pAnimCtrl->pAnimSequence = NULL;
}

void NNS_G2dInitAnimCallBackFunctor (NNSG2dCallBackFunctor * pCallBack)
{

    pCallBack->type = NNS_G2D_ANMCALLBACKTYPE_NONE;
    pCallBack->param = 0x0;
    pCallBack->pFunc = NULL;
    pCallBack->frameIdx = 0;
}

void NNS_G2dResetAnimCtrlState (NNSG2dAnimController * pAnimCtrl)
{

    if ( IsAnimCtrlMovingForward_(pAnimCtrl)) {
        pAnimCtrl->pCurrent = GetFrameLoopBegin_(pAnimCtrl->pAnimSequence);
    } else {
        pAnimCtrl->pCurrent = GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1;
    }

    pAnimCtrl->pActiveCurrent = pAnimCtrl->pCurrent;
    pAnimCtrl->currentTime = 0;

    (void)func_0203495c(pAnimCtrl, 0);
}

void NNS_G2dBindAnimCtrl (NNSG2dAnimController * pAnimCtrl, const NNSG2dAnimSequence * pAnimSequence)
{

    pAnimCtrl->pAnimSequence = pAnimSequence;

    NNS_G2dResetAnimCtrlState(pAnimCtrl);
}
