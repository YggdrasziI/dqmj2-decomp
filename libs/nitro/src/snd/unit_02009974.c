/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/snd.h"

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern BOOL SND_IsFinishedCommandTag(u32 tag);

extern const SNDCommand *SND_RecvCommandReply(u32 flags);

extern void RequestCommandProc(void);

void SND_WaitForCommandProc(u32 tag)
{
    if (SND_IsFinishedCommandTag(tag)) {
        return;
    }

    while (SND_RecvCommandReply(SND_COMMAND_NOBLOCK) != NULL) {
    }

    if (SND_IsFinishedCommandTag(tag)) {
        return;
    }

    RequestCommandProc();

    while (!SND_IsFinishedCommandTag(tag)) {
        (void)SND_RecvCommandReply(SND_COMMAND_BLOCK);
    }
}
