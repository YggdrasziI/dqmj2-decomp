/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/gfd.h"

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

typedef enum {
    NNS_G3D_JNTANM_SRTINFO_IDENTITY   = 0x00000001,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_T = 0x00000002,
    NNS_G3D_JNTANM_SRTINFO_BASE_T     = 0x00000004,
    NNS_G3D_JNTANM_SRTINFO_CONST_TX   = 0x00000008,
    NNS_G3D_JNTANM_SRTINFO_CONST_TY   = 0x00000010,
    NNS_G3D_JNTANM_SRTINFO_CONST_TZ   = 0x00000020,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_R = 0x00000040,
    NNS_G3D_JNTANM_SRTINFO_BASE_R     = 0x00000080,
    NNS_G3D_JNTANM_SRTINFO_CONST_R    = 0x00000100,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_S = 0x00000200,
    NNS_G3D_JNTANM_SRTINFO_BASE_S     = 0x00000400,
    NNS_G3D_JNTANM_SRTINFO_CONST_SX   = 0x00000800,
    NNS_G3D_JNTANM_SRTINFO_CONST_SY   = 0x00001000,
    NNS_G3D_JNTANM_SRTINFO_CONST_SZ   = 0x00002000,
    NNS_G3D_JNTANM_SRTINFO_NODE_MASK  = 0xff000000,
    NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT = 24
} NNSG3dJntAnmSRTTag;

typedef struct NNSG3dResJntAnmSRTTag_ {
    u32 tag;
} NNSG3dResJntAnmSRTTag;

typedef struct NNSG3dResJntAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
} NNSG3dResJntAnm;

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

typedef enum {
    NNS_G3D_ANMOBJ_MAPDATA_EXIST     = 0x0100,
    NNS_G3D_ANMOBJ_MAPDATA_DISABLED  = 0x0200,
    NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD = 0x00ff
} NNSG3dAnmObjMapData;

typedef enum {
    NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE    = 0x00000001,
    NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO     = 0x00000002,
    NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO   = 0x00000004,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX0_ONE = 0x00000008,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX1_ONE = 0x00000010,
    NNS_G3D_JNTANM_RESULTFLAG_MAYA_SSC     = 0x00000020
} NNSG3dJntAnmResultFlag;

typedef struct NNSG3dJntAnmResult_ {
    NNSG3dJntAnmResultFlag flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

typedef void (*NNSG3dFuncAnmJnt)(NNSG3dJntAnmResult *, const NNSG3dAnmObj *, u32);

void MIi_CpuClear16(u16 data, void * destp, u32 size);

extern struct NNSG3dJntAnmResult_;

extern struct NNSG3dResMdl_;

extern NNSG3dFuncAnmJnt data_020c66dc;

inline NNSG3dResNodeInfo * NNS_G3dGetNodeInfo(const NNSG3dResMdl * mdl);

static inline void MI_CpuFill16 (void * dest, u16 data, u32 size)
{
    MIi_CpuClear16(data, dest, size);
}

static inline void MI_CpuClear16 (void * dest, u32 size)
{
    MI_CpuFill16(dest, 0, size);
}

inline NNSG3dResNodeInfo * NNS_G3dGetNodeInfo (const NNSG3dResMdl * mdl)
{
    if (mdl)
        return (NNSG3dResNodeInfo *)&mdl->nodeInfo;
    else
        return NULL ;
}

void NNSi_G3dAnmObjInitNsBca (NNSG3dAnmObj * pAnmObj, void * pResAnm, const NNSG3dResMdl * pResMdl)
{
    u32 i;
    u16 * ofsArray;
    NNSG3dResJntAnm * jntAnm;
    const NNSG3dResNodeInfo * jnt;

    pAnmObj->resAnm = pResAnm;
    jntAnm = (NNSG3dResJntAnm *)pResAnm;
    jnt = NNS_G3dGetNodeInfo(pResMdl);
    pAnmObj->funcAnm = data_020c66dc;
    pAnmObj->numMapData = pResMdl->info.numNode;

    MI_CpuClear16(&pAnmObj->mapData[0], sizeof(u16) * pAnmObj->numMapData);

    ofsArray = (u16 *)((u8 *)jntAnm + sizeof(NNSG3dResJntAnm));

    for (i = 0; i < jntAnm->numNode; ++i)
    {
        NNSG3dResJntAnmSRTTag * pTag =
            (NNSG3dResJntAnmSRTTag *)((u8 *)jntAnm + ofsArray[i]);
        pAnmObj->mapData[i] = (u16)((pTag->tag >> NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT) |
                                    NNS_G3D_ANMOBJ_MAPDATA_EXIST);
    }
}
