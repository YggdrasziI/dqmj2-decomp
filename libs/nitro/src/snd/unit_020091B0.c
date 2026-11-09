/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetTrackAllocatableChannel(int a, int b, int c) {
    PushCommand_impl(0x9, a, b, c, 0);
}
