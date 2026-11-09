/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern int func_0200829c(unsigned int value);

extern int data_020cc028;

extern unsigned short data_020cc02c;

void OSi_UnlockVram(unsigned int mask, unsigned short owner) {
    unsigned int mine;
    int enabled = OS_DisableInterrupts();
    int bit;
    unsigned int clear;
    mine = mask & data_020cc028 & 0x1ff;
    for (;;) {
        bit = 0x1f - func_0200829c(mine);
        if (bit < 0) {
            break;
        }
        clear = ~(1 << bit);
        mine &= clear;
        if (owner == (&data_020cc02c)[bit]) {
            (&data_020cc02c)[bit] = 0;
            data_020cc028 &= clear;
        }
    }
    OS_RestoreInterrupts(enabled);
}
