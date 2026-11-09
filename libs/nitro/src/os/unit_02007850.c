/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OSi_SetExContext(void);

extern void func_020078f4(void);

asm void OSi_GetAndDisplayContext(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext
    bl func_020078f4
    ldmia sp!, {r0, lr}
    bx lr
}
