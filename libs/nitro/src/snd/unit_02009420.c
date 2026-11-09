/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SNDi_SetPlayerParam(int a, int b, int c, int d) {
    PushCommand_impl(0x6, a, b, c, d);
}
