/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

s32 func_0200c180(FSFile * p_file, void * dst, s32 len);

BOOL FS_SeekFile(FSFile * p_file, s32 offset, FSSeekFileMode origin);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

s32 ReadFileStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset)
{
    BOOL result;

    result = FS_SeekFile(
        &player->file,
        (s32)(player->fileOffset + offset),
        FS_SEEK_SET
        );
    return func_0200c180(
        &player->file,
        dest,
        (s32)size
        );
}
