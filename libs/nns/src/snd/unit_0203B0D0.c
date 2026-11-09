/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void MI_CpuCopy8(const void * src, void * dest, u32 size);

void * NNS_SndArcGetFileAddress(u32 fileId);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

BOOL OpenMemoryStream (NNSSndStrmPlayer * player, u32 fileId)
{
    player->fileOffset = (u32)NNS_SndArcGetFileAddress(fileId);

    MI_CpuCopy8(
        (const void *)(player->fileOffset),
        &player->info,
        sizeof(player->info)
        );

    return TRUE;
}
