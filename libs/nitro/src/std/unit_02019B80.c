/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

int STD_GetStringLength (const char * str)
{
    int n = 0;
    while (str[n]) {
        n++;
    }
    return n;
}
