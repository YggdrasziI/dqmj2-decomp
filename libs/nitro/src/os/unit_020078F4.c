/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/os.h"

extern OSiExceptionStatics data_020cbf44;

extern void *data_020cbf48;

extern OSExceptionHandler data_020cbf4c;

extern OSiExContext data_020cbf70;

extern void OS_EnableProtectionUnit(void);

extern void OS_DisableProtectionUnit(void);

void func_020078f4(void)
{
    if (data_020cbf44.userExceptionHandler) {
        asm {
            mrs r2, CPSR
            mov r0, sp
            ldr r1, =0x9f
            msr CPSR_cxsf, r1
            mov r1, sp
            mov sp, r0
            stmfd sp!, {r1, r2}
            bl OS_EnableProtectionUnit
            ldr r0, =data_020cbf70
            ldr r1, =data_020cbf48
            ldr r1, [r1]
            ldr r12, =data_020cbf4c
            ldr r12, [r12]
            ldr lr, =@1
            bx r12
        @1:
            bl OS_DisableProtectionUnit
            ldmfd sp!, {r1, r2}
            mov sp, r1
            msr CPSR_cxsf, r2
        }
    }
}
