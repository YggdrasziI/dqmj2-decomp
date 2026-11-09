/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#define MIi_DmaSetParams_wait func_01ff85d0

#define MIi_GXDmaParams data_020cc040

extern void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);

extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);

extern void MIi_DmaSetParams(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

extern void func_01ff85d0(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

extern void MI_WaitDma(u32 dmaNo);

extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);

extern u32 OS_ResetRequestIrqMask(u32 intr);

extern void OS_Terminate(void);

extern MIiGXDmaParams data_020cc040;

extern void MIi_DMACallback(void *arg);

extern void MIi_DMAFastCallback(void *arg);

static inline void MIi_CallCallback(MIDmaCallback callback, void *arg)
{
    if (callback) {
        (callback)(arg);
    }
}

void MIi_FIFOCallback (void)
{
	u32 length;
	u32 src;

	if (MIi_GXDmaParams.length == 0) {
		return;
	}

	length = (MIi_GXDmaParams.length >= MIi_GX_LENGTH_ONCE) ? MIi_GX_LENGTH_ONCE : MIi_GXDmaParams.length;
	src = MIi_GXDmaParams.src;

	MIi_GXDmaParams.length -= length;
	MIi_GXDmaParams.src += length;

	if (MIi_GXDmaParams.length == 0) {
		OSi_EnterDmaCallback(MIi_GXDmaParams.dmaNo, MIi_DMACallback, NULL);
		MIi_DmaSetParams(MIi_GXDmaParams.dmaNo, src, (u32)REG_GXFIFO_ADDR, MI_CNT_SEND32_IF(length));
		(void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
	} else {
		MIi_DmaSetParams(MIi_GXDmaParams.dmaNo, src, (u32)REG_GXFIFO_ADDR, MI_CNT_SEND32(length));
		(void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
	}
}
