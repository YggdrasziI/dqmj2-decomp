/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

/* The file's static data: one block in this build, read from its start */
extern struct {
    BOOL initialized;             /* 0x00: NNS_SndArcStrmInit's flag */
    NNSSndStrmThread *prepareThread; /* 0x04: sPrepareThread */
    u8 *decodeBuffer;             /* 0x08: sDecodeBuffer */
} data_020ddb04;


void OS_LockMutex(OSMutex * mutex);

void OS_UnlockMutex(OSMutex * mutex);

void NNS_SndStrmFreeChannel(NNSSndStrm * stream);

extern NNSSndStrmThread data_020ddcb4;

extern void func_0203a160(NNSSndStrmPlayer * player);

extern void func_0203a160 (NNSSndStrmPlayer * player);




void func_0203a444 (void * mem, u32, u32 data1, u32)
{
    NNSSndStrmPlayer * player = (NNSSndStrmPlayer *)data1;

    if (mem == player->buffer) {
        OS_LockMutex(&data_020ddcb4.mutex);
        if (data_020ddb04.prepareThread) OS_LockMutex(&data_020ddb04.prepareThread->mutex);

        func_0203a160(player);

        player->buffer = NULL;
        player->bufSize = 0;

        player->numChannels = 0;
        if (player->allocChannelCount > 0) {
            NNS_SndStrmFreeChannel(&player->stream);
            player->allocChannelCount = 0;
        }

        OS_UnlockMutex(&data_020ddcb4.mutex);
        if (data_020ddb04.prepareThread) OS_UnlockMutex(&data_020ddb04.prepareThread->mutex);
    }
}
