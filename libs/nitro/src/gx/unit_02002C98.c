/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/gx.h"

#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define HW_IOREG 0x04000000

#define HW_REG_BASE HW_IOREG

#define REG_DISPCNT_OFFSET 0x000

#define REG_DISPCNT_ADDR (HW_REG_BASE + REG_DISPCNT_OFFSET)

#define reg_GX_DISPCNT (*( REGType32v *) REG_DISPCNT_ADDR)

#define REG_GX_DISPCNT_VRAM_MASK 0x000c0000

#define REG_GX_DISPCNT_MODE_SHIFT 16

#define REG_GX_DISPCNT_MODE_MASK 0x00030000

#define REG_GX_DISPCNT_BG02D3D_SHIFT 3

#define REG_GX_DISPCNT_BG02D3D_MASK 0x00000008

#define REG_GX_DISPCNT_BGMODE_SHIFT 0

#define REG_GX_DISPCNT_BGMODE_MASK 0x00000007

typedef void *OSMessage;

extern u16 data_020cbc00;

extern u16 data_020c5ca0;

void GX_SetGraphicsMode (GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d)
{
	u32 cnt = reg_GX_DISPCNT;

	data_020cbc00 = (u16)dispMode;
	if (!data_020c5ca0) {
		dispMode = GX_DISPMODE_OFF;
	}

	cnt &= ~(REG_GX_DISPCNT_BGMODE_MASK |
	         REG_GX_DISPCNT_BG02D3D_MASK | REG_GX_DISPCNT_MODE_MASK | REG_GX_DISPCNT_VRAM_MASK);

	reg_GX_DISPCNT = (u32)(cnt |
	                       (dispMode << REG_GX_DISPCNT_MODE_SHIFT) |
	                       (bgMode << REG_GX_DISPCNT_BGMODE_SHIFT) | (bg0_2d3d <<
	                                                                  REG_GX_DISPCNT_BG02D3D_SHIFT));

	if (data_020cbc00 == GX_DISPMODE_OFF) {
		data_020c5ca0 = FALSE;
	}
}
