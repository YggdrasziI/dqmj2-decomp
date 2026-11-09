/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern void SNDi_FreeVoiceChannel(NNSSndStrmPlayer * player, int fadeFrame);

extern void SNDi_FreeVoiceChannel (NNSSndStrmPlayer * player, int fadeFrame);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

inline BOOL NNS_SndStrmHandleIsValid (const NNSSndStrmHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndArcStrmStop (NNSSndStrmHandle * handle, int fadeFrame)
{

    if (!NNS_SndStrmHandleIsValid(handle)) return;

    SNDi_FreeVoiceChannel(handle->player, fadeFrame);
}
