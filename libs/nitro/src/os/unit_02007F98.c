/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_DisableIrqMask();

extern struct {
    unsigned short state;
    unsigned short pad;
    int field_4;
    int field_8;
    int field_c;
    int field_10;
} data_020cc010;

void OS_InitVAlarm(void) {
    if (data_020cc010.state != 0) return;
    data_020cc010.state = 1;
    data_020cc010.field_c = 0;
    data_020cc010.field_10 = 0;
    OS_DisableIrqMask(4);
    data_020cc010.field_8 = 0;
    data_020cc010.field_4 = 0;
}
