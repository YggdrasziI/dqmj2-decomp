/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void MI_CpuCopy8(const void * src, void * dest, u32 size);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

s32 ReadMemoryStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset)
{

    const u8 * src = (const u8 *)(player->fileOffset);

    MI_CpuCopy8(src + offset, dest, size);

    return (s32)size;
}
