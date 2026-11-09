/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/wm.h"

#define PXI_FIFO_TAG_WM         10

#define PXI_PROC_ARM7           1

#define MI_DMA_MAX_NUM          3

#define wmInitialized data_ov105_020bfa20

#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

#define MI_CpuClear32(dst, size) func_02008c14(0, (dst), (size))

#define MI_CpuCopy32(src, dst, size) MIi_CpuCopy32((src), (dst), (size))

extern u16 data_ov105_020bfa20;

extern WMArm9Buf *func_020117c0(void);

extern WMErrCode Ov105_WMi_CheckInitialized(void);

extern WMErrCode Ov105_WMi_CheckIdle(void);

extern WMErrCode func_02011834(s32 paramNum, ...);

extern WMErrCode func_020116a4(WMApiid id, u16 paramNum, ...);

extern WMErrCode Ov105_WMi_SendCommandDirect(void *data, u32 length);

extern void func_02011634(WMApiid id, WMCallbackFunc callback);

extern int Ov105_WM_GetMPSendBufferSize(void);

extern int Ov105_WM_GetMPReceiveBufferSize(void);

extern void DC_InvalidateRange(void *addr, u32 size);

extern void DC_StoreRange(void *addr, u32 size);

extern void func_02008c14(u32 value, void *dst, u32 size);

extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

extern WMErrCode func_02012c6c(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, WMMPTmpParam *tmpParam);

WMErrCode func_02012e80(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, u16 mpFreq)
{
    WMMPTmpParam tmpParam;

    MI_CpuClear32(&tmpParam, sizeof(tmpParam));

    tmpParam.mask = WM_MP_TMP_PARAM_FREQUENCY | WM_MP_TMP_PARAM_MIN_FREQUENCY;
    tmpParam.minFrequency = mpFreq;
    tmpParam.frequency = mpFreq;

    return func_02012c6c(callback, recvBuf, recvBufSize, sendBuf, sendBufSize, &tmpParam);
}

WMErrCode func_02012ee8(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio)
{
    WMErrCode result;
    BOOL isParent;
    u16 mpReadyBitmap = 0x0001;
    u16 childBitmap = 0x0001;
    WMArm9Buf *p = func_020117c0();
    WMStatus *status = p->status;

    result = func_02011834(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
    WM_CHECK_RESULT(result);

    DC_InvalidateRange(&(status->aid), 2);
    isParent = (status->aid == 0) ? TRUE : FALSE;

    if (isParent == TRUE) {
        DC_InvalidateRange(&(status->child_bitmap), 2);
        childBitmap = status->child_bitmap;
        DC_InvalidateRange(&(status->mp_readyBitmap), 2);
        mpReadyBitmap = status->mp_readyBitmap;
    }

    if (sendData == NULL) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (childBitmap == 0) {
        return WM_ERRCODE_NO_CHILD;
    }

    DC_InvalidateRange(&(status->mp_sendBuf), 2);

    if ((void *)sendData == (void *)status->mp_sendBuf) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (sendDataSize > WM_SIZE_MP_DATA_MAX) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (sendDataSize == 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    DC_StoreRange((void *)sendData, sendDataSize);

    result = func_020116a4(WM_APIID_SET_MP_DATA, 7,
                                 (u32)sendData,
                                 (u32)sendDataSize,
                                 (u32)destBitmap, (u32)port, (u32)prio, (u32)callback, (u32)arg);
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}

WMErrCode func_02013018(WMCallbackFunc callback)
{
    WMErrCode result;
    WMArm9Buf *p = func_020117c0();

    result = func_02011834(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
    WM_CHECK_RESULT(result);

    DC_InvalidateRange(&(p->status->mp_flag), 4);
    if (p->status->mp_flag == FALSE) {
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    func_02011634(WM_APIID_END_MP, callback);

    result = func_020116a4(WM_APIID_END_MP, 0);
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}
