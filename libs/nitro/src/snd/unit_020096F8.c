/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/snd.h"

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern BOOL IsCommandAvailable(void);

extern SNDCommand *SND_PopFreeCommand(void);

extern int SND_CountWaitingCommand(void);

extern const SNDCommand *SND_RecvCommandReply(u32 flags);

extern BOOL SND_FlushCommand(u32 flags);

extern void RequestCommandProc(void);

SNDCommand *SND_AllocCommand(u32 flags)
{
    SNDCommand *command;

    if (!IsCommandAvailable())
        return NULL;

    command = SND_PopFreeCommand();
    if (command != NULL)
        return command;

    if ((flags & SND_COMMAND_BLOCK) == 0)
        return NULL;

    if (SND_CountWaitingCommand() > 0) {
        while (SND_RecvCommandReply(SND_COMMAND_NOBLOCK) != NULL) {
        }

        command = SND_PopFreeCommand();
        if (command != NULL)
            return command;
    } else {
        (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    }

    RequestCommandProc();

    do {
        (void)SND_RecvCommandReply(SND_COMMAND_BLOCK);
        command = SND_PopFreeCommand();
    } while (command == NULL);

    return command;
}
