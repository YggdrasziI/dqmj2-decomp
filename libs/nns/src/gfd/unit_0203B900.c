/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020dea50;

void NNS_GfdResetFrmPlttVramState(void) {
    *(int *)&data_020dea50 = 0;
    *(int *)((char *)&data_020dea50 + 4) = *(int *)((char *)&data_020dea50 + 8);
}
