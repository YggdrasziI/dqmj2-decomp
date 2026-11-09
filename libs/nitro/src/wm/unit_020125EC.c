/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/wm.h"

extern int func_020117ec(void);

extern void func_02011634(int slot, int arg);

extern WMErrCode func_020116a4(WMApiid id, u16 paramNum, ...);

int func_020125ec(int arg) {
    int r = func_020117ec();
    if (r != 0) {
        return r;
    }
    func_02011634(1, arg);
    r = func_020116a4(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
