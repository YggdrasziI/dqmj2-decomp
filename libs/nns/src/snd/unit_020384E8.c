/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

/* The file's static data: one block in this build, read from its start */
extern struct {
    u32 captureLock;              /* 0x00 */
    u32 alarmLock;                /* 0x04: sAlarmLock */
    u32 channelLock;              /* 0x08: sChannelLock */
} data_020ddab8;


void SND_LockChannel(u32 chBitMask, u32 flags);




BOOL NNS_SndLockChannel (u32 chBitFlag)
{
    if (chBitFlag == 0) return TRUE;
    if (chBitFlag & data_020ddab8.channelLock) return FALSE;

    SND_LockChannel(chBitFlag, 0);

    data_020ddab8.channelLock |= chBitFlag;

    return TRUE;
}
