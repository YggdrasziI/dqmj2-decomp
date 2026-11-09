/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/snd.h"

/* The file's static data: one block in this build, read from its start */
extern struct {
    u32 captureLock;              /* 0x00 */
    u32 alarmLock;                /* 0x04: sAlarmLock */
    u32 channelLock;              /* 0x08: sChannelLock */
} data_020ddab8;





int NNS_SndAllocAlarm (void)
{
    int alarmNo;
    u32 mask = 1;

    for (alarmNo = 0; alarmNo < SND_ALARM_NUM; alarmNo++, mask <<= 1) {
        if ((data_020ddab8.alarmLock & mask) == 0) {
            data_020ddab8.alarmLock |= mask;
            return alarmNo;
        }
    }

    return -1;
}
