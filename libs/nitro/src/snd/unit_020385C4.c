/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern struct { int a, b; } data_020ddab8;

void SND_ClearChannelBit(int bit) {
    data_020ddab8.b &= ~(1 << bit);
}
