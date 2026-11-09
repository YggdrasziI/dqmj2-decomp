/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#define HW_MAIN_MEM 0x02000000

#define CARD_BACKUP_CAPS_READ               (u32)(1 << CARD_REQ_READ_BACKUP)

#define CARD_BACKUP_CAPS_AVAILABLE          (u32)(CARD_BACKUP_CAPS_READ - 1)

#define CARD_BACKUP_CAPS_WRITE              (u32)(1 << CARD_REQ_WRITE_BACKUP)

#define CARD_BACKUP_CAPS_PROGRAM            (u32)(1 << CARD_REQ_PROGRAM_BACKUP)

#define CARD_BACKUP_CAPS_VERIFY             (u32)(1 << CARD_REQ_VERIFY_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_PAGE         (u32)(1 << CARD_REQ_ERASE_PAGE_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_SECTOR       (u32)(1 << CARD_REQ_ERASE_SECTOR_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_CHIP         (u32)(1 << CARD_REQ_ERASE_CHIP_BACKUP)

#define CARD_BACKUP_CAPS_READ_STATUS        (u32)(1 << CARD_REQ_READ_STATUS)

#define CARD_BACKUP_CAPS_WRITE_STATUS       (u32)(1 << CARD_REQ_WRITE_STATUS)

#define CARD_BACKUP_CAPS_ERASE_SUBSECTOR    (u32)(1 << CARD_REQ_ERASE_SUBSECTOR_BACKUP)

#define CARD_BACKUP_TYPE_DEVICE_SHIFT   0

#define CARD_BACKUP_TYPE_DEVICE_MASK    0xFF

#define CARD_BACKUP_TYPE_DEVICE_EEPROM  1

#define CARD_BACKUP_TYPE_DEVICE_FLASH   2

#define CARD_BACKUP_TYPE_DEVICE_FRAM    3

#define CARD_BACKUP_TYPE_SIZEBIT_SHIFT  8

#define CARD_BACKUP_TYPE_SIZEBIT_MASK   0xFF

#define CARD_BACKUP_TYPE_VENDER_SHIFT   16

#define CARD_BACKUP_TYPE_VENDER_MASK    0xFF

#define CARD_BACKUP_TYPE_NOT_USE        0

#define CARD_THREAD_PRIORITY_DEFAULT    4

#define OS_LOCK_ID_ERROR (-3)

#define PXI_FIFO_TAG_FS 11

#define HW_ROM_HEADER_BUF       0x027FFE00

#define HW_CARD_ROM_HEADER      0x027FFA80

#define HW_CARD_ROM_HEADER_SIZE 0x160

#define HW_WM_BOOT_BUF          0x027FFC40

#define MB_TYPE_MULTIBOOT       2

#define OS_Panic(...) OS_Terminate()

#define OS_TPanic(...) OS_Terminate()

#define cardi_backup_assert ((char *)0x02000b8c)

#define SDK_USING_BACKUP() OSi_ReferSymbol((void *)cardi_backup_assert)

#define OS_GetCurrentThread() (data_02044330.current)

#define cardi_common data_020cde00

#define cardi_arg data_020cdda0

#define cardi_thread_stack_end data_020ce420

#define MI_CpuFillFast(dest, data, size) MIi_CpuClearFast((data), (dest), (size))

#define CARD_Enable func_02010010

typedef void *OSMessage;

typedef s32 CARDiOwner;

typedef int CARDResult;

typedef int CARDBackupType;

typedef int CARDRequest;

typedef int CARDRequestMode;

typedef int CARDTargetMode;

typedef void (*MIDmaCallback)(void *);

typedef struct OSThreadQueue { struct OSThread *head; struct OSThread *tail; } OSThreadQueue;

enum {
    CARD_RESULT_SUCCESS = 0, CARD_RESULT_FAILURE, CARD_RESULT_INVALID_PARAM, CARD_RESULT_UNSUPPORTED,
    CARD_RESULT_TIMEOUT, CARD_RESULT_ERROR, CARD_RESULT_NO_RESPONSE, CARD_RESULT_CANCELED
};

enum { CARD_TARGET_NONE, CARD_TARGET_ROM, CARD_TARGET_BACKUP };

enum {
    CARD_REQ_INIT = 0, CARD_REQ_ACK, CARD_REQ_IDENTIFY, CARD_REQ_READ_ID, CARD_REQ_READ_ROM,
    CARD_REQ_WRITE_ROM, CARD_REQ_READ_BACKUP, CARD_REQ_WRITE_BACKUP, CARD_REQ_PROGRAM_BACKUP,
    CARD_REQ_VERIFY_BACKUP, CARD_REQ_ERASE_PAGE_BACKUP, CARD_REQ_ERASE_SECTOR_BACKUP,
    CARD_REQ_ERASE_CHIP_BACKUP, CARD_REQ_READ_STATUS, CARD_REQ_WRITE_STATUS,
    CARD_REQ_ERASE_SUBSECTOR_BACKUP, CARD_REQ_MAX
};

enum { CARD_REQUEST_MODE_RECV, CARD_REQUEST_MODE_SEND, CARD_REQUEST_MODE_SEND_VERIFY, CARD_REQUEST_MODE_SPECIAL };

enum {
    CARD_STAT_INIT = (1 << 0), CARD_STAT_INIT_CMD = (1 << 1), CARD_STAT_BUSY = (1 << 2),
    CARD_STAT_TASK = (1 << 3), CARD_STAT_RECV = (1 << 4), CARD_STAT_REQ = (1 << 5), CARD_STAT_CANCEL = (1 << 6)
};

typedef struct CARDiCommandArg {
    CARDResult result;            
    CARDBackupType type;          
    u32 id;                       
    u32 src;                      
    u32 dst;                      
    u32 len;                      
    struct {                      
        u32 total_size;           
        u32 sect_size;            
        u32 subsect_size;         
        u32 page_size;            
        u32 addr_width;           
        u32 program_page;         
        u32 write_page;           
        u32 write_page_total;     
        u32 erase_chip;           
        u32 erase_chip_total;     
        u32 erase_sector;         
        u32 erase_sector_total;   
        u32 erase_subsector;      
        u32 erase_subsector_total;
        u32 erase_page;           
        u8 initial_status;        
        u8 padding1[3];
        u32 caps;                 
        u8 padding2[4];
    } spec;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *cmd;         
    int command;                  
    volatile CARDiOwner lock_owner;   
    volatile int lock_ref;        
    OSThreadQueue lock_queue[1];  
    CARDTargetMode lock_target;   
    u32 src;                      
    u32 dst;                      
    u32 len;                      
    u32 dma;                      
    CARDRequest req_type;         
    int req_retry;                
    CARDRequestMode req_mode;     
    MIDmaCallback callback;       
    void *callback_arg;           
    void (*task_func)(struct CARDiCommon *);   
    u8 thread[0xc0];              
    struct OSThread *cur_th;      
    u32 priority;                 
    OSThreadQueue busy_q[1];      
    volatile u32 flag;            
    u32 flush_threshold_ic;       
    u32 flush_threshold_dc;       
    u8 backup_cache_page_buf[256] __attribute__((aligned(32)));   
} CARDiCommon;

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern void OS_SleepThread(OSThreadQueue *queue);

extern void OS_WakeupThread(OSThreadQueue *queue);

extern void OS_WakeupThreadDirect(void *thread);

extern void OS_Terminate(void);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern void MI_CpuFill8(void *dst, u8 data, u32 size);

extern void DC_FlushRange(const void *startAddr, u32 nBytes);

extern void DC_InvalidateRange(void *startAddr, u32 nBytes);

extern void DC_WaitWriteBufferEmpty(void);

extern BOOL CARDi_Request(CARDiCommon *p, int req_type, int retry_max);

extern void CARDi_SetTask(void (*task)(CARDiCommon *));

extern u32 CARD_GetBackupSectorSize(void);

extern void CARD_CheckEnabled(void);

extern void OSi_ReferSymbol(void *symbol);

extern struct { u32 initialized; struct OSThread *current; } data_02044330;

extern CARDiCommon data_020cde00 __attribute__((aligned(32)));

extern CARDiCommandArg data_020cdda0 __attribute__((aligned(32)));

extern u8 data_020ce420[];

extern void MIi_CpuClearFast(u32 data, void *destp, u32 size);

extern void OS_CreateThread(void *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);

extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(int, u32, BOOL));

extern void CARDi_TaskThread(void *arg);

extern void CARDi_OnFifoRecv(int tag, u32 data, BOOL err);

extern void func_02010010(BOOL enable);

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}

static inline void CARDi_WaitTask(CARDiCommon *p, MIDmaCallback callback, void *callback_arg)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    while ((p->flag & CARD_STAT_BUSY) != 0) {
        OS_SleepThread(p->busy_q);
    }

    p->flag |= CARD_STAT_BUSY;
    p->callback = callback;
    p->callback_arg = callback_arg;

    (void)OS_RestoreInterrupts(bak_psr);
}

static inline void CARDi_EndTask(CARDiCommon *p, BOOL is_own_task)
{
    const MIDmaCallback func = p->callback;
    void *const arg = p->callback_arg;

    {
        OSIntrMode bak_psr = OS_DisableInterrupts();

        p->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
        OS_WakeupThread(p->busy_q);

        if ((p->flag & CARD_STAT_RECV) != 0) {
            OS_WakeupThreadDirect(p->thread);
        }

        (void)OS_RestoreInterrupts(bak_psr);
    }

    if (is_own_task && func) {
        (*func)(arg);
    }
}

static inline BOOL MB_IsMultiBootChild(void)
{
    return *(const u16 *)HW_WM_BOOT_BUF == MB_TYPE_MULTIBOOT;
}

void CARDi_InitCommon (void)
{
	CARDiCommon *p = &cardi_common;

	p->lock_owner = OS_LOCK_ID_ERROR;
	p->lock_ref = 0;
	p->lock_target = CARD_TARGET_NONE;

	p->cmd = &cardi_arg;
	MI_CpuFillFast(&cardi_arg, 0x00, sizeof(cardi_arg));
	DC_FlushRange(&cardi_arg, sizeof(cardi_arg));

	p->flush_threshold_ic = 0xFFFFFFFF;
	p->flush_threshold_dc = 0xFFFFFFFF;

	if (!MB_IsMultiBootChild()) {
		MI_CpuCopy8((const void *)HW_ROM_HEADER_BUF, (void *)HW_CARD_ROM_HEADER,
		            HW_CARD_ROM_HEADER_SIZE);
	}

	OS_InitThreadQueue(p->lock_queue);
	OS_InitThreadQueue(p->busy_q);
	p->priority = CARD_THREAD_PRIORITY_DEFAULT;
	OS_CreateThread(p->thread,
	                CARDi_TaskThread, NULL,
	                cardi_thread_stack_end,
	                0x400, p->priority);
	OS_WakeupThreadDirect(p->thread);

	PXI_SetFifoRecvCallback(PXI_FIFO_TAG_FS, CARDi_OnFifoRecv);

	if (!MB_IsMultiBootChild()) {
		CARD_Enable(TRUE);
	}
}
