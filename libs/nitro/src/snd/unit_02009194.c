/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void SNDi_SetTrackParam(int player, unsigned int trackMask, int param, int value, int immediate);

void SND_SetTrackPan(int player, unsigned int trackMask, int pan) {
    SNDi_SetTrackParam(player, trackMask, 9, pan, 1);
}
