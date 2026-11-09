/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

extern const s16 data_020c1084[128 ];

void NNS_SndStrmStart(NNSSndStrm * stream);

void NNS_SndStrmSetVolume(NNSSndStrm * stream, int volume);

int NNSi_SndFaderGet(const NNSSndFader * fader);

void NNSi_SndFaderUpdate(NNSSndFader * fader);

BOOL NNSi_SndFaderIsFinished(const NNSSndFader * fader);

extern NNSSndStrmPlayer data_020de1a0[4 ];

extern void func_0203a160(NNSSndStrmPlayer * player);

extern void func_0203a160 (NNSSndStrmPlayer * player);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

static inline
s16 SND_CalcDecibel (int scale)
{
    return data_020c1084[scale];
}

void NNSi_SndArcStrmMain (void)
{
    NNSSndStrmPlayer * player;
    int playerNo;
    int volume;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; ++playerNo) {
        player = &data_020de1a0[ playerNo ];

        if (!player->activeFlag) continue;

        if (player->finishCounter == 0) {
            func_0203a160(player);
            continue;
        }

        if (player->startFlag) {
            if (player->prepareFlag) {
                NNS_SndStrmStart(&player->stream);

                player->playFlag = TRUE;
                player->startFlag = FALSE;
            }
        }

        if (!player->playFlag) continue;

        NNSi_SndFaderUpdate(&player->fader);

        volume
            = SND_CalcDecibel(NNSi_SndFaderGet(&player->fader) >> 8)
              + SND_CalcDecibel(player->initVolume)
              + SND_CalcDecibel(player->extVolume)
            ;
        if (volume != player->volume) {
            NNS_SndStrmSetVolume(&player->stream, volume);

            player->volume = volume;
        }

        if (player->fadeOutFlag) {
            if (NNSi_SndFaderIsFinished(&player->fader)) {
                func_0203a160(player);
            }
        }
    }
}
