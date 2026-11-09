/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)

extern OSiIrqSlot data_020cbc5c[];

extern unsigned int data_027e0000;

OSIrqFunction OS_GetIrqFunction(unsigned int intrBits)
{
    int i;
    OSIrqFunction *entry = OSi_IrqTable;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1, entry++) {
        if (intrBits & 1) {
            if (i >= 8 && i <= 11) {
                return data_020cbc5c[i - 8].pfnHandler;
            }
            if (i >= 3 && i <= 6) {
                return data_020cbc5c[i + 1].pfnHandler;
            }
            return *entry;
        }
    }
    return 0;
}
