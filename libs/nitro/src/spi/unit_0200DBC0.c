/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    unsigned short initialized;
    char _2[0x2];
    int field_4;
    char _8[0x8];
    unsigned short field_10;
    char _12[0x2];
    int field_14;
    char _18[0x1c];
    unsigned short field_34;
    unsigned short field_36;
    unsigned short field_38;
    unsigned short field_3a;
} Data_02046390;

extern void func_0200a2c4(void);

extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));

extern int PXI_IsCallbackReady(int fifoNo, int kind);

extern void TPi_TpCallback(int fifoNo, unsigned int data);

extern Data_02046390 data_020cdcd0;

void TP_Init(void)
{
    if (data_020cdcd0.initialized != 0)
        return;

    data_020cdcd0.initialized = 1;
    func_0200a2c4();
    data_020cdcd0.field_10 = 0;
    data_020cdcd0.field_4 = 0;
    data_020cdcd0.field_14 = 0;
    data_020cdcd0.field_36 = 0;
    data_020cdcd0.field_34 = 0;
    data_020cdcd0.field_3a = 0;
    data_020cdcd0.field_38 = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    PXI_SetFifoRecvCallback(6, TPi_TpCallback);
}
