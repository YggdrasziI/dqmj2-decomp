/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern char data_020ce680[];

void func_02011634(int idx, int value) {
    *(int *)(*(int *)(data_020ce680 + 4) + idx * 4 + 0x18) = value;
}
