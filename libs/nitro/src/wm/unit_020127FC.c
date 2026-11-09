/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/wm.h"

extern WMErrCode func_02011834(s32 paramNum, ...);

extern void func_02011634(int slot, int arg);

extern WMErrCode func_020116a4(WMApiid id, u16 paramNum, ...);

int func_020127fc(int arg) {
    int r = func_02011834(1, 7);
    if (r != 0) {
        return r;
    }
    func_02011634(9, arg);
    r = func_020116a4(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
