/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/fs.h"

#include "nitro/wm.h"

#include "nnsys/g3d.h"

#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#include "nitro/mi.h"

#include "nitro/fx_types.h"

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

extern struct WBTContext;

extern struct WBTCommandList;

extern struct WFSClientContext;

inline const NNSG3dResName * NNS_G3dGetResNameByIdx(const NNSG3dResDict * dict, u32 idx);

inline void * NNS_G3dGetResDataByIdx(const NNSG3dResDict * dict, u32 idx);

const NNSG3dResDictTexPatAnmData * NNSi_G3dGetTexPatAnmDataByIdx(const NNSG3dResTexPatAnm * pPatAnm, u32 idx);

extern const NNSG3dResDictTexPatAnmData * NNSi_G3dGetTexPatAnmDataByIdx (const NNSG3dResTexPatAnm * pPatAnm, u32 idx);

void FX_DivAsync(fx32 numer, fx32 denom);

fx32 FX_GetDivResult(void);

inline const NNSG3dResName * NNS_G3dGetResNameByIdx (const NNSG3dResDict * dict, u32 idx)
{
    NNSG3dResDictEntryHeader * hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (NNSG3dResName *)((u8 *)hdr +
                                 hdr->ofsName +
                                 sizeof(NNSG3dResName) * idx);
    } else {
        return NULL ;
    }
}

inline void * NNS_G3dGetResDataByIdx (const NNSG3dResDict * dict, u32 idx)
{
    NNSG3dResDictEntryHeader * hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL ;
    }
}

void * NNS_G3dGetResDataByName (const NNSG3dResDict * dict, const NNSG3dResName * name)
{

    if (!name)
        return NULL;

    if (dict->numEntry < 16) {
        u32 idx;
        const NNSG3dResName * n;
        u32 v0 = name->val[0];
        u32 v1 = name->val[1];
        u32 v2 = name->val[2];
        u32 v3 = name->val[3];

        for (idx = 0; idx < dict->numEntry; ++idx) {
            n = NNS_G3dGetResNameByIdx(dict, idx);
            if (n->val[0] == v0 &&
                n->val[1] == v1 &&
                n->val[2] == v2 &&
                n->val[3] == v3) {
                return NNS_G3dGetResDataByIdx(dict, idx);
            }
        }
    } else {
        const NNSG3dResName * n;
        const NNSG3dResDictTreeNode * treeBase;
        const NNSG3dResDictTreeNode * p, * x;

        treeBase = &dict->node[0];
        p = treeBase;

        if (p->idxLeft != 0) {
            x = treeBase + p->idxLeft;
            while (p->refBit > x->refBit) {
                p = x;

                x = treeBase + *(&x->idxLeft +
                                 ((name->val[x->refBit >> 5] >> (x->refBit & 31)) & 1));
            }

            n = NNS_G3dGetResNameByIdx(dict, x->idxEntry);

            if (n->val[0] == name->val[0] &&
                n->val[1] == name->val[1] &&
                n->val[2] == name->val[2] &&
                n->val[3] == name->val[3]) {
                return NNS_G3dGetResDataByIdx(dict, x->idxEntry);
            }
        }
    }
    return NULL;
}

int NNS_G3dGetResDictIdxByName (const NNSG3dResDict * dict, const NNSG3dResName * name)
{

    if (!name)
        return -1;

    if (dict->numEntry < 16) {
        u32 idx;
        const NNSG3dResName * n;
        u32 v0 = name->val[0];
        u32 v1 = name->val[1];
        u32 v2 = name->val[2];
        u32 v3 = name->val[3];

        for (idx = 0; idx < dict->numEntry; ++idx) {
            n = NNS_G3dGetResNameByIdx(dict, idx);
            if (n->val[0] == v0 &&
                n->val[1] == v1 &&
                n->val[2] == v2 &&
                n->val[3] == v3) {
                return (int)idx;
            }
        }
    } else {
        const NNSG3dResName * n;
        const NNSG3dResDictTreeNode * treeBase;
        const NNSG3dResDictTreeNode * p, * x;

        treeBase = &dict->node[0];

        p = treeBase;

        if (p->idxLeft != 0) {
            x = treeBase + p->idxLeft;
            while (p->refBit > x->refBit) {
                p = x;
                x = treeBase + *(&x->idxLeft +
                                 ((name->val[x->refBit >> 5] >> (x->refBit & 31)) & 1));
            }

            n = NNS_G3dGetResNameByIdx(dict, x->idxEntry);

            if (n->val[0] == name->val[0] &&
                n->val[1] == name->val[1] &&
                n->val[2] == name->val[2] &&
                n->val[3] == name->val[3]) {
                return x->idxEntry;
            }
        }
    }
    return -1;
}

NNSG3dResMdlSet * NNS_G3dGetMdlSet (const NNSG3dResFileHeader * header)
{
    u32 * blks;

    blks = (u32 *)((u8 *)header + header->headerSize);
    return (NNSG3dResMdlSet *)((u8 *)header + blks[0]);
}

NNSG3dResTex * NNS_G3dGetTex (const NNSG3dResFileHeader * header)
{
    u32 * blks;

    blks = (u32 *)((u8 *)header + header->headerSize);

    if (header->dataBlocks == 1) {
        if (header->sigVal == NNS_G3D_SIGNATURE_NSBTX) {
            return (NNSG3dResTex *)((u8 *)header + blks[0]);
        } else {
            return NULL;
        }
    } else {
        return (NNSG3dResTex *)((u8 *)header + blks[1]);
    }
}

void * NNS_G3dGetAnmByIdx (const void * pRes, u32 idx)
{

    if (pRes) {
        const NNSG3dResFileHeader * header;
        const NNSG3dResAnmSet * anmSet;
        const NNSG3dResDictAnmSetData * anmSetData;
        u32 * blks;

        header = (const NNSG3dResFileHeader *) pRes;
        blks = (u32 *)((u8 *)header + header->headerSize);

        anmSet = (const NNSG3dResAnmSet *)((u8 *)header + blks[0]);
        anmSetData = (const NNSG3dResDictAnmSetData *)NNS_G3dGetResDataByIdx(&anmSet->dict, idx);

        if (anmSetData) {
            return (void *)((u8 *)anmSet + anmSetData->offset);
        }
    }

    return NULL;
}

const NNSG3dResName * NNSi_G3dGetTexPatAnmTexNameByIdx (const NNSG3dResTexPatAnm * pPatAnm, u8 texIdx)
{

    if (pPatAnm && texIdx < pPatAnm->numTex) {
        const NNSG3dResName * pNameArray
            = (const NNSG3dResName *)((const u8 *)pPatAnm + pPatAnm->ofsTexName);

        return &pNameArray[texIdx];
    }

    return NULL;
}

const NNSG3dResName * NNSi_G3dGetTexPatAnmPlttNameByIdx (const NNSG3dResTexPatAnm * pPatAnm, u8 plttIdx)
{

    if (pPatAnm && plttIdx < pPatAnm->numPltt) {
        const NNSG3dResName * pNameArray
            = (const NNSG3dResName *)((const u8 *)pPatAnm + pPatAnm->ofsPlttName);

        return &pNameArray[plttIdx];
    }

    return NULL;
}

const NNSG3dResTexPatAnmFV * NNSi_G3dGetTexPatAnmFV (const NNSG3dResTexPatAnm * pPatAnm, u32 idx, u32 frame)
{
    {
        const NNSG3dResDictTexPatAnmData * pAnmData =
            NNSi_G3dGetTexPatAnmDataByIdx(pPatAnm, idx);
        {

            const NNSG3dResTexPatAnmFV * pfvArray
                = (const NNSG3dResTexPatAnmFV *)((u8 *)pPatAnm + pAnmData->offset);

            const u32 fvIdx = (u32)((fx32)pAnmData->ratioDataFrame * frame >> FX32_SHIFT);

            {
                u32 realFvIdx = fvIdx;

                while (realFvIdx > 0 && pfvArray[ realFvIdx ].idxFrame >= frame) {
                    realFvIdx--;
                }

                while (realFvIdx + 1 < pAnmData->numFV && pfvArray[ realFvIdx + 1 ].idxFrame <= frame) {
                    realFvIdx++;
                }

                return &pfvArray[realFvIdx];
            }
        }
    }
}

const NNSG3dResDictTexPatAnmData * NNSi_G3dGetTexPatAnmDataByIdx (const NNSG3dResTexPatAnm * pPatAnm, u32 idx)
{
    return (const NNSG3dResDictTexPatAnmData *)NNS_G3dGetResDataByIdx(&pPatAnm->dict, idx);
}

void func_0202bc6c (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;
    fx32 ss_sin, ss_cos, st_sin, st_cos;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    ss_cos = (fx32)((fx64)anm->scaleS * anm->cosR >> FX32_SHIFT);
    ss_sin = (fx32)((fx64)anm->scaleS * anm->sinR >> FX32_SHIFT);
    st_cos = (fx32)((fx64)anm->scaleT * anm->cosR >> FX32_SHIFT);
    st_sin = (fx32)((fx64)anm->scaleT * anm->sinR >> FX32_SHIFT);

    m->_00 = ss_cos;
    m->_11 = st_cos;

    m->_01 = st_sin * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    p = (-anm->origWidth << (FX32_SHIFT - 1)) - anm->transS * anm->origWidth;
    q = (-anm->origHeight << (FX32_SHIFT - 1)) + anm->transT * anm->origHeight;

    m->_30 = (fx32)(((fx64)ss_cos * p - (fx64)ss_sin * q) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)st_sin * p + (fx64)st_cos * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = -ss_sin * FX_GetDivResult() >> FX32_SHIFT;
}

void func_0202bd74 (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    m->_00 = anm->cosR;
    m->_11 = anm->cosR;

    m->_01 = anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    p = (-anm->origWidth << (FX32_SHIFT - 1)) - anm->transS * anm->origWidth;
    q = (-anm->origHeight << (FX32_SHIFT - 1)) + anm->transT * anm->origHeight;

    m->_30 = (fx32)(((fx64)anm->cosR * p - (fx64)anm->sinR * q) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)anm->sinR * p + (fx64)anm->cosR * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = -anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
}

void func_0202be5c (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;

    m->_00 = anm->scaleS;
    m->_11 = anm->scaleT;

    m->_01 = 0;

    p = (-anm->origWidth << (FX32_SHIFT - 1)) - anm->transS * anm->origWidth;
    q = (-anm->origHeight << (FX32_SHIFT - 1)) + anm->transT * anm->origHeight;

    m->_30 = (fx32)(((fx64)anm->scaleS * p) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)anm->scaleT * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = 0;
}

void func_0202bedc (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = FX32_ONE;
    m->_11 = FX32_ONE;

    m->_01 = 0;

    m->_30 = (-anm->transS * anm->origWidth) << 4;
    m->_31 = (anm->transT * anm->origHeight) << 4;

    m->_10 = 0;
}

void func_0202bf24 (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;
    fx32 ss_sin, ss_cos, st_sin, st_cos;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    ss_cos = (fx32)((fx64)anm->scaleS * anm->cosR >> FX32_SHIFT);
    ss_sin = (fx32)((fx64)anm->scaleS * anm->sinR >> FX32_SHIFT);
    st_cos = (fx32)((fx64)anm->scaleT * anm->cosR >> FX32_SHIFT);
    st_sin = (fx32)((fx64)anm->scaleT * anm->sinR >> FX32_SHIFT);

    m->_00 = ss_cos;
    m->_11 = st_cos;

    m->_01 = st_sin * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    p = (-anm->origWidth << (FX32_SHIFT - 1));
    q = (-anm->origHeight << (FX32_SHIFT - 1));

    m->_30 = (fx32)(((fx64)ss_cos * p - (fx64)ss_sin * q) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)st_sin * p + (fx64)st_cos * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = -ss_sin * FX_GetDivResult() >> FX32_SHIFT;
}

void func_0202c01c (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    m->_00 = anm->cosR;
    m->_11 = anm->cosR;

    m->_01 = anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    p = (-anm->origWidth << (FX32_SHIFT - 1));
    q = (-anm->origHeight << (FX32_SHIFT - 1));

    m->_30 = (fx32)(((fx64)anm->cosR * p - (fx64)anm->sinR * q) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)anm->sinR * p + (fx64)anm->cosR * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = -anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
}

void func_0202c0f4 (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = anm->scaleS;
    m->_11 = anm->scaleT;

    m->_01 = 0;

    m->_30 = ((-anm->scaleS + FX32_ONE) * anm->origWidth) << 3;
    m->_31 = ((-anm->scaleT + FX32_ONE) * anm->origHeight) << 3;

    m->_10 = 0;
}
