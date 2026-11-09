/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

asm void OSi_CancelDma0(void) {
    mov     r12, #0x04000000
    ldr     r1, [r12, #0x208]
    str     r12, [r12, #0x208]
@loop:
    ldrh    r0, [r12, #6]
    cmp     r0, #0
    bne     @loop
    str     r1, [r12, #0x208]
    bx      lr
}
