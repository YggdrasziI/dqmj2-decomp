/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    unsigned short initialized;
    char _2[0xa];
    int field_c;
    int field_10;
    int field_14;
    int field_18;
    char _1c[0xc];
    int field_28;
} Data_02046438;

extern void func_0200a2c4(void);

extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));

extern int PXI_IsCallbackReady(int fifoNo, int kind);

extern void RtcCommonCallback(int fifoNo, unsigned int data);

extern Data_02046438 data_020cdd38;

void RTC_Init(void)
{
    if (data_020cdd38.initialized != 0)
        return;

    data_020cdd38.initialized = 1;
    data_020cdd38.field_c = 0;
    data_020cdd38.field_10 = 0;
    data_020cdd38.field_28 = 0;
    data_020cdd38.field_14 = 0;
    data_020cdd38.field_18 = 0;
    func_0200a2c4();
    while (!PXI_IsCallbackReady(5, 1)) {
    }
    PXI_SetFifoRecvCallback(5, RtcCommonCallback);
}
