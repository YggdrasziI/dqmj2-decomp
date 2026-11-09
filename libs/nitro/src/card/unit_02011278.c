/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/card.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void OS_Terminate();

extern void OS_Terminate(void);

extern void OS_SpinWait(u32 cycle);

void MI_StopDma(u32 dmaNo);

u32 func_0200ea38(void);

extern void CARDi_SendtoPxi(u32 data, u32 wait);

extern void CARDi_SendtoPxi (u32 data, u32 wait);

static inline BOOL PAD_DetectFold (void)
{
    return (BOOL)((*(vu16 *)(0x02000000 + 0x007fffa8) & 0x8000 ) >> 15);
}

void CARD_TerminateForPulledOut (void)
{
#ifndef SDK_TEG
	BOOL should_be_halt = TRUE;

	MI_StopDma(0);
	MI_StopDma(1);
	MI_StopDma(2);
	MI_StopDma(3);

	if (PAD_DetectFold()) {
		u32 res;
		while ((res = func_0200ea38()) == SPI_PXI_RESULT_EXCLUSIVE) {
			OS_SpinWait(HW_CPU_CLOCK_ARM9 / 100);
		}
		if (res == PM_RESULT_SUCCESS) {
			should_be_halt = FALSE;
		}
	}

	if (should_be_halt) {
		CARDi_SendtoPxi(CARD_PXI_COMMAND_TERMINATE, 1);
	}
#endif

	OS_Terminate();
}
