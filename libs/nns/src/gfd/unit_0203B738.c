/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020dea50[];

extern void *data_020c6998;

extern void *data_020c699c;

extern void NNS_GfdResetFrmPlttVramState(int value);

extern void func_0203b784(void);

extern void func_0203b8c0(void);

void NNS_GfdInitFrmPlttVramManager(int value, int install_callbacks) {
    data_020dea50[2] = value;
    NNS_GfdResetFrmPlttVramState(value);

    if (install_callbacks != 0) {
        data_020c6998 = func_0203b784;
        data_020c699c = func_0203b8c0;
    }
}
