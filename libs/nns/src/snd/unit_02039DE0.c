/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void NNS_SndStrmHandleRelease(struct NNSSndStrmHandle * handle);

extern NNSSndStrmPlayer data_020de1a0[4 ];

extern void func_0203a160(NNSSndStrmPlayer * player);

extern void NNS_SndStrmHandleRelease (NNSSndStrmHandle * handle);

extern void func_0203a160 (NNSSndStrmPlayer * player);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

inline BOOL NNS_SndStrmHandleIsValid (const NNSSndStrmHandle * handle)
{
    return handle->player != NULL ;
}

NNSSndStrmPlayer * AllocPlayer (NNSSndStrmHandle * handle, int playerNo, int prio)
{
    NNSSndStrmPlayer * player;

    if (NNS_SndStrmHandleIsValid(handle)) {
        NNS_SndStrmHandleRelease(handle);
    }

    player = &data_020de1a0[ playerNo ];

    if (player->buffer == NULL) return NULL;

    if (player->activeFlag) {
        if (prio < player->prio) return NULL;
        func_0203a160(player);
    }

    player->prio = prio;
    player->activeFlag = TRUE;

    player->handle = handle;
    handle->player = player;

    return player;
}
