/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

BOOL FS_OpenFileFast(FSFile * p_file, FSFileID file_id);

s32 func_02038ca0(u32 fileId, void * buffer, s32 size, s32 offset);

FSFileID NNS_SndArcGetFileID(void);

u32 NNS_SndArcGetFileOffset(u32 fileId);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

BOOL OpenFileStream (NNSSndStrmPlayer * player, u32 fileId)
{
    if (func_02038ca0(fileId, &player->info, sizeof(player->info), 0) != sizeof(player->info)) {
        return FALSE;
    }

    if (!FS_OpenFileFast(&player->file, NNS_SndArcGetFileID())) {
        return FALSE;
    }
    player->fileOffset = NNS_SndArcGetFileOffset(fileId);

    return TRUE;
}
