/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define reg_GX_POWCNT        (*(vu16 *)0x04000304)

#define reg_GX_DISPCNT       (*(vu32 *)0x04000000)

#define reg_GX_DISPSTAT      (*(vu16 *)0x04000004)

#define reg_GX_MASTER_BRIGHT (*(vu16 *)0x0400006c)

#define reg_G2_BG0CNT        ((void *)0x04000008)

#define reg_GXS_DB_DISPCNT   ((void *)0x04001000)

#define POWCNT_INIT_MASK 0x20e

#define POWCNT_DSEL      0x8000

#define POWCNT_LCD       0x0001

extern void GX_InitGXState(void);

extern s32 OS_GetLockID(void);

extern void OS_Terminate(void);

extern void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size);

extern void func_02008c14(u32 data, void *dest, u32 size);

extern vu16 data_020cbc00[];

extern u32 data_020c5ca0[];

void GX_Init(void)
{
    s32 lockId;

    reg_GX_POWCNT |= POWCNT_DSEL;
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~POWCNT_INIT_MASK) | POWCNT_INIT_MASK);
    reg_GX_POWCNT = (u16)(reg_GX_POWCNT | POWCNT_LCD);

    GX_InitGXState();

    while (data_020cbc00[1] == 0) {
        lockId = OS_GetLockID();
        if (lockId == OS_LOCK_ID_ERROR) {
            OS_Terminate();
        }
        data_020cbc00[1] = (u16)lockId;
    }

    reg_GX_DISPSTAT = 0;
    reg_GX_DISPCNT = 0;

    if (data_020c5ca0[1] != (u32)-1) {
        MI_DmaFill32(data_020c5ca0[1], reg_G2_BG0CNT, 0, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        MI_DmaFill32(data_020c5ca0[1], reg_GXS_DB_DISPCNT, 0, 0x70);
    } else {
        func_02008c14(0, reg_G2_BG0CNT, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        func_02008c14(0, reg_GXS_DB_DISPCNT, 0x70);
    }

    *(vu16 *)0x04000020 = 0x100; 
    *(vu16 *)0x04000026 = 0x100; 
    *(vu16 *)0x04000030 = 0x100; 
    *(vu16 *)0x04000036 = 0x100; 
    *(vu16 *)0x04001020 = 0x100; 
    *(vu16 *)0x04001026 = 0x100; 
    *(vu16 *)0x04001030 = 0x100; 
    *(vu16 *)0x04001036 = 0x100; 
}
