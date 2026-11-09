/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

typedef struct LoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer * player;
    NNSSndStrmCallbackStatus status;
    int numChannels;
    void * buffer[6 ];
    u32 bufLen;
} LoadCommand;

void OS_SleepThread(OSThreadQueue * queue);

void OS_LockMutex(OSMutex * mutex);

void OS_UnlockMutex(OSMutex * mutex);

extern LoadCommand * ReadCommandBuffer(NNSFndList * commandList);

extern void FreeCommandBuffer(LoadCommand * command);

extern void NNSi_SndArcStrm_MakeWaveData(LoadCommand * command);

extern LoadCommand * ReadCommandBuffer (NNSFndList * commandList);

extern void FreeCommandBuffer (LoadCommand * command);

extern void NNSi_SndArcStrm_MakeWaveData (LoadCommand * command);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

void StrmThread (void * arg)
{
    NNSSndStrmThread * thread = (NNSSndStrmThread *)arg;

    while (1) {
        LoadCommand * command;

        OS_SleepThread(&thread->threadQ);

        while (1) {
            OS_LockMutex(&thread->mutex);

            command = ReadCommandBuffer(&thread->commandList);
            if (command == NULL) {
                OS_UnlockMutex(&thread->mutex);
                break;
            }

            NNSi_SndArcStrm_MakeWaveData(command);
            FreeCommandBuffer(command);
            OS_UnlockMutex(&thread->mutex);
        }
    }
}
