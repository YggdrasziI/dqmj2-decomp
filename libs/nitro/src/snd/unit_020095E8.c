/* NitroSDK; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below). The defined data is reached through the .bss
 * section symbol, which tools/lib_unit_gen.py --source does not map to a name:
 * checked with the objdiff report (100 % code and .bss).
 * File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"
#include "nitro/os.h"

typedef int PXIFifoTag;
typedef struct SNDCommand {
    struct SNDCommand *next;      /* 0x00 */
    u32 id;                       /* 0x04 */
    u32 arg[4];                   /* 0x08 */
} SNDCommand;                     /* 0x18 */
typedef struct SNDSharedWork SNDSharedWork;
#define SND_COMMAND_NUM 256
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

/* The command queue's scalars, defined here: mwcc addresses them from the first one
 * (data_020cc080) and lays them out in reverse declaration order, the last one
 * appended (khdays-decomp's layout; SDK names from its comments). This unit owns
 * their .bss (0x020CC080-0x020CC0A4). */
int data_020cc09c = 0;            /* sWaitingCommandListCount */
int data_020cc098 = 0;            /* sWaitingCommandListQueueWrite */
int data_020cc094 = 0;            /* sWaitingCommandListQueueRead */
SNDCommand *data_020cc090 = 0;    /* sFreeListEnd */
SNDCommand *data_020cc08c = 0;    /* sReserveListEnd */
SNDCommand *data_020cc088 = 0;    /* sReserveList */
u32 data_020cc084 = 0;            /* sFinishedTag */
SNDCommand *data_020cc080 = 0;    /* sFreeList */
u32 data_020cc0a0 = 0;            /* sCurrentTag */
extern SNDCommand *data_020cc0a4[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];   /* sWaitingCommandListQueue */
#define sWaitingCommandListQueue data_020cc0a4
extern SNDSharedWork data_020447a0;   /* sSharedWork (0x280 bytes in this SDK, unaligned) */
#define sSharedWork data_020447a0
extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));   /* sCommandArray */
#define sCommandArray data_02044a20
extern SNDSharedWork *data_02046280;   /* SNDi_SharedWork */
#define SNDi_SharedWork data_02046280

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SpinWait(u32 cycles);   /* OS_SpinWait */
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void InitPXI(void);
extern void SNDi_InitSharedWork(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *SND_AllocCommand(u32 flags);
extern void SND_PushCommand(SNDCommand *command);   /* SND_PushCommand */
extern BOOL SND_FlushCommand(u32 flags);              /* SND_FlushCommand */

/* SND_RecvCommandReply -- NitroSDK snd_command.c: SND_RecvCommandReply. */
const SNDCommand * SND_RecvCommandReply (u32 flags)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();
    SNDCommand * commandList;
    SNDCommand * commandListEnd;

    if (flags & SND_COMMAND_BLOCK) {
        while (data_020cc084 == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(bak_psr);
            OS_SpinWait(100);
            bak_psr = OS_DisableInterrupts();
        }
    } else {
        if (data_020cc084 == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(bak_psr);
            return NULL;
        }
    }

    commandList = sWaitingCommandListQueue[data_020cc094];
    data_020cc094++;
    if (data_020cc094 > SND_PXI_FIFO_MESSAGE_BUFSIZE)
        data_020cc094 = 0;

    commandListEnd = commandList;
    while (commandListEnd->next != NULL) {
        commandListEnd = commandListEnd->next;
    }

    if (data_020cc090 != NULL) {
        data_020cc090->next = commandList;
    } else {
        data_020cc080 = commandList;
    }

    data_020cc090 = commandListEnd;

    data_020cc09c--;
    data_020cc084++;

    (void)OS_RestoreInterrupts(bak_psr);
    return commandList;
}
