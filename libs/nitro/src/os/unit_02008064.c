/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

asm void OS_SpinWait(register unsigned int cycles)
{
loop:
    subs r0, r0, #4
    bhs loop
    bx lr
}
