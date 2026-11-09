/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020cc040;

void MIi_DMAFastCallback(void) {
    void (*cb)(int);
    int arg;

    data_020cc040 = 0;
    cb = *(void (**)(int))((int)&data_020cc040 + 0x10);
    arg = *(int *)((int)&data_020cc040 + 0x14);
    if (cb != 0) {
        cb(arg);
    }
}
