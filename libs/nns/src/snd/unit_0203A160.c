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

void NNS_SndStrmStop(NNSSndStrm * stream);

extern NNSSndStrmThread data_020ddcb4;

extern void OSi_DestroyThread(NNSSndStrmPlayer * player);

extern void OSi_DestroyThread (NNSSndStrmPlayer * player);




void func_0203a160 (NNSSndStrmPlayer * player)
{

    OS_LockMutex(&data_020ddcb4.mutex);
    if (data_020ddb04.prepareThread) OS_LockMutex(&data_020ddb04.prepareThread->mutex);

    if (player->playFlag) {
        NNS_SndStrmStop(&player->stream);
    }

    if (player->activeFlag) {
        player->cancelStreamFunc(player);
    }

    OSi_DestroyThread(player);

    OS_UnlockMutex(&data_020ddcb4.mutex);
    if (data_020ddb04.prepareThread) OS_UnlockMutex(&data_020ddb04.prepareThread->mutex);
}
