/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

asm void GX_SendFifo48B(void *src, void *dst)
{
    ldmia r0!, {r2, r3, ip}
    stmia r1, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    stmia r1, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    stmia r1, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    stmia r1, {r2, r3, ip}
    bx lr
}
