/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SNDi_SetTrackParam(int player, unsigned int trackMask, int param, int value, int immediate) {
    PushCommand_impl(7, player | (immediate << 24), trackMask, param, value);
}
