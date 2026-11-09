/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int PXI_SendWordByFifo(int channel, int data, int flag);

void OSi_SendToPxi(int data) {
    int payload = data << 8;
    int channel = 0xc;
    int zero = 0;
    while (PXI_SendWordByFifo(channel, payload, zero) != 0) {
        ;
    }
}
