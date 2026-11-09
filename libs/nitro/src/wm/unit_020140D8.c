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

#define MI_CpuClear32(dst, size) INITi_CpuClear32_0x01ff86fc(0, (dst), (size))

#define MI_CpuCopy32(src, dst, size) MIi_CpuCopy32((src), (dst), (size))

extern u16 data_ov105_020bfa20;

extern WMArm9Buf *Ov105_WMi_GetSystemWork(void);

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

extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *dst, u32 size);

extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

WMErrCode func_020140d8(WMCallbackFunc callback, BOOL enabled)
{
    WMErrCode result;

    result = func_02011834(2, WM_STATE_PARENT, WM_STATE_MP_PARENT);
    WM_CHECK_RESULT(result);

    func_02011634(WM_APIID_SET_ENTRY, callback);

    result = func_020116a4(WM_APIID_SET_ENTRY, 1, (u32)enabled);
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}
