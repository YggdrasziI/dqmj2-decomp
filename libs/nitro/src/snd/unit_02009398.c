/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void SND_InvalidateBankData(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1f, start, end, 0, 0);
}
