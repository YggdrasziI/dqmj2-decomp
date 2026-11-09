/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void SND_InvalidateSeqData(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1e, start, end, 0, 0);
}
