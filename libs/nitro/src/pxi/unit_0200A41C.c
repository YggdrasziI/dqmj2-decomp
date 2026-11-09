/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/hw.h"

#define OS_GetSystemWork() ((OSSystemWork *)HW_MAIN_MEM_SYSTEM)

typedef void *OSMessage;

typedef int PXIProc;

typedef struct OSSystemWork {
    u8 reserved[0x388];
    u32 pxiHandleChecker[2];      
} OSSystemWork;

BOOL PXI_IsCallbackReady(int fifotag, PXIProc proc)
{
    OSSystemWork *p = OS_GetSystemWork();
    return (p->pxiHandleChecker[proc] & (1UL << fifotag)) ? TRUE : FALSE;
}
