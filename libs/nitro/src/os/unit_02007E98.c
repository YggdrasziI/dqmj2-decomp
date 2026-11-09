/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OSi_ArrangeTimer(void);

asm void OSi_AlarmHandler(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_ArrangeTimer
    ldmia sp!, {r0, lr}
    bx lr
}
