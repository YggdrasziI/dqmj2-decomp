/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

#define BLOCK_SIZE 512

#define BLOCK_NUM 4

void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

const NNSSndArcStrmPlayerInfo * NNS_SndArcGetStrmPlayerInfo(int playerNo);

typedef struct StrmCommand {
    NNSFndLink link;
    u32 param[10];
} StrmCommand;

#define COMMAND_NUM 8

extern NNSSndStrmPlayer data_020de1a0[NNS_SND_STRM_PLAYER_NUM];

extern NNSFndList data_020ddb10;

extern OSMutex data_020ddb1c;

extern StrmCommand data_020ddb34[COMMAND_NUM];

extern u8 data_020de780[BLOCK_SIZE];

extern NNSSndStrmThread data_020ddcb4;

void NNS_FndInitList(NNSFndList * list, u16 offset);

void NNS_FndAppendListObject(NNSFndList * list, void * object);

void OS_InitMutex(OSMutex * mutex);

void FS_InitFile(FSFile * p_file);

void NNS_SndStrmInit(NNSSndStrm * stream);

BOOL NNS_SndArcStrmSetupPlayer(NNSSndHeapHandle heap);

void CreateThread(NNSSndStrmThread * thread, u32 threadPrio);

/* The file's static data: one block in this build, read from its start */
extern struct {
    BOOL initialized;             /* 0x00: NNS_SndArcStrmInit's flag */
    NNSSndStrmThread *prepareThread; /* 0x04: sPrepareThread */
    u8 *decodeBuffer;             /* 0x08: sDecodeBuffer */
} data_020ddb04;




#pragma opt_rotateloops off

#pragma opt_strength_reduction off

void NNS_SndArcStrmInit (u32 threadPrio, NNSSndHeapHandle heap)
{
    int i;
    int playerNo;
    NNSSndStrmPlayer * player;

    if (data_020ddb04.initialized) {
        (void)NNS_SndArcStrmSetupPlayer(heap);
        return;
    }
    data_020ddb04.initialized = TRUE;

    NNS_FndInitList(&data_020ddb10, 0);
    for (i = 0; i < COMMAND_NUM; i++) {
        NNS_FndAppendListObject(&data_020ddb10, &data_020ddb34[i]);
    }
    OS_InitMutex(&data_020ddb1c);

    data_020ddb04.decodeBuffer = data_020de780;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; playerNo++) {
        player = &data_020de1a0[playerNo];

        player->activeFlag = FALSE;
        FS_InitFile(&player->file);
        NNS_SndStrmInit(&player->stream);
        player->playerNo = playerNo;
        player->numChannels = 0;
        player->buffer = NULL;
        player->bufSize = 0;
        player->allocChannelCount = 0;
    }

    (void)NNS_SndArcStrmSetupPlayer(heap);

    CreateThread(&data_020ddcb4, threadPrio);
}

#pragma opt_strength_reduction reset

#pragma opt_rotateloops reset
