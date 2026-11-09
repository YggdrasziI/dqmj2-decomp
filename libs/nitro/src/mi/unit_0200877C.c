/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

void MI_StopDma(unsigned int channel) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned short *ctrl = &((volatile unsigned short *)0x040000b0)[channel * 6 + 5];
    *ctrl &= ~0x3a00;
    *ctrl &= ~0x8000;
    *ctrl;
    *ctrl;
    if (channel == 0) {
        volatile unsigned int *reg = (volatile unsigned int *)(0x040000b0 + channel * 12);
        reg[0] = 0;
        reg[1] = 0;
        reg[2] = 0x81400001;
    }
    OS_RestoreInterrupts(enabled);
}
