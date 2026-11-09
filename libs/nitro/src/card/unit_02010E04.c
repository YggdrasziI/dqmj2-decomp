/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

enum {
    CARD_RESULT_SUCCESS = 0,
    CARD_STAT_BUSY = 1 << 2,
    CARD_STAT_TASK = 1 << 3,
    CARD_STAT_RECV = 1 << 4,
    CARD_STAT_CANCEL = 1 << 6,
    CARD_ROM_PAGE_SIZE = 512
};

typedef void (*CARDCallback)(void *argument);

struct CARDiCommandArg {
    int result;
};

struct CARDiCommon {
    struct CARDiCommandArg *cmd;
    s32 command;
    volatile s32 lock_owner;
    volatile s32 lock_ref;
    u8 lock_queue[8];
    s32 lock_target;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    s32 req_type;
    s32 req_retry;
    s32 req_mode;
    CARDCallback callback;
    void *callback_arg;
    void (*task_func)(struct CARDiCommon *common);
    u8 thread[0xc8];
    u8 busy_q[8];
    volatile u32 flag;
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
};

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern BOOL CARDi_ReadFromCache(struct CARDRomStat *state);

extern u32 CARDi_ReadRomIDCore(void);

extern void CARDi_CheckPulledOutCore(u32 id);

extern void OS_WakeupThread(void *queue);

extern void OS_WakeupThreadDirect(void *thread);

extern struct CARDiCommon data_020cde00 __attribute__((aligned(32)));

extern struct CARDRomStat data_020ce440;

void CARDi_ReadRomSyncCore(void)
{
    struct CARDRomStat *state = &data_020ce440;
    struct CARDiCommon *common;
    CARDCallback callback;
    void *callbackArgument;
    int interruptState;

    if (CARDi_ReadFromCache(state)) {
        (*state->read_func)(state);
    }
    common = &data_020cde00;
    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    common->cmd->result = CARD_RESULT_SUCCESS;
    callback = common->callback;
    callbackArgument = common->callback_arg;
    interruptState = OS_DisableInterrupts();
    common->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
    OS_WakeupThread(common->busy_q);
    if ((common->flag & CARD_STAT_RECV) != 0) {
        OS_WakeupThreadDirect(common->thread);
    }
    OS_RestoreInterrupts(interruptState);
    if (callback != 0) {
        callback(callbackArgument);
    }
}
