/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_0200a2c4(void);

extern int PXI_IsCallbackReady(int fifoNo, int kind);

extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned));

extern void OSi_CommonCallback(int, unsigned);

extern struct { unsigned short _0; unsigned short state; } data_020cc024;

void OS_InitReset(void)
{
    if (data_020cc024.state != 0) return;
    data_020cc024.state = 1;
    func_0200a2c4();
    while (!PXI_IsCallbackReady(0xc, 1));
    PXI_SetFifoRecvCallback(0xc, OSi_CommonCallback);
}
