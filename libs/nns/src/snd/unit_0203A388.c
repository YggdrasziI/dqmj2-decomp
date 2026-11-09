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

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

void NNS_FndRemoveListObject(NNSFndList * list, void * object);

void * NNS_FndGetNextListObject(NNSFndList * list, void * object);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

LoadCommand * ReadCommandBuffer (NNSFndList * commandList)
{
    OSIntrMode old;
    LoadCommand * command;

    old = OS_DisableInterrupts();

    command = (LoadCommand *)NNS_FndGetNextListObject(commandList, NULL);
    if (command != NULL) {
        NNS_FndRemoveListObject(commandList, command);

        command->player->commandCount--;
    }

    (void)OS_RestoreInterrupts(old);

    return command;
}
