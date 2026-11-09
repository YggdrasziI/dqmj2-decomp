/* NitroSDK; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/hw.h"

extern void *func_02005ef8(int id, void *word, void *callback);

extern void *func_02005f7c(int id, void *word, void *callback);

extern void WaitByLoop(u32 count);

extern void func_02008c14(u32 value, void *destination, u32 size);

extern u32 data_020cbcbc;

typedef struct {
    u32 lockFlag;
    u16 ownerId;
    u16 extension;
} OSLockWord;

/* The init lock word (HW_INIT_LOCK_BUF). The ROM's code is reproduced only when it
 * is reached through a symbol (a constant address schedules the stores
 * differently): the link defines it (tools/lcf_keep.py). */
extern OSLockWord data_027ffff0;

#define OSi_LockIdFlags  ((u32 *)0x027fffb0)

#define OS_LOCKID_INIT   0x7e

#define OS_LOCKID_ERROR  0x7f

void OS_InitLock(void)
{
    if (data_020cbcbc != 0) {
        return;
    }
    data_020cbcbc = 1;
    data_027ffff0.lockFlag = 0;
    func_02005ef8(OS_LOCKID_INIT, &data_027ffff0, 0);

    {
        OSLockWord *w = &data_027ffff0;

        while (w->extension != 0) {
            WaitByLoop(0x400);
        }
    }

    OSi_LockIdFlags[0] = 0xffffffff;
    OSi_LockIdFlags[1] = 0xffff0000;
    func_02008c14(0, OSi_LockIdFlags + 4, 40);

    REG_EXMEM_CNT |= 0x800;
    REG_EXMEM_CNT |= 0x80;

    func_02005f7c(OS_LOCKID_INIT, &data_027ffff0, 0);
    func_02005ef8(OS_LOCKID_ERROR, &data_027ffff0, 0);
}
