/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

inline BOOL NNS_SndStrmHandleIsValid (const NNSSndStrmHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndArcStrmStartPrepared (NNSSndStrmHandle * handle)
{

    if (!NNS_SndStrmHandleIsValid(handle)) return;

    handle->player->startFlag = TRUE;
}
