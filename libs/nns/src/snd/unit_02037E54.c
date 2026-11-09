/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define FADER_SHIFT 8

void NNS_FndInitList(NNSFndList * list, u16 offset);

void NNS_FndAppendListObject(NNSFndList * list, void * object);

extern NNSSndSeqPlayer data_020dd1f8[ 16 ];

extern NNSSndPlayer data_020dd638[ 32 ];

extern NNSFndList data_020dd1ec;

extern NNSFndList data_020dd1e0;

BOOL SND_IsFinishedCommandTag(u32 tag);

void SND_StartPreparedSeq(int playerNo);

void SND_SetPlayerVolume(int playerNo, int volume);

u32 SND_GetPlayerStatus(void);

extern const s16 data_020c1084[128 ];

void * NNS_FndGetNextListObject(NNSFndList * list, void * object);

int NNSi_SndFaderGet(const NNSSndFader * fader);

void NNSi_SndFaderUpdate(NNSSndFader * fader);

BOOL NNSi_SndFaderIsFinished(const NNSSndFader * fader);

extern void ShutdownPlayer(NNSSndSeqPlayer * seqPlayer);

extern void ForceStopSeq(NNSSndSeqPlayer * seqPlayer);

extern void ForceStopSeq (NNSSndSeqPlayer * seqPlayer);

extern void ShutdownPlayer (NNSSndSeqPlayer * seqPlayer);

void NNS_SndHandleReleaseSeq(NNSSndHandle * handle);

extern NNSSndSeqPlayer * AllocSeqPlayer(int prio);

extern void InsertPlayerList(NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer);

extern void NNS_SndHandleReleaseSeq (NNSSndHandle * handle);

extern void InsertPlayerList (NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer);

extern NNSSndSeqPlayer * AllocSeqPlayer (int prio);

static inline
s16 SND_CalcDecibel (int scale)
{
    return data_020c1084[scale];
}

inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}

void NNSi_SndPlayerInit (void)
{
    NNSSndPlayer * player;
    int playerNo;

    NNS_FND_INIT_LIST(&data_020dd1ec, NNSSndSeqPlayer, prioLink);
    NNS_FND_INIT_LIST(&data_020dd1e0, NNSSndSeqPlayer, prioLink);

    for (playerNo = 0; playerNo < SND_PLAYER_NUM; playerNo++) {
        data_020dd1f8[ playerNo ].status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
        data_020dd1f8[ playerNo ].playerNo = (u8)playerNo;
        NNS_FndAppendListObject(&data_020dd1e0, &data_020dd1f8[ playerNo ]);
    }

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_NUM; playerNo++) {
        player = &data_020dd638[ playerNo ];

        NNS_FND_INIT_LIST(&player->playerList, NNSSndSeqPlayer, playerLink);
        NNS_FND_INIT_LIST(&player->heapList, NNSSndPlayerHeap, link);
        player->volume = 127;
        player->playableSeqCount = 1;
        player->allocChBitFlag = 0;
    }
}

void NNSi_SndPlayerMain (void)
{
    NNSSndSeqPlayer * seqPlayer;
    NNSSndSeqPlayer * next;
    u32 status;
    int fader;

    status = SND_GetPlayerStatus();

    for (seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020dd1ec, NULL);
         seqPlayer != NULL; seqPlayer = next) {
        next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020dd1ec, seqPlayer);

        if (!seqPlayer->startFlag) {
            if (SND_IsFinishedCommandTag(seqPlayer->commandTag)) {
                seqPlayer->startFlag = TRUE;
            }
        }

        if (seqPlayer->startFlag) {
            if ((status & (1 << seqPlayer->playerNo)) == 0) {
                ShutdownPlayer(seqPlayer);
                continue;
            }
        }

        NNSi_SndFaderUpdate(&seqPlayer->fader);

        fader
            = SND_CalcDecibel(seqPlayer->initVolume)
              + SND_CalcDecibel(seqPlayer->extVolume)
              + SND_CalcDecibel(seqPlayer->player->volume)
              + SND_CalcDecibel(NNSi_SndFaderGet(&seqPlayer->fader) >> FADER_SHIFT)
            ;
        if (fader < -32768) fader = -32768;
        else if (fader > 32767) fader = 32767;

        if (fader != seqPlayer->volume) {
            SND_SetPlayerVolume(seqPlayer->playerNo, fader);
            seqPlayer->volume = (s16)fader;
        }

        if (seqPlayer->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) {
            if (NNSi_SndFaderIsFinished(&seqPlayer->fader)) {
                ForceStopSeq(seqPlayer);
            }
        }

        if (seqPlayer->prepareFlag) {
            SND_StartPreparedSeq(seqPlayer->playerNo);
            seqPlayer->prepareFlag = FALSE;
        }
    }
}

NNSSndSeqPlayer * NNSi_SndPlayerAllocSeqPlayer (NNSSndHandle * handle, int playerNo, int prio)
{
    NNSSndSeqPlayer * seqPlayer;
    NNSSndPlayer * player;

    player = &data_020dd638[ playerNo ];

    if (NNS_SndHandleIsValid(handle)) {
        NNS_SndHandleReleaseSeq(handle);
    }

    if (player->playerList.numObjects >= player->playableSeqCount) {

        seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&player->playerList, NULL);
        if (seqPlayer == NULL) return NULL;
        if (prio < seqPlayer->prio) return NULL;

        ForceStopSeq(seqPlayer);
    }

    seqPlayer = AllocSeqPlayer(prio);
    if (seqPlayer == NULL) return NULL;

    InsertPlayerList(player, seqPlayer);

    seqPlayer->handle = handle;
    handle->player = seqPlayer;

    return seqPlayer;
}
