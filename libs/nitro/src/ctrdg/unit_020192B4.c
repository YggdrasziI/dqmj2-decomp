/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_0200a2c4(void);

extern int PXI_IsCallbackReady(int fifoNo, int kind);

extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));

extern void CTRDG_Enable(int enable);

extern void CTRDGi_InitCommon(void);

extern void CTRDGi_InitModuleInfo(void);

extern void CTRDGi_InitTaskThread(void *p);

extern void CTRDGi_InitCallback(int fifoNo, unsigned int data);

extern void CTRDGi_PulledOutCallback(int fifoNo, unsigned int data);

extern void func_020195f8(int fifoNo, unsigned int data);

extern struct {
    char _0[8];
    int initialized;
    int field_c;
    char _10[8];
    int field_18;
} data_020d4cc0;

extern char data_020d4da0;

void CTRDG_Init(void)
{
    if (data_020d4cc0.initialized != 0)
        return;

    data_020d4cc0.initialized = 1;
    CTRDGi_InitCommon();
    data_020d4cc0.field_c = 0;
    func_0200a2c4();
    while (!PXI_IsCallbackReady(13, 1)) {
    }
    PXI_SetFifoRecvCallback(13, CTRDGi_InitCallback);
    CTRDGi_InitModuleInfo();
    PXI_SetFifoRecvCallback(13, 0);
    PXI_SetFifoRecvCallback(13, CTRDGi_PulledOutCallback);
    data_020d4cc0.field_18 = 0;
    CTRDGi_InitTaskThread(&data_020d4da0);
    PXI_SetFifoRecvCallback(17, func_020195f8);
    CTRDG_Enable(0);
}
