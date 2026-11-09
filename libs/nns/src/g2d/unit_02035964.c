/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/pxi.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void MIi_CpuClearFast(u32 data, void * destp, u32 size);

static inline void MI_CpuFillFast (void * dest, u32 data, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}

static inline int GetCharacterSize (const NNSG2dCharCanvas * pCC)
{
    return 8 * 8 * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32 (const NNSG2dCharCanvas * pCC, int cl)
{
    u32 val = (u32)cl;
    if ( pCC->dstBpp == 4 ) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }
    return val;
}

void ClearContinuous (const NNSG2dCharCanvas * pCC, int cl)
{
    u32 data;

    data = SpreadColor32(pCC, cl);

    MI_CpuFillFast(
        pCC->charBase,
        data,
        (u32)pCC->areaWidth * pCC->areaHeight * GetCharacterSize(pCC)
        );
}
