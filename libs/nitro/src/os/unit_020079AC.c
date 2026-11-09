/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#define TM0CNT_L (*(volatile unsigned short *)0x04000100)

#define TM0CNT_H (*(volatile unsigned short *)0x04000102)

typedef struct {
    unsigned short active;
    unsigned short _pad;
    int field_4;
    int field_8;
    int field_c;
} Data_02044664;

extern void func_02007970(int timer);

extern void OS_SetIrqFunction(unsigned int mask, void (*callback)(void));

extern unsigned int OS_EnableIrqMask(unsigned int mask);

extern void OSi_CountUpTick(void);

extern Data_02044664 data_020cbff4;

void OS_InitTick(void)
{
    if (data_020cbff4.active != 0)
        return;

    data_020cbff4.active = 1;
    func_02007970(0);
    data_020cbff4.field_8 = 0;
    data_020cbff4.field_c = 0;
    TM0CNT_H = 0;
    TM0CNT_L = 0;
    TM0CNT_H = 0xC1;
    OS_SetIrqFunction(8, OSi_CountUpTick);
    OS_EnableIrqMask(8);
    data_020cbff4.field_4 = 0;
}
