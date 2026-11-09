/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_027e0060;

void OS_InitIrqTable(void) {
    *(int *)((int)&data_027e0060 + 4) = 0;
    data_027e0060 = 0;
}
