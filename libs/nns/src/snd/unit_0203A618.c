/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

typedef enum StrmFormat {
    STRM_FORMAT_PCM8,
    STRM_FORMAT_PCM16,
    STRM_FORMAT_ADPCM
} StrmFormat;

const NNSSndArcStrmInfo * NNS_SndArcGetStrmInfo(int strmNo);

extern void SetupStreamFunction(NNSSndStrmPlayer * player, u32 fileId);

extern void SetupStreamFunction (NNSSndStrmPlayer * player, u32 fileId);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

void OnDataEnd (NNSSndStrmPlayer * player)
{
    NNSSndArcStrmCallbackInfo info;
    NNSSndArcStrmCallbackParam param;
    const NNSSndArcStrmInfo * strmInfo;
    u8 old_format;
    u16 old_sampleRate;
    u64 tmpU64;
    BOOL result;

    info.playerNo = player->playerNo;
    info.strmNo = player->strmNo;

    param.strmNo = player->strmNo;
    param.offset = 0;

    result = player->sndArcStrmCallback(
        NNS_SND_ARC_STRM_CALLBACK_DATA_END,
        &info,
        &param,
        player->sndArcStrmCallbackArg
        );
    if (!result) return;

    strmInfo = NNS_SndArcGetStrmInfo(param.strmNo);
    if (strmInfo == NULL) return;

    old_format = player->info.format;
    old_sampleRate = player->info.sampleRate;

    player->closeStreamFunc(player);

    SetupStreamFunction(player, strmInfo->fileId);

    if (!player->openStreamFunc(player, strmInfo->fileId)) {
        return;
    }

    if (old_sampleRate != player->info.sampleRate) {
        return;
    }
    if (old_format == STRM_FORMAT_PCM8 && player->info.format != STRM_FORMAT_PCM8 ||
        old_format != STRM_FORMAT_PCM8 && player->info.format == STRM_FORMAT_PCM8) {
        return;
    }

    player->strmNo = param.strmNo;
    tmpU64 = player->info.sampleRate;
    tmpU64 *= param.offset;
    tmpU64 /= 1000;
    player->curSample = (u32)tmpU64;
    if (player->curSample != 0 && player->info.format == STRM_FORMAT_ADPCM) {
        player->dirtyFlag = TRUE;
    } else {
        player->dirtyFlag = FALSE;
    }

    player->finishFlag = FALSE;
}
