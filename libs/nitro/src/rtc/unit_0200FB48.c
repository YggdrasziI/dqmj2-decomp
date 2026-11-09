/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern volatile int data_020cdd44;

asm void RtcWaitBusy(void)
{
    ldr r12, =data_020cdd44
loop:
    ldr r0, [r12, #0]
    cmp r0, #1
    beq loop
    bx lr
}
