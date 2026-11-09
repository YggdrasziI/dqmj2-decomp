/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/hw.h"

#pragma pack(4)

#pragma pack()

#define OS_TIMER_1 1

#define OS_TIMER_PRESCALER_64 (1UL << 0)

#define OSi_ALARM_TIMERCONTROL    (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

#define OSi_ALARM_TIMER           OS_TIMER_1

#define OSi_ALARM_IE_TIMER        (1UL << 4)

#define OSi_UseAlarm data_020cc004.useAlarm

#define OSi_AlarmQueue data_020cc004.queue

typedef void *OSMessage;

typedef int OSTimer;

typedef u32 OSIrqMask;

typedef void (*OSAlarmHandler)(void *);

typedef struct OSAlarm OSAlarm;

struct OSAlarm {
    OSAlarmHandler handler;       
    void *arg;                    
    u32 tag;                      
    OSTick fire;                  
    OSAlarm *prev;                
    OSAlarm *next;                
    OSTick period;                
    OSTick start;                 
};

struct OSiAlarmQueue {
    OSAlarm *head;
    OSAlarm *tail;
};

typedef struct {
    u8 reserved[0x3fc0];
    u8 sysrv[0x38];
    vu32 intr_check;              
} OSDtcm;

extern OSDtcm data_027e0000;

extern OSTick OS_GetTick(void);

extern void OSi_EnterTimerCallback(int timerNo, void (*callback)(void *), void *arg);

extern OSIrqMask OS_EnableIrqMask(OSIrqMask intr);

extern OSIrqMask OS_DisableIrqMask(OSIrqMask intr);

extern void OSi_AlarmHandler(void *arg);

extern struct { u16 useAlarm; u16 pad; struct OSiAlarmQueue queue; } data_020cc004;

extern void OSi_SetTimer(OSAlarm *alarm);

extern void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire);

static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    *((vu16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    *((vu16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}

static inline void OS_SetIrqCheckFlag(OSIrqMask intr)
{
    data_027e0000.intr_check |= (u32)intr;
}

void OSi_InsertAlarm (OSAlarm * alarm, OSTick fire)
{
    OSAlarm * prev;
    OSAlarm * next;

    if (alarm->period > 0) {
        OSTick tick = OS_GetTick();

        fire = alarm->start;
        if (alarm->start < tick) {
            fire += alarm->period * ((tick - alarm->start) / alarm->period + 1);
        }
    }

    alarm->fire = fire;

    for (next = OSi_AlarmQueue.head; next; next = next->next) {

        if ((s64)(fire - next->fire) >= 0) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;

        if (prev) {
            prev->next = alarm;
        } else {
            OSi_AlarmQueue.head = alarm;
            OSi_SetTimer(alarm);
        }

        return;
    }

    alarm->next = 0;
    prev = OSi_AlarmQueue.tail;
    OSi_AlarmQueue.tail = alarm;
    alarm->prev = prev;

    if (prev) {
        prev->next = alarm;
    } else {
        OSi_AlarmQueue.head = OSi_AlarmQueue.tail = alarm;
        OSi_SetTimer(alarm);
    }
}
