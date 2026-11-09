/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/hw.h"

#define OS_CONSOLE_SIZE_MASK 0x00000003

#define OS_CONSOLE_SIZE_4MB  0x00000001

#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)

#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)

#define OSi_MAIN_ARENA_HI_DEFAULT   HW_MAIN_MEM_MAIN_END

#define OSi_MAINEX_ARENA_HI_DEFAULT HW_MAIN_MEM_DEBUGGER

#define OSi_DTCM_ARENA_LO_DEFAULT   ((u32)SDK_SECTION_ARENA_DTCM_START)

#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT HW_WRAM

#define HW_DTCM ((u32)&data_027e0000)

#define OSi_Initialized data_02044588.initialized

#define OSi_MainExArenaEnabled data_02044588.mainExArenaEnabled

#define OS_THREAD_LAUNCHER_PRIORITY 16

#define OS_THREAD_PRIORITY_MAX 31

#define OS_THREAD_SPECIFIC_MAX 3

#define OSi_CurrentThreadPtr data_0204430c.currentThreadPtr

#define OSi_IsThreadInitialized data_0204430c.isThreadInitialized

#define OSi_ThreadInfo data_0204430c.threadInfo

#define OSi_IdleThread data_02044340

#define OSi_LauncherThread data_02044400

#define OSi_IDLE_CHECKNUM_SIZE (sizeof(u32) * 2 + HW_SVC_STACK_SIZE)

#define OSi_IDLE_SVC_SIZE (sizeof(u32) * 32)

#define OSi_IDLE_THREAD_STACK_SIZE (OSi_IDLE_CHECKNUM_SIZE + OSi_IDLE_SVC_SIZE)

#define OSi_IdleThreadStack data_020444c0

#define OSi_STACK_CHECKNUM_BOTTOM 0xfddb597dUL

#define OSi_STACK_CHECKNUM_TOP    0x7bf9dd5bUL

#define OSi_LAUNCHER_STACK_LO_DEFAULT SDK_SECTION_ARENA_DTCM_START

#define OSi_LAUNCHER_STACK_HI_MAX (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)

#define OSi_LAUNCHER_STACK_BOTTOM (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)

#define OSi_SYSTEMWORK_THREADINFO_MAINP (*(OSThreadInfo **)0x027fffa0)

#define OS_SetSwitchThreadCallback OS_SetIrqWorkField30

#define NVRAMCONFIG_SIZE 0x74

typedef void *OSMessage;

typedef int OSArenaId;

enum { OS_ARENA_MAIN = 0, OS_ARENA_MAIN_SUBPRIV, OS_ARENA_MAINEX, OS_ARENA_ITCM, OS_ARENA_DTCM, OS_ARENA_SHARED, OS_ARENA_WRAM_MAIN, OS_ARENA_WRAM_SUB, OS_ARENA_WRAM_SUBPRIV, OS_ARENA_MAX };

typedef struct OSThread OSThread;

typedef struct OSThreadQueue { OSThread *head; OSThread *tail; } OSThreadQueue;

typedef struct OSThreadLink { OSThread *prev; OSThread *next; } OSThreadLink;

typedef struct OSMutexQueue { void *head; void *tail; } OSMutexQueue;

typedef int OSThreadState;

enum { OS_THREAD_STATE_WAITING = 0, OS_THREAD_STATE_READY = 1, OS_THREAD_STATE_TERMINATED = 2 };

struct OSThread {
    u8 context[0x64];             
    OSThreadState state;          
    OSThread *next;               
    u32 id;                       
    u32 priority;                 
    void *profiler;               
    OSThreadQueue *queue;         
    OSThreadLink link;            
    void *mutex;                  
    OSMutexQueue mutexQueue;      
    u32 stackTop;                 
    u32 stackBottom;              
    u32 stackWarningOffset;       
    OSThreadQueue joinQueue;      
    void *specific[OS_THREAD_SPECIFIC_MAX];   
    void *alarmForSleep;          
    void (*destructor)(void *);   
    void *userParameter;          
    int systemErrno;              
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;       
    u16 irqDepth;                 
    OSThread *current;            
    OSThread *list;               
    void *switchCallback;         
} OSThreadInfo;

typedef struct {
    unsigned char pad0[0x64];
    unsigned short bits : 3;
    unsigned short : 13;
} SrcA;

typedef struct {
    unsigned char pad0[2];
    unsigned char bits4 : 4;
    unsigned char : 4;
} SrcB;

extern void SDK_SYS_STACKSIZE(void);

extern void SDK_IRQ_STACKSIZE(void);

extern void SDK_SECTION_ARENA_DTCM_START(void);

extern u32 data_027e0000;

extern u32 OS_GetConsoleType(void);

extern struct { BOOL initialized; BOOL mainExArenaEnabled; } data_02044588;

extern struct {
    u32 unused0;                  
    u32 unused4;                  
    OSThread **currentThreadPtr;  
    BOOL isThreadInitialized;     
    u32 unused10[4];              
    int threadIdCount;            
    OSThreadInfo threadInfo;      
} data_0204430c;

extern OSThread data_02044340;

extern OSThread data_02044400;

extern u32 data_020444c0[OSi_IDLE_THREAD_STACK_SIZE / sizeof(u32)];

extern int OS_SetIrqWorkField30(void *callback);

extern void OS_CreateThread(OSThread *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);

extern void OSi_IdleThreadProc(void *arg);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}

static inline void OS_SetCurrentThread(OSThread *thread)
{
    OSi_ThreadInfo.current = thread;
}

void OS_GetMacAddress(u8 *macAddress)
{
    u8 *src;

    src = (u8 *)((u32)HW_NVRAM_USER_INFO + ((NVRAMCONFIG_SIZE + 3) & ~0x00000003));
    MI_CpuCopy8(src, macAddress, 6);
}

void OS_GetOwnerInfo(OSOwnerInfo *info) {
    unsigned char *p = (unsigned char *)0x027ffc80;
    info->language = (unsigned char)((SrcA *)p)->bits;
    info->favoriteColor = ((SrcB *)p)->bits4;
    info->birthday.month = p[3];
    info->birthday.day = p[4];
    info->nickNameLength = (unsigned short)p[0x1a];
    info->commentLength = (unsigned short)p[0x50];
    MIi_CpuCopy16(p + 6, info->nickName, OS_OWNERINFO_NICKNAME_MAX * sizeof(u16));
    MIi_CpuCopy16(p + 0x1c, info->comment, OS_OWNERINFO_COMMENT_MAX * sizeof(u16));
    info->nickName[OS_OWNERINFO_NICKNAME_MAX] = 0;
    info->comment[OS_OWNERINFO_COMMENT_MAX] = 0;
}
