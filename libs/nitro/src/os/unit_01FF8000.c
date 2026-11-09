/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

extern char data_027e0000[];

extern void func_01ff8058(void);

extern char data_027e0060[];

extern char data_020cbce4[];

extern void CP_SaveContext(void *context);

extern void CPi_RestoreContext(void *context);

extern void Boot_ReloadModules(void);

extern void func_01ff81e8(void);

extern volatile unsigned short data_020cc024;

extern void func_01ff82b4(u32 data, void *destination, u32 size);

asm void func_01ff8000(void)
{
    stmdb   sp!, {lr}
    mov     ip, #0x04000000
    add     ip, ip, #0x210
    ldr     r1, [ip, #-8]
    cmp     r1, #0
    ldmeqia sp!, {pc}
    ldmia   ip, {r1, r2}
    ands    r1, r1, r2
    ldmeqia sp!, {pc}
    mov     r3, #0x80000000
selectHighestPriority:
    clz     r0, r1
    bics    r1, r1, r3, lsr r0
    bne     selectHighestPriority
    mov     r1, r3, lsr r0
    str     r1, [ip, #4]
    rsbs    r0, r0, #31
    ldr     r1, =data_027e0000
    ldr     r0, [r1, r0, lsl #2]
    ldr     lr, =func_01ff8058
    bx      r0
}

asm void func_01ff8058(void)
{
    ldr     ip, =data_027e0060
    mov     r3, #0
    ldr     ip, [ip]
    mov     r2, #1
    cmp     ip, #0
    beq     checkThreadSwitch
clearIrqThreadState:
    str     r2, [ip, #0x64]
    str     r3, [ip, #0x78]
    str     r3, [ip, #0x7c]
    ldr     r0, [ip, #0x80]
    str     r3, [ip, #0x80]
    mov     ip, r0
    cmp     ip, #0
    bne     clearIrqThreadState
    ldr     ip, =data_027e0060
    str     r3, [ip]
    str     r3, [ip, #4]
    ldr     ip, =data_020cbce4
    mov     r1, #1
    strh    r1, [ip]
checkThreadSwitch:
    ldr     ip, =data_020cbce4
    ldrh    r1, [ip]
    cmp     r1, #0
    ldreq   pc, [sp], #4
    mov     r1, #0
    strh    r1, [ip]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    add     r2, ip, #8
    ldr     r1, [r2]
scanRunnableThreads:
    cmp     r1, #0
    ldrneh  r0, [r1, #0x64]
    cmpne   r0, #1
    ldrne   r1, [r1, #0x68]
    bne     scanRunnableThreads
    cmp     r1, #0
    bne     compareCurrentThread
returnFromIrq:
    mov     r3, #0x92
    msr     cpsr_c, r3
    ldr     pc, [sp], #4
compareCurrentThread:
    ldr     r0, [ip, #4]
    cmp     r1, r0
    beq     returnFromIrq
    ldr     r3, [ip, #0xc]
    cmp     r3, #0
    beq     saveThreadContext
    stmdb   sp!, {r0, r1, ip}
    mov     lr, pc
    bx      r3
    ldmia   sp!, {r0, r1, ip}
saveThreadContext:
    str     r1, [ip, #4]
    mrs     r2, spsr
    str     r2, [r0, #0]!
    stmdb   sp!, {r0, r1}
    add     r0, r0, #0
    add     r0, r0, #0x48
    ldr     r1, =CP_SaveContext
    blx     r1
    ldmia   sp!, {r0, r1}
    ldmib   sp!, {r2, r3}
    stmib   r0!, {r2, r3}
    ldmib   sp!, {r2, r3, ip, lr}
    stmib   r0!, {r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}^
    stmib   r0!, {lr}
    mov     r3, #0xd3
    msr     cpsr_c, r3
    stmib   r0!, {sp}
    stmdb   sp!, {r1}
    add     r0, r1, #0
    add     r0, r0, #0x48
    ldr     r1, =CPi_RestoreContext
    blx     r1
    ldmia   sp!, {r1}
    ldr     sp, [r1, #0x44]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    ldr     r2, [r1, #0]!
    msr     spsr_fc, r2
    ldr     lr, [r1, #0x40]
    ldmib   r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}^
    mov     r0, r0
    stmda   sp!, {r0, r1, r2, r3, ip, lr}
    ldmia   sp!, {pc}
}

void OSi_FinalizeReset(void)
{
    while (data_020cc024 == 0) { }
    *(volatile unsigned short *)0x04000208 = 0;
    Boot_ReloadModules();
    func_01ff81e8();
}

asm void func_01ff81e8(void)
{
    mov     ip, #0x4000000
    str     ip, [ip, #0x208]

    ldr     r1, =data_027e0000
    add     r1, r1, #0x3fc0
    add     r1, r1, #0x3c
    mov     r0, #0
    str     r0, [r1]

    ldr     r1, =0x04000180
waitForArm7Reset:
    ldrh    r0, [r1]
    and     r0, r0, #0xf
    cmp     r0, #1
    bne     waitForArm7Reset
    mov     r0, #0x100
    strh    r0, [r1]

    mov     r0, #0
    ldr     r3, =0x027ffd9c
    ldr     r4, [r3]
    ldr     r1, =0x027ffd80
    mov     r2, #0x80
    bl      func_01ff82b4
    str     r4, [r3]

    ldr     r1, =0x027fff80
    mov     r2, #0x18
    bl      func_01ff82b4

    ldr     r1, =0x027fff98
    strh    r0, [r1]

    ldr     r1, =0x027fff9c
    mov     r2, #0x64
    bl      func_01ff82b4

    ldr     r1, =0x04000180
waitForArm7Boot:
    ldrh    r0, [r1]
    and     r0, r0, #0xf
    cmp     r0, #1
    beq     waitForArm7Boot
    mov     r0, #0
    strh    r0, [r1]

    ldr     r3, =0x027ffe00
    ldr     ip, [r3, #0x24]
    mov     lr, ip
    ldr     r11, =0x027fff80
    ldmia   r11, {r0-r10}
    mov     r11, #0
    bx      ip
}
