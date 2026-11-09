/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    unsigned short active;
    char _2[2];
    void *unk4;
    void *unk8;
} Data_02044674;

extern void func_02007970(int);

extern void OS_DisableIrqMask(unsigned int);

extern Data_02044674 data_020cc004;

void OS_InitAlarm(void)
{
    if (data_020cc004.active != 0)
        return;

    data_020cc004.active = 1;
    func_02007970(1);
    data_020cc004.unk4 = 0;
    data_020cc004.unk8 = 0;
    OS_DisableIrqMask(0x10);
}
