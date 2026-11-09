/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void SNDi_SetPlayerParam(int a, int b, int c, int d);

void SND_SetPlayerVolume(int playerNo, int volume) {
    SNDi_SetPlayerParam(playerNo, 6, volume, 2);
}
