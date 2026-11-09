/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/os.h"

extern unsigned int OS_DisableIrqMask(unsigned int mask);

extern void OS_SetIrqFunction(unsigned int intrBits, OSIrqFunction function);

extern int data_020cc040;

void MIi_DMACallback(void) {
    void (*callback)(void *);
    void *callbackArg;

    OS_DisableIrqMask(0x200000);

    *(volatile unsigned int *)0x04000600 =
        (*(unsigned int *)((char *)&data_020cc040 + 0x18) << 30) |
        (*(volatile unsigned int *)0x04000600 & ~0xc0000000);

    OS_SetIrqFunction(0x200000, *(OSIrqFunction *)((char *)&data_020cc040 + 0x1c));

    data_020cc040 = 0;
    callback = *(void (**)(void *))((int)&data_020cc040 + 0x10);
    callbackArg = *(void **)((int)&data_020cc040 + 0x14);
    if (callback != 0) {
        callback(callbackArg);
    }
}
