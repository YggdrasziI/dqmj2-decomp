/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)

extern OSiIrqSlot data_020cbc5c[];

extern unsigned int data_027e0000;

void OS_SetIrqFunction(unsigned int intrBits, OSIrqFunction function)
{
    int i;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1) {
        if (intrBits & 1) {
            OSiIrqSlot *slot = 0;

            if (i >= 8 && i <= 11) {
                slot = &data_020cbc5c[i - 8];
            } else if (i >= 3 && i <= 6) {
                slot = &data_020cbc5c[i + 1];
            } else {
                OSi_IrqTable[i] = function;
            }

            if (slot != 0) {
                slot->pfnHandler = function;
                slot->pArg = 0;
                slot->bKeepEnabled = 1;
            }
        }
    }
}
