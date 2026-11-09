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

#define HW_INTR_CHECK_BUF ((char *)&data_027e0000 + 0x3ff8)

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

extern u32 data_027e0000;

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
    *(vu32 *)HW_INTR_CHECK_BUF |= (u32)intr;
}

void OSi_ArrangeTimer (void)
{
    OSTick tick;
    OSAlarm * alarm;
    OSAlarm * next;
    OSAlarmHandler handler;

    OS_SetTimerControl(OSi_ALARM_TIMER, 0);
    (void)OS_DisableIrqMask(OSi_ALARM_IE_TIMER);
    OS_SetIrqCheckFlag(OSi_ALARM_IE_TIMER);

    tick = OS_GetTick();
    alarm = OSi_AlarmQueue.head;

    if (alarm == NULL) {
        return;
    }

    if (tick < alarm->fire) {
        OSi_SetTimer(alarm);
        return;
    }

    next = alarm->next;
    OSi_AlarmQueue.head = next;

    if (next == NULL) {
        OSi_AlarmQueue.tail = NULL;
    } else {
        next->prev = NULL;
    }

    handler = alarm->handler;

    if (alarm->period == 0) {
        alarm->handler = NULL;
    }

    if (handler) {
        (handler) (alarm->arg);
    }

    if (alarm->period > 0) {
        alarm->handler = handler;
        OSi_InsertAlarm(alarm, 0);
    }

    if (OSi_AlarmQueue.head) {
        OSi_SetTimer(OSi_AlarmQueue.head);
    }
}
