/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

extern void OS_Terminate(void);

void MIi_CheckAnotherAutoDMA(int dmaNo, int timing) {
    int i;
    vu32 *cntp = (vu32 *)0x040000B8;

    for (i = 0; i < 3; i++, cntp += 3) {
        u32 cnt;
        if (i == dmaNo) {
            continue;
        }
        cnt = *cntp;
        if (cnt & 0x80000000) {
            cnt &= 0x38000000;
            if (cnt == (u32)timing) {
                continue;
            }
        } else {
            continue;
        }
        if (cnt == 0x08000000 && timing == 0x10000000) {
            continue;
        }
        if (cnt == 0x10000000 && timing == 0x08000000) {
            continue;
        }
        if (cnt == 0x18000000 || cnt == 0x20000000 || cnt == 0x28000000 ||
            cnt == 0x30000000 || cnt == 0x38000000 || cnt == 0x08000000 ||
            cnt == 0x10000000) {
            OS_Terminate();
        }
    }
}
