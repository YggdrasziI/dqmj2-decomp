/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#define SQRT_REGISTERS ((SqrtRegisters *)0x040002b0)

typedef struct SqrtRegisters {
    volatile unsigned short control;
    unsigned short padding[3];
    volatile s64 parameter;
} SqrtRegisters;

fx32 VEC_Mag(const VecFx32 *v)
{
    s64 squared;
    fx32 y = v->y;
    fx32 x = *(volatile const fx32 *)&v->x;

    squared = (s64)x * x;
    squared += (s64)y * y;
    squared += (s64)v->z * v->z;

    SQRT_REGISTERS->control = 1;
    SQRT_REGISTERS->parameter = squared * 4;
    while (SQRT_REGISTERS->control & 0x8000) {
    }
    return (*(volatile fx32 *)0x040002b4 + 1) >> 1;
}
