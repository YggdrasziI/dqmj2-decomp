/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nitro/ctrdg.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void OS_Terminate();

extern void OS_Terminate(void);

void CTRDGi_SendtoPxi(u32 data);

extern void CTRDGi_SendtoPxi(u32 data);

void CTRDG_TerminateForPulledOut (void)
{
	CTRDGi_SendtoPxi(CTRDG_PXI_COMMAND_TERMINATE);
	OS_Terminate();
}
