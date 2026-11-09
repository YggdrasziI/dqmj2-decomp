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

extern WMErrCode func_020117ec(void);

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);

extern WMErrCode func_020116a4(WMApiid id, u16 paramNum, ...);

extern WMErrCode Ov105_WMi_SendCommandDirect(void *data, u32 length);

extern void func_02011634(WMApiid id, WMCallbackFunc callback);

extern int Ov105_WM_GetMPSendBufferSize(void);

extern int Ov105_WM_GetMPReceiveBufferSize(void);

extern void DC_InvalidateRange(void *addr, u32 size);

extern void DC_StoreRange(void *addr, u32 size);

extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *dst, u32 size);

extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

WMErrCode func_02013e08(WMCallbackFunc callback, u16 wepmode, const u16 *wepkey)
{
    WMErrCode result;

    result = func_020117ec();
    WM_CHECK_RESULT(result);

    if (wepmode > 3) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (wepmode != WM_WEPMODE_NO) {
        if (wepkey == NULL) {
            return WM_ERRCODE_INVALID_PARAM;
        }

        DC_StoreRange((void *)wepkey, WM_SIZE_WEPKEY);
    }

    func_02011634(WM_APIID_SET_WEPKEY, callback);

    result = func_020116a4(WM_APIID_SET_WEPKEY, 2, (u32)wepmode, (u32)wepkey);
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}
