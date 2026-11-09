/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#define SQRT_CONTROL (*(volatile u16 *)0x040002b0)

#define SQRT_RESULT (*(volatile fx32 *)0x040002b4)

#define SQRT_PARAMETER (*(volatile u64 *)0x040002b8)

#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

fx32 func_0200235c(fx32 numer, fx32 denom);

extern const fx16 data_020c0e10[128 + 1];

fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b)
{
    fx32 x = a->x - b->x;
    fx32 y = a->y - b->y;
    fx32 z = a->z - b->z;
    fx64 squaredDistance = (fx64)x * x;

    squaredDistance += (fx64)y * y;
    squaredDistance += (fx64)z * z;

    SQRT_CONTROL = 1;
    SQRT_PARAMETER = (u64)(squaredDistance * 4);
    while (SQRT_CONTROL & 0x8000) {
    }

    return (SQRT_RESULT + 1) >> 1;
}

fx16 FX_Atan2 (fx32 y, fx32 x)
{
	fx32 a, b, c;
	int sgn;

	if (y > 0) {
		if (x > 0) {
			if (x > y) {
				a = y;
				b = x;
				c = 0;
				sgn = 1;
			} else if (x < y)   {
				a = x;
				b = y;
				c = 6434;
				sgn = 0;
			} else {
				return (fx16)3217;
			}
		} else if (x < 0)   {
			x = -x;
			if (x < y) {
				a = x;
				b = y;
				c = 6434;
				sgn = 1;
			} else if (x > y)   {
				a = y;
				b = x;
				c = 12868;
				sgn = 0;
			} else {
				return (fx16)9651;
			}
		} else {
			return (fx16)6434;
		}
	} else if (y < 0)   {
		y = -y;
		if (x < 0) {
			x = -x;
			if (x > y) {
				a = y;
				b = x;
				c = -12868;
				sgn = 1;
			} else if (x < y)   {
				a = x;
				b = y;
				c = -6434;
				sgn = 0;
			} else {
				return (fx16) - 9651;
			}
		} else if (x > 0)   {
			if (x < y) {
				a = x;
				b = y;
				c = -6434;
				sgn = 1;
			} else if (x > y)   {
				a = y;
				b = x;
				c = 0;
				sgn = 0;
			} else {
				return (fx16) - 3217;
			}
		} else {
			return (fx16) - 6434;
		}
	} else {
		if (x >= 0) {
			return 0;
		} else {
			return (fx16)12868;
		}
	}

	if (b == 0)
		return 0;
	if (sgn)
		return (fx16)(c + data_020c0e10[func_0200235c(a, b) >> 5]);
	else
		return (fx16)(c - data_020c0e10[func_0200235c(a, b) >> 5]);
}
