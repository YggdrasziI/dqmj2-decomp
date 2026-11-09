/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/snd.h"

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

#define sCallbackTable data_020cdb60

typedef struct AlarmCallbackInfo {
    SNDAlarmHandler func;         
    void *arg;                    
    u8 id;                        
} AlarmCallbackInfo;

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern AlarmCallbackInfo data_020cdb60[8];

void SNDi_CallAlarmHandler(int msg)
{
    AlarmCallbackInfo *info;
    int alarmNo = msg & 0xff;
    int id = (msg >> 8) & 0xff;

    info = &sCallbackTable[alarmNo];

    if (id == info->id) {
        if (info->func != NULL) {
            info->func(info->arg);
        }
    }
}
