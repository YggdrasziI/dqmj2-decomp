/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define FADER_SHIFT 8

void NNSi_SndFaderSet(NNSSndFader * fader, int target, int frame);

void SND_SetPlayerChannelPriority(int playerNo, int prio);

inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndHandleReleaseSeq (NNSSndHandle * handle)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->handle = NULL;
    handle->player = NULL;
}

void NNS_SndPlayerSetVolume (NNSSndHandle * handle, int volume)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->extVolume = (u8)volume;
}

void NNS_SndPlayerSetInitialVolume (NNSSndHandle * handle, int volume)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->initVolume = (u8)volume;
}

void NNS_SndPlayerMoveVolume (NNSSndHandle * handle, int targetVolume, int frames)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    if (handle->player->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) return;

    NNSi_SndFaderSet(&handle->player->fader, targetVolume << FADER_SHIFT, frames);
}

void NNS_SndPlayerSetChannelPriority (NNSSndHandle * handle, int priority)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    SND_SetPlayerChannelPriority(handle->player->playerNo, priority);
}
