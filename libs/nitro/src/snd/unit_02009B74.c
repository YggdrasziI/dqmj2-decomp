/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int PXI_SendWordByFifo(int a, int b, int c);

void RequestCommandProc(void) {
    int cmd = 7;
    int zero = 0;
    while (PXI_SendWordByFifo(cmd, zero, zero) < 0) {
        ;
    }
}
