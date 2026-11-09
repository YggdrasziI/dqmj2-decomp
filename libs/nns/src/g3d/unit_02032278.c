/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/fx.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/fs.h"

#include "nitro/wm.h"

#include "nnsys/gfd.h"

#include "nitro/fx_types.h"

#include "nitro/os.h"

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

typedef enum STDResult {
    STD_RESULT_SUCCESS,
    STD_RESULT_ERROR,
    STD_RESULT_INVALID_PARAM,
    STD_RESULT_CONVERSION_FAILED
} STDResult;

typedef STDResult (*STDConvertUnicodeCallback) (u16 * dst, int * dst_len, const char * src, int * src_len);

typedef STDResult (*STDConvertSjisCallback) (char * dst, int * dst_len, const u16 * src, int * src_len);

typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);

typedef void (*WBTCallback) (void *);

typedef s16 WBTResult;

typedef enum {
    WBT_CMD_REQ_NONE = 0,
    WBT_CMD_REQ_WAIT,
    WBT_CMD_REQ_SYNC,
    WBT_CMD_RES_SYNC,
    WBT_CMD_REQ_GET_BLOCK,
    WBT_CMD_RES_GET_BLOCK,
    WBT_CMD_REQ_GET_BLOCKINFO,
    WBT_CMD_RES_GET_BLOCKINFO,
    WBT_CMD_REQ_GET_BLOCK_DONE,
    WBT_CMD_RES_GET_BLOCK_DONE,
    WBT_CMD_REQ_USER_DATA,
    WBT_CMD_RES_USER_DATA,
    WBT_CMD_SYSTEM_CALLBACK,
    WBT_CMD_PREPARE_SEND_DATA,
    WBT_CMD_REQ_ERROR,
    WBT_CMD_RES_ERROR,
    WBT_CMD_CANCEL
} WBTCommandType;

typedef u8 WBTCommandCounter;

typedef u16 WBTAidBitmap;

typedef s16 WBTBlockNumEntry;

typedef struct {
    u32 id;
    s32 block_size;
    u8 user_id[32 ];
} WBTBlockInfo;

typedef struct WBTBlockInfoList {
    WBTBlockInfo data_info;
    struct WBTBlockInfoList * next;
    void * data_ptr;
    WBTAidBitmap permission_bmp;
    u16 block_type;
} WBTBlockInfoList;

typedef struct {
    WBTBlockInfo * block_info[((1 + 15 - 1) + 1) ];
} WBTBlockInfoTable;

typedef struct {
    u32 * packet_bitmap[((1 + 15 - 1) + 1) ];
} WBTPacketBitmapTable;

typedef struct {
    u8 * recv_buf[((1 + 15 - 1) + 1) ];
} WBTRecvBufTable;

typedef struct {
    WBTBlockNumEntry num_of_list;
    s16 peer_packet_size;
    s16 my_packet_size;
    u16 pad1;
    u32 padd2[2];
} WBTRequestSyncCallback;

typedef struct {
    u32 block_id;
} WBTGetBlockDoneCallback;

typedef struct {
    u32 block_id;
    s32 block_seq_no;
    void * data_ptr;
    s16 own_packet_size;
    u16 padd;
} WBTPrepareSendDataCallback;

typedef struct {
    u8 data[9 ];
    u8 size;
    u8 padd[3];
} WBTRecvUserDataCallback;

typedef struct {
    u32 block_id;
    u32 recv_data_size;
    WBTRecvBufTable recv_buf_table;
    WBTPacketBitmapTable pkt_bmp_table;
} WBTGetBlockCallback;

typedef struct {
    WBTCommandType command;
    WBTCommandType event;
    u16 target_bmp;
    u16 peer_bmp;
    WBTCommandCounter my_cmd_counter;
    WBTCommandCounter peer_cmd_counter;
    WBTResult result;
    WBTCallback callback;
    union {
        WBTRequestSyncCallback sync;
        WBTGetBlockDoneCallback blockdone;
        WBTPrepareSendDataCallback prepare_send_data;
        WBTRecvUserDataCallback user_data;
        WBTGetBlockCallback get;
    };
} WBTCommand;

typedef void (*WBTEventCallback)(void *, WBTCommand *);

typedef struct WBTCommandList {
    struct WBTCommandList * next;
    WBTCommand command;
    WBTEventCallback callback;
} WBTCommandList;

typedef struct WBTRecvToken {
    u8 token_command;
    u8 token_peer_cmd_counter;
    u8 last_peer_cmd_counter;
    u8 dummy[1];
    u32 token_block_id;
    s32 token_block_seq_no;
} WBTRecvToken;

typedef struct WBTPacketBitmap {
    s32 length;
    void * buffer;
    s32 count;
    s32 total;
    u32 * bitmap;
    s32 current;
} WBTPacketBitmap;

typedef struct WBTContext {
    WBTCommandList * command;
    WBTCommandList * command_pool;
    void * userdata;
    WBTEventCallback callback;
    WBTCommand system_cmd;
    struct {
        WBTRecvToken recv_token;
        WBTPacketBitmap pkt_bmp;
    } peer_param[16];
    int my_aid;
    s16 peer_data_packet_size;
    s16 my_data_packet_size;
    WBTBlockInfoList * list;
    u8 my_command_counter;
    u8 padding[3];
    int last_target_aid;
    u32 last_block_id;
    s32 last_seq_no_1;
    s32 last_seq_no_2;
    int req_bitmap;
    u32 binfo_bitmap[16][(((sizeof(WBTBlockInfo)) + (( sizeof(u32)) - 1)) & ~(( sizeof(u32)) - 1)) / sizeof(u32)];
} WBTContext;

typedef enum WFSTableRegionType {
    WFS_TABLE_REGION_FAT,
    WFS_TABLE_REGION_FNT,
    WFS_TABLE_REGION_OV9,
    WFS_TABLE_REGION_OV7,
    WFS_TABLE_REGION_MAX
} WFSTableRegionType;

typedef enum WFSEventType {
    WFS_EVENT_SERVER_SEGMENT_REQUEST,
    WFS_EVENT_CLIENT_READY
} WFSEventType;

typedef struct WFSTableFormat {
    u32 origin;
    u8 * buffer;
    u32 length;
    CARDRomRegion region[WFS_TABLE_REGION_MAX];
} WFSTableFormat;

typedef void (*WFSEventCallback)(void * context, WFSEventType, void * argument);

typedef void (*WFSRequestClientReadDoneCallback)(struct WFSClientContext * context, BOOL succeeded, void * arg);

typedef struct WFSClientContext {
    void * userdata;
    WFSEventCallback callback;
    MIAllocator * allocator;
    u32 fat_ready :1;
    u32 flags :31;
    WBTContext wbt[1];
    WBTCommandList wbt_list[2];
    WBTRecvBufTable recv_buf_table;
    WBTPacketBitmapTable recv_buf_packet_bmp_table;
    WBTBlockInfoTable block_info_table;
    WBTBlockInfo block_info[16];
    u32 * recv_pkt_bmp_buf;
    u32 max_file_size;
    WFSTableFormat table[1];
    u32 block_id;
    CARDRomRegion request_region;
    void * request_buffer;
    WFSRequestClientReadDoneCallback request_callback;
    void * request_argument;
    u8 padding[12];
} WFSClientContext;

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

typedef struct NNSG3dResMat_ {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dResShp_ {
    NNSG3dResDict dict;
} NNSG3dResShp;

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

typedef enum {
    NNS_G3D_SRTFLAG_TRANS_ZERO        = 0x0001,
    NNS_G3D_SRTFLAG_ROT_ZERO          = 0x0002,
    NNS_G3D_SRTFLAG_SCALE_ONE         = 0x0004,
    NNS_G3D_SRTFLAG_PIVOT_EXIST       = 0x0008,
    NNS_G3D_SRTFLAG_IDXPIVOT_MASK     = 0x00f0,
    NNS_G3D_SRTFLAG_PIVOT_MINUS       = 0x0100,
    NNS_G3D_SRTFLAG_SIGN_REVC         = 0x0200,
    NNS_G3D_SRTFLAG_SIGN_REVD         = 0x0400,
    NNS_G3D_SRTFLAG_IDXMTXSTACK_MASK  = 0xf800,
    NNS_G3D_SRTFLAG_IDENTITY          = NNS_G3D_SRTFLAG_TRANS_ZERO |
                                        NNS_G3D_SRTFLAG_ROT_ZERO |
                                        NNS_G3D_SRTFLAG_SCALE_ONE,
    NNS_G3D_SRTFLAG_IDXPIVOT_SHIFT    = 4,
    NNS_G3D_SRTFLAG_IDXMTXSTACK_SHIFT = 11
} NNSG3dSRTFlag;

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

typedef enum {
    NNS_G3D_JNTANM_RIDX_PIVOT         = 0x8000,
    NNS_G3D_JNTANM_RIDX_IDXDATA_MASK  = 0x7fff,
    NNS_G3D_JNTANM_RIDX_IDXDATA_SHIFT = 0
} NNSG3dJntAnmRIdx;

typedef struct NNSG3dResJntAnmSRTTag_ {
    u32 tag;
} NNSG3dResJntAnmSRTTag;

typedef enum {
    NNS_G3D_JNTANM_OPTION_INTERPOLATION = 0x01,
    NNS_G3D_JNTANM_OPTION_END_TO_START_INTERPOLATION = 0x02
} NNSG3dJntAnmOption;

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

typedef BOOL (*NNSG3dFuncAnmBlendMat)(struct NNSG3dMatAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef BOOL (*NNSG3dFuncAnmBlendJnt)(struct NNSG3dJntAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef BOOL (*NNSG3dFuncAnmBlendVis)(struct NNSG3dVisAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef void (*NNSG3dSbcCallBackFunc)(struct NNSG3dRS_ *);

typedef struct NNSG3dRenderObj_ {
    u32 flag;
    NNSG3dResMdl * resMdl;
    NNSG3dAnmObj * anmMat;
    NNSG3dFuncAnmBlendMat funcBlendMat;
    NNSG3dAnmObj * anmJnt;
    NNSG3dFuncAnmBlendJnt funcBlendJnt;
    NNSG3dAnmObj * anmVis;
    NNSG3dFuncAnmBlendVis funcBlendVis;
    NNSG3dSbcCallBackFunc cbFunc;
    u8 cbCmd;
    u8 cbTiming;
    u16 dummy_;
    NNSG3dSbcCallBackFunc cbInitFunc;
    void * ptrUser;
    u8 * ptrUserSbc;
    struct NNSG3dJntAnmResult_ * recJntAnm;
    struct NNSG3dMatAnmResult_ * recMatAnm;
    u32 hintMatAnmExist[64 / 32];
    u32 hintJntAnmExist[64 / 32];
    u32 hintVisAnmExist[64 / 32];
} NNSG3dRenderObj;

typedef enum {
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE  = 0x00000001,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO   = 0x00000002,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO = 0x00000004,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SET       = 0x00000008,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_MULT      = 0x00000010,
    NNS_G3D_MATANM_RESULTFLAG_WIREFRAME        = 0x00000020}
NNSG3dMatAnmResultFlag;

typedef struct NNSG3dMatAnmResult_ {
    NNSG3dMatAnmResultFlag flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS, scaleT;
    fx16 sinR, cosR;
    fx32 transS, transT;
    u16 origWidth, origHeight;
    fx32 magW, magH;
} NNSG3dMatAnmResult;

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

typedef struct NNSG3dVisAnmResult_ {
    BOOL isVisible;
} NNSG3dVisAnmResult;

typedef void (*NNSG3dGetJointScale)(NNSG3dJntAnmResult * pResult, const fx32 * p, const u8 * cmd, u32 srtflag);

typedef void (*NNSG3dSendJointSRT)(const NNSG3dJntAnmResult *);

typedef void (*NNSG3dSendTexSRT)(const NNSG3dMatAnmResult *);

typedef struct NNSG3dRS_ {
    u8 * c;
    NNSG3dRenderObj * pRenderObj;
    u32 flag;
    NNSG3dSbcCallBackFunc cbVecFunc[0x20 ];
    u8 cbVecTiming[0x20 ];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
    u8 dummy_;
    NNSG3dMatAnmResult * pMatAnmResult;
    NNSG3dJntAnmResult * pJntAnmResult;
    NNSG3dVisAnmResult * pVisAnmResult;
    u32 isMatCached[64 / 32];
    u32 isScaleCacheOne[64 / 32];
    u32 isEvpCached[64 / 32];
    const NNSG3dResNodeInfo * pResNodeInfo;
    const NNSG3dResMat * pResMat;
    const NNSG3dResShp * pResShp;
    fx32 posScale;
    fx32 invPosScale;
    NNSG3dGetJointScale funcJntScale;
    NNSG3dSendJointSRT funcJntMtx;
    NNSG3dSendTexSRT funcTexMtx;
    NNSG3dMatAnmResult tmpMatAnmResult;
    NNSG3dJntAnmResult tmpJntAnmResult;
    NNSG3dVisAnmResult tmpVisAnmResult;
} NNSG3dRS;

typedef enum {
    NNS_G3D_JNTANM_TINFO_STEP_1            = 0x00000000,
    NNS_G3D_JNTANM_TINFO_STEP_2            = 0x40000000,
    NNS_G3D_JNTANM_TINFO_STEP_4            = 0x80000000,
    NNS_G3D_JNTANM_TINFO_FX16ARRAY         = 0x20000000,
    NNS_G3D_JNTANM_TINFO_LAST_INTERP_MASK  = 0x1fff0000,
    NNS_G3D_JNTANM_TINFO_STEP_MASK         = 0xc0000000,
    NNS_G3D_JNTANM_TINFO_LAST_INTERP_SHIFT = 16,
    NNS_G3D_JNTANM_TINFO_STEP_SHIFT        = 30
} NNSG3dJntAnmTInfo;

extern struct WBTContext;

extern struct WBTCommandList;

extern struct WFSClientContext;

extern struct NNSG3dMatAnmResult_;

extern struct NNSG3dJntAnmResult_;

extern struct NNSG3dVisAnmResult_;

extern struct NNSG3dRS_;

extern struct NNSG3dResMdl_;

extern NNSG3dRS * data_020d6af4;

extern void getTransData_(fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void getTransDataEx_(fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_020328e0(fx32 * s_invs, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_02032ac8(fx32 * s_invs, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_02032c5c(MtxFx33 * pRot, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void getRotDataEx_(MtxFx33 * pRot, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern BOOL getRotDataByIdx_(MtxFx33 * pRot, const void * pArrayRot3, const void * pArrayRot5, NNSG3dJntAnmRIdx info);

extern void getMdlTrans_ (NNSG3dJntAnmResult * pResult);

extern void getMdlScale_ (NNSG3dJntAnmResult * pResult);

extern void func_020320f8 (NNSG3dJntAnmResult * pResult);

extern void getTransData_ (fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void getTransDataEx_ (fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_020328e0 (fx32 * s_invs, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_02032ac8 (fx32 * s_invs, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void func_02032c5c (MtxFx33 * pRot, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern void getRotDataEx_ (MtxFx33 * pRot, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm);

extern BOOL getRotDataByIdx_ (MtxFx33 * pRot, const void * pArrayRot3, const void * pArrayRot5, NNSG3dJntAnmRIdx info);

extern s32 FX_Whole(fx32 v);

static inline void vecCross_ (const VecFx32 * a, const VecFx32 * b, VecFx32 * axb)
{
    fx32 x, y, z;
    x = (a->y * b->z - a->z * b->y) >> 12 ;
    y = (a->z * b->x - a->x * b->z) >> 12 ;
    z = (a->x * b->y - a->y * b->x) >> 12 ;
    axb->x = x;
    axb->y = y;
    axb->z = z;
}

static inline s32 FX_Whole (fx32 v)
    {
        return (s32)(v >> 12 );
    }

void getJntSRTAnmResult_ (const NNSG3dResJntAnm * pJntAnm, u32 dataIdx, fx32 Frame, NNSG3dJntAnmResult * pResult)
{
    NNSG3dResJntAnmSRTTag * pAnmSRTTag;
    NNSG3dJntAnmSRTTag tag;
    const u32 * pData;
    BOOL IsDecimalFrame;
    fx32 pS_invS[6];

    {
        const u16 * ofsTag = (const u16 *)((u8 *) pJntAnm + sizeof(NNSG3dResJntAnm));
        pAnmSRTTag = (NNSG3dResJntAnmSRTTag *)((u8 *) pJntAnm + ofsTag[dataIdx]);
        tag = (NNSG3dJntAnmSRTTag)pAnmSRTTag->tag;
    }

    if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY) {
        pResult->flag = (NNSG3dJntAnmResultFlag)(NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE |
                                                 NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO |
                                                 NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO);
        goto GET_JOINTSCALE;
    }

    pData = (const u32 *)((const u8 *)pAnmSRTTag + sizeof(NNSG3dResJntAnmSRTTag));

    IsDecimalFrame = (BOOL)((Frame & (FX32_ONE - 1)) &&
                            (pJntAnm->flag & NNS_G3D_JNTANM_OPTION_INTERPOLATION));

    pResult->flag = (NNSG3dJntAnmResultFlag) 0;

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_T | NNS_G3D_JNTANM_SRTINFO_BASE_T))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TX)) {
            if (IsDecimalFrame) {
                getTransDataEx_(&pResult->trans.x,
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                getTransData_(&pResult->trans.x,
                              Frame,
                              pData,
                              pJntAnm);
            }

            pData += 2;
        } else {
            pResult->trans.x = *(fx32 *)pData;
            pData += 1;
        }

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TY)) {
            if (IsDecimalFrame) {
                getTransDataEx_(&pResult->trans.y,
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                getTransData_(&pResult->trans.y,
                              Frame,
                              pData,
                              pJntAnm);
            }

            pData += 2;
        } else {
            pResult->trans.y = *(fx32 *)pData;
            pData += 1;
        }

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TZ)) {

            if (IsDecimalFrame) {
                getTransDataEx_(&pResult->trans.z,
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                getTransData_(&pResult->trans.z,
                              Frame,
                              pData,
                              pJntAnm);
            }

            pData += 2;
        } else {
            pResult->trans.z = *(fx32 *)pData;
            pData += 1;
        }
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_T) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO;
        } else {
            getMdlTrans_(pResult);
        }
    }

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_R | NNS_G3D_JNTANM_SRTINFO_BASE_R))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_R)) {

            if (IsDecimalFrame) {
                getRotDataEx_(&pResult->rot,
                              Frame,
                              pData,
                              pJntAnm);
            } else {
                func_02032c5c(&pResult->rot,
                            Frame,
                            pData,
                            pJntAnm);
            }

            pData += 2;
        } else {
            if (getRotDataByIdx_(&pResult->rot,
                                 (void *)((u8 *)pJntAnm + pJntAnm->ofsRot3),
                                 (void *)((u8 *)pJntAnm + pJntAnm->ofsRot5),
                                 (NNSG3dJntAnmRIdx) * pData)) {
                vecCross_((const VecFx32 *)&pResult->rot._00,
                          (const VecFx32 *)&pResult->rot._10,
                          (VecFx32 *)&pResult->rot._20);
            }

            pData += 1;
        }
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_R) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO;
        } else {
            func_020320f8(pResult);
        }
    }

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_S | NNS_G3D_JNTANM_SRTINFO_BASE_S))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SX)) {

            fx32 sx_invsx[2];
            if (IsDecimalFrame) {
                func_02032ac8(&sx_invsx[0],
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                func_020328e0(&sx_invsx[0],
                              Frame,
                              pData,
                              pJntAnm);
            }
            *(pS_invS + 0) = sx_invsx[0];
            *(pS_invS + 3) = sx_invsx[1];
        } else {
            const fx32 * p_fx32 = (const fx32 *)pData;

            *(pS_invS + 0) = *(p_fx32 + 0);
            *(pS_invS + 3) = *(p_fx32 + 1);
        }

        pData += 2;

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SY)) {

            fx32 sy_invsy[2];
            if (IsDecimalFrame) {
                func_02032ac8(&sy_invsy[0],
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                func_020328e0(&sy_invsy[0],
                              Frame,
                              pData,
                              pJntAnm);
            }
            *(pS_invS + 1) = sy_invsy[0];
            *(pS_invS + 4) = sy_invsy[1];
        } else {
            const fx32 * p_fx32 = (const fx32 *)pData;

            *(pS_invS + 1) = *(p_fx32 + 0);
            *(pS_invS + 4) = *(p_fx32 + 1);

        }

        pData += 2;

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SZ)) {

            fx32 sz_invsz[2];
            if (IsDecimalFrame) {
                func_02032ac8(&sz_invsz[0],
                                Frame,
                                pData,
                                pJntAnm);
            } else {
                func_020328e0(&sz_invsz[0],
                              Frame,
                              pData,
                              pJntAnm);
            }
            *(pS_invS + 2) = sz_invsz[0];
            *(pS_invS + 5) = sz_invsz[1];
        } else {
            const fx32 * p_fx32 = (const fx32 *)pData;

            *(pS_invS + 2) = *(p_fx32 + 0);
            *(pS_invS + 5) = *(p_fx32 + 1);
        }

        pData += 2;
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_S) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE;
        } else {
            getMdlScale_(pResult);
            return;
        }
    }
GET_JOINTSCALE:

    (*data_020d6af4->funcJntScale)(
        pResult,
        pS_invS,
        data_020d6af4->c,
        ((pResult->flag & NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE) ?
         NNS_G3D_SRTFLAG_SCALE_ONE :
         0)
        );
}

void getTransData_ (fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm)
{
    u32 frame = (u32)FX_Whole(Frame);
    const void * pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    NNSG3dJntAnmTInfo info = (NNSG3dJntAnmTInfo) * pData;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (!(info & NNS_G3D_JNTANM_TINFO_STEP_MASK)) {
        idx = frame;
        goto TRANS_NONINTERP;
    }

    last_interp = ((u32)info & NNS_G3D_JNTANM_TINFO_LAST_INTERP_MASK) >>
                  NNS_G3D_JNTANM_TINFO_LAST_INTERP_SHIFT;

    if (info & NNS_G3D_JNTANM_TINFO_STEP_2) {

        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto TRANS_NONINTERP;
            } else {
                idx = frame >> 1;
                goto TRANS_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto TRANS_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto TRANS_NONINTERP;
            }

            if (frame & 1) {
                fx32 v, v_sub;
                if (frame & 2) {
                    idx_sub = (frame >> 2);
                    idx = idx_sub + 1;
                } else {
                    idx = (frame >> 2);
                    idx_sub = idx + 1;
                }

                if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
                    const fx16 * p_fx16 = (const fx16 *)pArray;

                    v = *(p_fx16 + idx);
                    v_sub = *(p_fx16 + idx_sub);
                    *pVal = (v + v + v + v_sub) >> 2;
                } else {
                    const fx32 * p_fx32 = (const fx32 *)pArray;

                    v = *(p_fx32 + idx);
                    v_sub = *(p_fx32 + idx_sub);

                    *pVal = (fx32)(((fx64)v + v + v + v_sub) >> 2);
                }
                return;
            } else {
                idx = frame >> 2;
                goto TRANS_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto TRANS_NONINTERP;
        }
    }
TRANS_INTERP_2:
    if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
        const fx16 * p_fx16 = (const fx16 *)pArray;

        *pVal = (*(p_fx16 + idx) + *(p_fx16 + idx + 1)) >> 1;
    } else {
        const fx32 * p_fx32 = (const fx32 *)pArray;

        fx32 v1 = *(p_fx32 + idx) >> 1;
        fx32 v2 = *(p_fx32 + idx + 1) >> 1;
        *pVal = v1 + v2;
    }
    return;
TRANS_NONINTERP:
    if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
        *pVal = *((const fx16 *)pArray + idx);
    } else {
        *pVal = *((const fx32 *)pArray + idx);
    }
    return;
}

void getTransDataEx_ (fx32 * pVal, fx32 Frame, const u32 * pData, const NNSG3dResJntAnm * pJntAnm)
{
    const void * pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    NNSG3dJntAnmTInfo info = (NNSG3dJntAnmTInfo) * pData;

    u32 last_interp;
    u32 idx;
    fx32 remainder;
    int step;
    u32 step_shift;
    u32 frame;

    frame = (u32)FX_Whole(Frame);

    if (frame == pJntAnm->numFrame - 1) {

        if (!(info & NNS_G3D_JNTANM_TINFO_STEP_MASK)) {
            idx = frame;
        } else if (info & NNS_G3D_JNTANM_TINFO_STEP_2)   {
            idx = (frame >> 1) + (frame & 1);
        } else {
            idx = (frame >> 2) + (frame & 3);
        }

        if (pJntAnm->flag & NNS_G3D_JNTANM_OPTION_END_TO_START_INTERPOLATION) {
            fx32 v0, v1;
            remainder = Frame & (FX32_ONE - 1);

            if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
                const fx16 * p_fx16 = (const fx16 *)pArray;

                v0 = *(p_fx16 + idx);
                v1 = *p_fx16;
            } else {
                const fx32 * p_fx32 = (const fx32 *)pArray;

                v0 = *(p_fx32 + idx);
                v1 = *p_fx32;
            }

            *pVal = v0 + (((v1 - v0) * remainder) >> FX32_SHIFT);
            return;
        } else {
            if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
                *pVal = *((const fx16 *)pArray + idx);
            } else {
                *pVal = *((const fx32 *)pArray + idx);
            }
            return;
        }
    }

    if (!(info & NNS_G3D_JNTANM_TINFO_STEP_MASK)) {
        goto TRANS_EX_0;
    }

    last_interp = ((u32)info & NNS_G3D_JNTANM_TINFO_LAST_INTERP_MASK) >>
                  NNS_G3D_JNTANM_TINFO_LAST_INTERP_SHIFT;

    if (info & NNS_G3D_JNTANM_TINFO_STEP_2) {
        if (frame >= last_interp) {
            idx = (last_interp >> 1);
            goto TRANS_EX_0_1;
        } else {
            idx = frame >> 1;
            remainder = Frame & (FX32_ONE * 2 - 1);
            step = 2;
            step_shift = 1;
            goto TRANS_EX;
        }
    } else {
        if (frame >= last_interp) {
            idx = (frame >> 2) + (frame & 3);
            goto TRANS_EX_0_1;
        } else {
            idx = frame >> 2;
            remainder = Frame & (FX32_ONE * 4 - 1);
            step = 4;
            step_shift = 2;
            goto TRANS_EX;
        }
    }
TRANS_EX_0:
    idx = (u32)frame;
TRANS_EX_0_1:
    remainder = Frame & (FX32_ONE - 1);
    step = 1;
    step_shift = 0;
TRANS_EX:
    {
        fx32 v0, v1;
        if (info & NNS_G3D_JNTANM_TINFO_FX16ARRAY) {
            const fx16 * p_fx16 = (const fx16 *)pArray;

            v0 = *(p_fx16 + idx);
            v1 = *(p_fx16 + idx + 1);
        } else {
            const fx32 * p_fx32 = (const fx32 *)pArray;

            v0 = *(p_fx32 + idx);
            v1 = *(p_fx32 + idx + 1);
        }

        *pVal = ((v0 * step) + (((v1 - v0) * remainder) >> FX32_SHIFT)) >> step_shift;
    }
    return;
}
