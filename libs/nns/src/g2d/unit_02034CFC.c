/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/fx.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/wm.h"

#include "nnsys/gfd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define NNS_G2D_INVALID_CELL_TRANSFER_STATE_HANDLE (u32)0xFFFFFFFF

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

typedef struct NNSG2dSVec2 {
    s16 x;
    s16 y;
} NNSG2dSVec2;

typedef struct NNSG2dFVec2 {
    fx32 x;
    fx32 y;
} NNSG2dFVec2;

typedef enum {
    NNS_G2D_SRTCONTROLTYPE_INVALID,
    NNS_G2D_SRTCONTROLTYPE_SRT,
    NNS_G2D_SRTCONTROLTYPE_MTX2D,
    NNS_G2D_SRTCONTROLTYPE_MTX3D,
    NNS_G2D_SRTCONTROLTYPE_MAX
} NNSG2dSRTControlType;

typedef union {
    struct {
        NNSG2dFVec2 scale;
        NNSG2dSVec2 trans;
        u16 rotZ;
        u16 SRT_EnableFlag;
    };
    MtxFx32 mtx;
} NNSG2dSRTData;

typedef struct {
    NNSG2dSRTControlType type;
    NNSG2dSRTData srtData;
} NNSG2dSRTControl;

typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_MAX
} NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimFrameData {
    void * pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrameData;

typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrameData * pAnmFrameArray;
} NNSG2dAnimSequenceData;

typedef enum NNSG2dCharacterDataMappingType {
    NNS_G2D_CHARACTERMAPPING_1D_32,
    NNS_G2D_CHARACTERMAPPING_1D_64,
    NNS_G2D_CHARACTERMAPPING_1D_128,
    NNS_G2D_CHARACTERMAPPING_1D_256,
    NNS_G2D_CHARACTERMAPPING_2D,
    NNS_G2D_CHARACTERMAPPING_MAX
} NNSG2dCharacterDataMappingType;

typedef struct NNSG2dCellVramTransferData {
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;

typedef struct NNSG2dVramTransferData {
    u32 szByteMax;
    NNSG2dCellVramTransferData * pCellTransferDataArray;
} NNSG2dVramTransferData;

typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;
} NNSG2dCellData;

typedef struct NNSG2dCellDataBank {
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMappingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dCellDataBank;

typedef NNSG2dAnimFrameData NNSG2dAnimFrame;

typedef NNSG2dAnimSequenceData NNSG2dAnimSequence;

typedef void (*NNSG2dAnmCallBackPtr)(u32 data, fx32 currentFrame);

typedef enum NNSG2dAnmCallbackType {
    NNS_G2D_ANMCALLBACKTYPE_NONE = 0,
    NNS_G2D_ANMCALLBACKTYPE_LAST_FRM,
    NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM,
    NNS_G2D_ANMCALLBACKTYPE_EVER_FRM,
    AnmCallbackType_MAX
} NNSG2dAnmCallbackType;

typedef struct NNSG2dCallBackFunctor {
    NNSG2dAnmCallbackType type;
    u32 param;
    NNSG2dAnmCallBackPtr pFunc;
    u16 frameIdx;
    u16 pad16_;
} NNSG2dCallBackFunctor, NNSG2dAnimCallBackFunctor;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame * pCurrent;
    const NNSG2dAnimFrame * pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    NNSG2dAnimationPlayMode overriddenPlayMode;
    const NNSG2dAnimSequence * pAnimSequence;
    NNSG2dAnimCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

typedef BOOL (*VramTransferTaskRegisterFuncPtr)(NNS_GFD_DST_TYPE type, u32 dstAddr, void * pSrc, u32 szByte);

typedef struct NNSG2dCellAnimation {
    NNSG2dAnimController animCtrl;
    const NNSG2dCellData * pCurrentCell;
    const NNSG2dCellDataBank * pCellDataBank;
    u32 cellTransferStateHandle;
    NNSG2dSRTControl srtCtrl;
} NNSG2dCellAnimation;

void NNS_G2dInitAnimCtrl(NNSG2dAnimController * pAnimCtrl);

void func_02034d38(NNSG2dCellAnimation * pCellAnim, const NNSG2dAnimSequence * pAnimSeq);

void NNSi_G2dSrtcInitControl(NNSG2dSRTControl * pCtrl, NNSG2dSRTControlType type);

extern void func_02034d38 (NNSG2dCellAnimation * pCellAnim, const NNSG2dAnimSequence * pAnimSeq);

static inline void InitCellAnimationImpl_ (NNSG2dCellAnimation * pCellAnim, const NNSG2dAnimSequence * pAnimSeq, const NNSG2dCellDataBank * pCellDataBank, u32 cellTransferStateHandle)
{
    pCellAnim->pCellDataBank = pCellDataBank;
    pCellAnim->cellTransferStateHandle = cellTransferStateHandle;
    NNSi_G2dSrtcInitControl(&pCellAnim->srtCtrl, NNS_G2D_SRTCONTROLTYPE_SRT);
    NNS_G2dInitAnimCtrl(&pCellAnim->animCtrl);
    func_02034d38(pCellAnim, pAnimSeq);
}

void NNS_G2dInitCellAnimation (NNSG2dCellAnimation * pCellAnim, const NNSG2dAnimSequence * pAnimSeq, const NNSG2dCellDataBank * pCellDataBank)
{

    InitCellAnimationImpl_(pCellAnim,
                           pAnimSeq,
                           pCellDataBank,
                           NNS_G2D_INVALID_CELL_TRANSFER_STATE_HANDLE);
}
