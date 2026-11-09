/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_StartPreparedSeq(int handle) {
    PushCommand_impl(3, handle, 0, 0, 0);
}
