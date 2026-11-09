/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/fs.h"

extern FSArchive data_020cdc74;

FSFileID FS_GetOverlayFileID(const FSOverlayInfo *p_ovi)
{
    FSFileID ret;
    ret.arc = &data_020cdc74;
    ret.file_id = p_ovi->header.file_id;
    return ret;
}
