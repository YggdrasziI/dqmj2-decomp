/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int PXI_SendWordByFifo(int channel, int data, int flag);

int RtcSendPxiCommand(int cmd) {
    return PXI_SendWordByFifo(5, (cmd << 8) & 0x7f00, 0) >= 0;
}
