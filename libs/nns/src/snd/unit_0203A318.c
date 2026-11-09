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

extern void FreeCommandBuffer(LoadCommand * command);

extern void FreeCommandBuffer (LoadCommand * command);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

void RemoveCommandByPlayer (NNSFndList * commandList, const NNSSndStrmPlayer * player)
{
    OSIntrMode old;
    LoadCommand * command;
    LoadCommand * next;

    old = OS_DisableInterrupts();

    for (command = (LoadCommand *)NNS_FndGetNextListObject(commandList, NULL);
         command != NULL; command = next) {
        next = (LoadCommand *)NNS_FndGetNextListObject(commandList, command);

        if (command->player == player) {
            NNS_FndRemoveListObject(commandList, command);
            FreeCommandBuffer(command);
        }
    }

    (void)OS_RestoreInterrupts(old);
}
