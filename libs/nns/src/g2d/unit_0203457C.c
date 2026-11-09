/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/fs.h"

#include "nitro/wm.h"

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

void NNSi_G2dUnpackUserExCellAttrBank(NNSG2dUserExCellAttrBank * pCellAttrBank);

void NNS_G2dUnpackNCE(NNSG2dCellDataBank * pCellData);

NNSG2dBinaryBlockHeader * NNS_G2dFindBinaryBlock(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);

extern void NNS_G2dUnpackNCE (NNSG2dCellDataBank * pCellData);

const NNSG2dCellData * NNS_G2dGetCellDataByIdx(const NNSG2dCellDataBank * pCellData, u16 idx);

extern void * GetPtrOamArrayHead_ (NNSG2dCellDataBank * pCellBank);

extern void UnpackExtendedData_ (void * pExData);

extern const NNSG2dCellData * NNS_G2dGetCellDataByIdx (const NNSG2dCellDataBank * pCellData, u16 idx);

extern struct WBTContext;

extern struct WBTCommandList;

extern struct WFSClientContext;

inline BOOL NNSi_G2dCellBankHasBR (const NNSG2dCellDataBank * pCellBank)
{
    return (BOOL)(pCellBank->cellBankAttr & 0x1 );
}

static inline void BitReaderReload (NNSiG2dBitReader * reader)
{
    reader->bits = *(reader->src)++;
    reader->availableBits = 8;
}

void * GetPtrOamArrayHead_ (NNSG2dCellDataBank * pCellBank)
{

    if (NNSi_G2dCellBankHasBR(pCellBank)) {
        return (NNSG2dCellDataWithBR *)(pCellBank->pCellDataArrayHead) + pCellBank->numCells;
    } else {
        return pCellBank->pCellDataArrayHead + pCellBank->numCells;
    }
}

void UnpackExtendedData_ (void * pExData)
{
    {
        NNSG2dUserExDataBlock * pBlk = (NNSG2dUserExDataBlock *)pExData;
        NNSG2dUserExCellAttrBank * pCellAttrBank = (NNSG2dUserExCellAttrBank *)(pBlk + 1);

        NNSi_G2dUnpackUserExCellAttrBank(pCellAttrBank);
    }
}

BOOL NNS_G2dGetUnpackedCellBank (void * pNcerFile, NNSG2dCellDataBank ** ppCellBank)
{

    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNcerFile;
        {
            NNSG2dCellDataBankBlock * pBinBlk =
                (NNSG2dCellDataBankBlock *)NNS_G2dFindBinaryBlock(pBinFile,
                                                                  NNS_G2D_BLKSIG_CELLBANK);
            if (pBinBlk) {
                NNS_G2dUnpackNCE((void *)&pBinBlk->cellDataBank);
                *ppCellBank = &pBinBlk->cellDataBank;
                return TRUE;
            } else {
                *ppCellBank = NULL;
                return FALSE;

            }
        }
    }
}

const NNSG2dCellData * NNS_G2dGetCellDataByIdx (const NNSG2dCellDataBank * pCellData, u16 idx)
{

    if (idx >= pCellData->numCells) {
        return NULL;
    }

    if (NNSi_G2dCellBankHasBR(pCellData)) {
        const NNSG2dCellDataWithBR * pCellBR =
            (const NNSG2dCellDataWithBR *)(pCellData->pCellDataArrayHead) + idx;
        return &pCellBR->cellData;
    } else {
        return pCellData->pCellDataArrayHead + idx;
    }
}

void NNS_G2dUnpackNCE (NNSG2dCellDataBank * pCellData)
{
    {
        pCellData->pCellDataArrayHead = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pCellDataArrayHead, pCellData);

        {
            void * pHeadOfOAMData = GetPtrOamArrayHead_(pCellData);

            u16 i;
            NNSG2dCellData * pCell = NULL;
            for (i = 0; i < pCellData->numCells; i++) {
                pCell = (NNSG2dCellData *)(NNS_G2dGetCellDataByIdx(pCellData, i));
                pCell->pOamAttrArray = NNS_G2D_UNPACK_OFFSET_PTR(pCell->pOamAttrArray, pHeadOfOAMData);
            }
        }

        if (pCellData->pVramTransferData != NULL) {
            NNSG2dVramTransferData * pVramTsfmData = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pVramTransferData, pCellData);

            pVramTsfmData->pCellTransferDataArray = NNS_G2D_UNPACK_OFFSET_PTR(pVramTsfmData->pCellTransferDataArray, pVramTsfmData);
            pCellData->pVramTransferData = pVramTsfmData;
        }

        if (pCellData->pExtendedData != NULL) {
            pCellData->pExtendedData = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pExtendedData, pCellData);
            UnpackExtendedData_(pCellData->pExtendedData);
        }

    }

}

u32 NNSi_G2dBitReaderRead (NNSiG2dBitReader * reader, int nBits)
{
    u32 val = reader->bits;
    int nAvlBits = reader->availableBits;

    if (nAvlBits < nBits) {
        int lack = nBits - nAvlBits;
        val <<= lack;
        BitReaderReload(reader);
        val |= NNSi_G2dBitReaderRead(reader, lack);
    } else {
        val >>= (nAvlBits - nBits);
        reader->availableBits = (s8)(nAvlBits - nBits);
    }

    val &= 0xFF >> (8 - nBits);
    return val;
}

unsigned short NNSi_G2dSplitCharUTF16(unsigned short **ppChar)
{
    unsigned short *q = *ppChar;
    unsigned short v = *q++;
    *ppChar = q;
    return v;
}
