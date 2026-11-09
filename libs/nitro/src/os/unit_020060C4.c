/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/hw.h"

void OSi_FreeCardBus(void)
{
    REG_EXMEM_CNT |= 0x0800;
}
