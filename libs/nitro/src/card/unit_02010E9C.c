/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

enum {
    CARD_STAT_BUSY = 1 << 2
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
    u8 thread[0xc0];
    void *cur_th;
    u32 priority;
    u8 busy_q[8];
    volatile u32 flag;
    u8 dummy[8];
    u8 backup_cache_page_buf[256] __attribute__((aligned(32)));
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[0x200];
};

extern void CARD_CheckEnabled(void);

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_SleepThread(void *queue);

extern void MI_StopDma(u32 channel);

extern BOOL CARDi_TryReadCardDma(struct CARDRomStat *state);

extern void func_02010ff8(void);

extern void CARDi_SetTask(void (*task)(struct CARDiCommon *common));

extern void CARDi_ReadRomSyncCore(struct CARDiCommon *common);

extern struct CARDRomStat data_020ce440 __attribute__((aligned(32)));

extern struct CARDiCommon data_020cde00;

extern u32 data_020ce420;

extern struct OSiThreadInfoPrefix data_020cbce4;

static inline void Card_WaitTask(struct CARDiCommon *common,
                                 CARDCallback callback,
                                 void *callbackArgument)
{
    int interruptState = OS_DisableInterrupts();
    while ((common->flag & CARD_STAT_BUSY) != 0) {
        OS_SleepThread(common->busy_q);
    }
    common->flag |= CARD_STAT_BUSY;
    common->callback = callback;
    common->callback_arg = callbackArgument;
    OS_RestoreInterrupts(interruptState);
}

void CARDi_ReadRom(u32 dma, const void *source, void *destination, u32 length,
                   CARDCallback callback, void *callbackArgument, BOOL asynchronous)
{
    struct CARDRomStat *const state = &data_020ce440;
    struct CARDiCommon *const common = &data_020cde00;

    CARD_CheckEnabled();
    Card_WaitTask(common, callback, callbackArgument);

    common->dma = dma;
    common->src = (u32)source + data_020ce420;
    common->dst = (u32)destination;
    common->len = length;
    if (dma <= MI_DMA_MAX_NUM) {
        MI_StopDma(dma);
    }

    if (CARDi_TryReadCardDma(state)) {
        if (!asynchronous) {
            func_02010ff8();
        }
    } else if (asynchronous) {
        CARDi_SetTask(CARDi_ReadRomSyncCore);
    } else {
        common->cur_th = data_020cbce4.current_thread;
        CARDi_ReadRomSyncCore(common);
    }
}
