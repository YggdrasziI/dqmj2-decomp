/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#define OS_ARENA_MAIN       0

#define OS_ARENA_MAINEX     2

#define OS_ARENA_ITCM       3

#define OS_ARENA_DTCM       4

#define OS_ARENA_SHARED     5

#define OS_ARENA_WRAM_MAIN  6

extern void *OS_GetInitArenaHi(int nArena);

extern void *func_02007644(int nArena);

extern void OS_SetArenaHi(int nArena, void *pAddress);

extern void OS_SetArenaLo(int nArena, void *pAddress);

extern BOOL data_020cbf3c;

void OS_InitArena(void)
{
    if (data_020cbf3c) {
        return;
    }
    data_020cbf3c = 1;

    OS_SetArenaHi(OS_ARENA_MAIN, OS_GetInitArenaHi(OS_ARENA_MAIN));
    OS_SetArenaLo(OS_ARENA_MAIN, func_02007644(OS_ARENA_MAIN));

    OS_SetArenaLo(OS_ARENA_MAINEX, (void *)0);
    OS_SetArenaHi(OS_ARENA_MAINEX, (void *)0);

    OS_SetArenaHi(OS_ARENA_ITCM, OS_GetInitArenaHi(OS_ARENA_ITCM));
    OS_SetArenaLo(OS_ARENA_ITCM, func_02007644(OS_ARENA_ITCM));

    OS_SetArenaHi(OS_ARENA_DTCM, OS_GetInitArenaHi(OS_ARENA_DTCM));
    OS_SetArenaLo(OS_ARENA_DTCM, func_02007644(OS_ARENA_DTCM));

    OS_SetArenaHi(OS_ARENA_SHARED, OS_GetInitArenaHi(OS_ARENA_SHARED));
    OS_SetArenaLo(OS_ARENA_SHARED, func_02007644(OS_ARENA_SHARED));

    OS_SetArenaHi(OS_ARENA_WRAM_MAIN, OS_GetInitArenaHi(OS_ARENA_WRAM_MAIN));
    OS_SetArenaLo(OS_ARENA_WRAM_MAIN, func_02007644(OS_ARENA_WRAM_MAIN));
}
