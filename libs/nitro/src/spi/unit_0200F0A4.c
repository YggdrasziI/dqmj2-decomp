/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/spi.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

BOOL func_0200ee8c(PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);

extern BOOL func_0200ee8c (PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);

BOOL PM_SetLCDPower (PMLCDPower sw)
{
    if (sw != PM_LCD_POWER_ON) {
        sw = PM_LCD_POWER_OFF;
    }

    return func_0200ee8c(sw, PM_LED_NONE, FALSE, TRUE);
}
