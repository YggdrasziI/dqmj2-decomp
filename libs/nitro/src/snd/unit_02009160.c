/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *SNDi_SetPlayerParam();

void *SND_SetPlayerChannelPriority(int player, int prio) {
    return SNDi_SetPlayerParam(player, 4, prio, 1);
}
