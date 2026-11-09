/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void WaitByLoop(int n);

extern void OS_WaitIrq(int clear, int mask);

void OS_WaitVBlankIntr(void) {
    int one = 1;
    WaitByLoop(one);
    OS_WaitIrq(one, one);
}
