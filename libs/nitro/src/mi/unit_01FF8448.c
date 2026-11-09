/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

struct DmaChannel {
    unsigned int src;
    unsigned int dst;
    unsigned int ctrl;
};

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int);

void MIi_DmaSetParams(unsigned int dmaNo, unsigned int src, unsigned int dest, unsigned int ctrl) {
    int mask = OS_DisableInterrupts();
    volatile unsigned int *p = (volatile unsigned int *)(0x040000B0 + dmaNo * 12);
    *p = (volatile unsigned int)src;
    *(p + 1) = (volatile unsigned int)dest;
    *(p + 2) = (volatile unsigned int)ctrl;
    OS_RestoreInterrupts(mask);
}

void func_01ff8488(unsigned int dmaNo, unsigned int src, unsigned int dest, unsigned int ctrl) {
    int mask = OS_DisableInterrupts();
    volatile unsigned int *p = (volatile unsigned int *)(0x040000B0 + dmaNo * 12);
    *p = (volatile unsigned int)src;
    *(p + 1) = (volatile unsigned int)dest;
    *(p + 2) = (volatile unsigned int)ctrl;
    (void)*(volatile unsigned int *)0x040000B0;
    (void)*(volatile unsigned int *)0x040000B0;
    if (dmaNo == 0) {
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    OS_RestoreInterrupts(mask);
}

void MIi_DmaSetChannelRegs(int ch, unsigned int src, unsigned int dst, unsigned int ctrl)
{
    struct DmaChannel *p = (struct DmaChannel *)0x40000b0;
    volatile unsigned int *q = &p[ch].dst;
    p[ch].src = src;
    q[0] = dst;
    q[1] = ctrl;
}

void func_01ff851c(u32 channel, u32 source, u32 destination, u32 control)
{
    vu32 *registers = (vu32 *)(0x040000b0 + channel * 12);

    registers[0] = source;
    registers[1] = destination;
    registers[2] = control;

    (void)*(vu32 *)0x040000b0;
    (void)*(vu32 *)0x040000b0;

    if (channel == 0) {
        registers[0] = 0;
        registers[1] = 0;
        registers[2] = 0x81400001;
    }

    (void)*(vu32 *)0x040000b0;
    (void)*(vu32 *)0x040000b0;
}
