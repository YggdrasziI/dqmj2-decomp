/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/fx.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/wm.h"

#include "nnsys/gfd.h"

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

typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);

typedef struct NNSG3dResDataBlockHeader_ {
    union {
        u32 kind;
        char chr[4];
    };
    u32 size;
} NNSG3dResDataBlockHeader;

typedef struct NNSG3dResDictTreeNode_ {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict_ {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResTexInfo_ {
    NNSGfdTexKey vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
} NNSG3dResTexInfo;

typedef struct NNSG3dResTex4x4Info_ {
    NNSGfdTexKey vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
    u32 ofsTexPlttIdx;
} NNSG3dResTex4x4Info;

typedef struct NNSG3dResPlttInfo_ {
    NNSGfdTexKey vramKey;
    u16 sizePltt;
    u16 flag;
    u16 ofsDict;
    u16 dummy_;
    u32 ofsPlttData;
} NNSG3dResPlttInfo;

typedef struct NNSG3dResTex_ {
    NNSG3dResDataBlockHeader header;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
    NNSG3dResPlttInfo plttInfo;
    NNSG3dResDict dict;
} NNSG3dResTex;

typedef struct NNSG3dResMdlInfo_ {
    u8 sbcType;
    u8 scalingRule;
    u8 texMtxMode;
    u8 numNode;
    u8 numMat;
    u8 numShp;
    u8 firstUnusedMtxStackID;
    u8 dummy_;
    fx32 posScale;
    fx32 invPosScale;
    u16 numVertex;
    u16 numPolygon;
    u16 numTriangle;
    u16 numQuad;
    fx16 boxX, boxY, boxZ;
    fx16 boxW, boxH, boxD;
    fx32 boxPosScale;
    fx32 boxInvPosScale;
} NNSG3dResMdlInfo;

typedef struct NNSG3dResNodeInfo_ {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResMdl_ {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
    u32 ofsShp;
    u32 ofsEvpMtx;
    NNSG3dResMdlInfo info;
    NNSG3dResNodeInfo nodeInfo;
} NNSG3dResMdl;

typedef struct NNSG3dResAnmHeader_ {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dAnmObj_ {
    fx32 frame;
    fx32 ratio;
    void * resAnm;
    void * funcAnm;
    struct NNSG3dAnmObj_ * next;
    const NNSG3dResTex * resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

typedef void (*NNSG3dAnimInitFunc)(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);

typedef struct {
    u8 category0;
    u8 dummy_;
    u16 category1;
    NNSG3dAnimInitFunc func;
} NNSG3dAnmObjInitFunc;

extern struct NNSG3dResMdl_;

extern u32 data_020c66d4;

extern NNSG3dAnmObjInitFunc data_020c66f8[10 ];

void NNS_G3dAnmObjInit (NNSG3dAnmObj * pAnmObj, void * pResAnm, const NNSG3dResMdl * pResMdl, const NNSG3dResTex * pResTex)
{
    const NNSG3dResAnmHeader * hdr;
    u32 i;

    pAnmObj->frame = 0;
    pAnmObj->resAnm = (void *)pResAnm;

    pAnmObj->next = NULL;
    pAnmObj->priority = 127;
    pAnmObj->ratio = FX32_ONE;
    pAnmObj->resTex = pResTex;
    pAnmObj->numMapData = 0;
    pAnmObj->funcAnm = NULL;

    hdr = (const NNSG3dResAnmHeader *)pResAnm;

    for (i = 0; i < data_020c66d4; ++i) {
        if (data_020c66f8[i].category0 == hdr->category0 &&
            data_020c66f8[i].category1 == hdr->category1) {
            if (data_020c66f8[i].func) {
                (*data_020c66f8[i].func)(pAnmObj, pResAnm, pResMdl);
            }
            break;
        }
    }
}
