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

void NNS_G2dResetAnimCtrlState(NNSG2dAnimController * pAnimCtrl);

extern void NNS_G2dStopAnimCtrl(NNSG2dAnimController * pAnimCtrl);

extern void NNS_G2dResetAnimCtrlState (NNSG2dAnimController * pAnimCtrl);

inline void NNS_G2dStopAnimCtrl (NNSG2dAnimController * pAnimCtrl)
{
    pAnimCtrl->bActive = 0 ;
}

static inline const NNSG2dAnimFrame * GetFrameBegin_ (const NNSG2dAnimSequence * pSequence)
{
    return pSequence->pAnmFrameArray;
}

static inline const NNSG2dAnimFrame * GetFrameEnd_ (const NNSG2dAnimSequence * pSequence)
{
    return pSequence->pAnmFrameArray + (pSequence->numFrames);
}

static inline const NNSG2dAnimFrame * GetFrameLoopBegin_ (const NNSG2dAnimSequence * pSequence)
{
    return pSequence->pAnmFrameArray + pSequence->loopStartFrameIdx;
}

static inline NNSG2dAnimationPlayMode GetAnimationPlayMode_ (const NNSG2dAnimController * pAnimCtrl)
{
    if ( pAnimCtrl->overriddenPlayMode != NNS_G2D_ANIMATIONPLAYMODE_INVALID ) {
        return pAnimCtrl->overriddenPlayMode;
    } else {
        return pAnimCtrl->pAnimSequence->playMode;
    }
}

static inline BOOL IsLoopAnimSequence_ (const NNSG2dAnimController * pAnimCtrl)
{
    {
        const NNSG2dAnimationPlayMode playMode = GetAnimationPlayMode_(pAnimCtrl);
        return (playMode == NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP ||
                playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP) ? 1 : 0 ;
    }
}

static inline BOOL IsReversePlayAnim_ (const NNSG2dAnimController * pAnimCtrl)
{
    {
        const NNSG2dAnimationPlayMode playMode = GetAnimationPlayMode_(pAnimCtrl);
        return (playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE ||
                playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP) ? 1 : 0 ;
    }
}

static inline BOOL IsReachStartEdge_ (const NNSG2dAnimController * pAnimCtrl, const NNSG2dAnimFrame * pFrame)
{
    return (pFrame <= (GetFrameLoopBegin_(pAnimCtrl->pAnimSequence) - 1)) ? 1 : 0 ;
}

static inline void SequenceEdgeHandleCommon_ (NNSG2dAnimController * pAnimCtrl)
{
    if ( pAnimCtrl->callbackFunctor.type == NNS_G2D_ANMCALLBACKTYPE_LAST_FRM ) {
        (*pAnimCtrl->callbackFunctor.pFunc)(pAnimCtrl->callbackFunctor.param, pAnimCtrl->currentTime);
    }
    if ( !IsLoopAnimSequence_(pAnimCtrl)) {
        NNS_G2dStopAnimCtrl(pAnimCtrl);
    } else {
        NNS_G2dResetAnimCtrlState(pAnimCtrl);
    }
}

static inline void SequenceEdgeHandleReverse_ (NNSG2dAnimController * pAnimCtrl)
{
    pAnimCtrl->bReverse = pAnimCtrl->bReverse ^ 1 ;
    if ( IsReachStartEdge_(pAnimCtrl, pAnimCtrl->pCurrent)) {
        SequenceEdgeHandleCommon_(pAnimCtrl);
    }
}

static inline void SequenceEdgeHandleNormal_ (NNSG2dAnimController * pAnimCtrl)
{
    SequenceEdgeHandleCommon_(pAnimCtrl);
}

static inline void ValidateAnimFrame_ (NNSG2dAnimController * pAnimCtrl, const NNSG2dAnimFrame ** pFrame)
{
    if ( *pFrame > GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1 ) {
        *pFrame = GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1;
    } else if ( *pFrame < GetFrameBegin_(pAnimCtrl->pAnimSequence)) {
        *pFrame = GetFrameBegin_(pAnimCtrl->pAnimSequence);
    }
}

void SequenceEdgeHandle_ (NNSG2dAnimController * pAnimCtrl)
{

    if ( IsReversePlayAnim_(pAnimCtrl)) {
        SequenceEdgeHandleReverse_(pAnimCtrl);
    } else {
        SequenceEdgeHandleNormal_(pAnimCtrl);
    }

    ValidateAnimFrame_(pAnimCtrl, &pAnimCtrl->pCurrent);
}

BOOL SetAnimCtrlCurrentFrameImpl_ (NNSG2dAnimController * pAnimCtrl, u16 index)
{

    if ( index < pAnimCtrl->pAnimSequence->numFrames ) {
        pAnimCtrl->pCurrent = &pAnimCtrl->pAnimSequence->pAnmFrameArray[index];
        if ( pAnimCtrl->pCurrent->frames != 0 ) {
            pAnimCtrl->pActiveCurrent = pAnimCtrl->pCurrent;
        }
        return TRUE;
    }
    return FALSE;
}

void * NNS_G2dGetAnimCtrlCurrentElement (NNSG2dAnimController * pAnimCtrl)
{

    return (void *)pAnimCtrl->pActiveCurrent->pContent;
}
