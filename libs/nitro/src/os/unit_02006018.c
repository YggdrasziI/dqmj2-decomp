/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_02005ff8(int processor);

asm void OS_UnLockCartridge(int processor)
{
    ldr r1, =func_02005ff8
    bx  r1
}
