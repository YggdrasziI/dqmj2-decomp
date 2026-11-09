/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_0200a2c4();

extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned));

extern void CARDi_PulledOutCallback(int, unsigned);

extern int data_020ce660[];

void CARD_InitPulledOutCallback(void) {
    func_0200a2c4();
    PXI_SetFifoRecvCallback(0xe, CARDi_PulledOutCallback);
    data_020ce660[1] = 0;
}
