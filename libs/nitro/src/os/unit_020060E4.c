/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

asm void OS_GetLockID(void)
{
    ldr     r3, =0x027fffb0
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    movne   r0, #0x40
    bne     @found
    add     r3, r3, #4
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    ldr     r0, =0xfffffffd
    bxeq    lr
    mov     r0, #0x60
@found:
    add     r0, r0, r2
    mov     r1, #0x80000000
    mov     r1, r1, lsr r2
    ldr     r2, [r3]
    bic     r2, r2, r1
    str     r2, [r3]
    bx      lr
}

asm void OS_ReleaseLockID(int nLockId)
{
    ldr     r3, =0x027fffb0
    cmp     r0, #0x60
    addpl   r3, r3, #4
    subpl   r0, r0, #0x60
    submi   r0, r0, #0x40
    mov     r1, #0x80000000
    mov     r1, r1, lsr r0
    ldr     r2, [r3]
    orr     r2, r2, r1
    str     r2, [r3]
    bx      lr
}
