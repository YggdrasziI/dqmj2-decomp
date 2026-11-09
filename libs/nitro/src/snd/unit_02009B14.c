/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define SND_COMMAND_NUM 256

#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8

#define SND_COMMAND_NOBLOCK 0

#define SND_COMMAND_BLOCK 1

#define SND_COMMAND_SHARED_WORK 0x1d

#define PXI_FIFO_TAG_SOUND 7

#define PXI_PROC_ARM7 1

#define sFreeList data_02044748

#define sWaitingCommandListQueue data_0204476c

#define sSharedWork data_020447a0

#define sCommandArray data_02044a20

#define SNDi_SharedWork data_02046280

typedef int PXIFifoTag;

typedef struct SNDCommand {
    struct SNDCommand *next;      
    u32 id;                       
    u32 arg[4];                   
} SNDCommand;

typedef struct SNDSharedWork SNDSharedWork;

extern int sWaitingCommandListCount;

extern int sWaitingCommandListQueueWrite;

extern int sWaitingCommandListQueueRead;

extern SNDCommand *sFreeListEnd;

extern SNDCommand *sReserveListEnd;

extern SNDCommand *sReserveList;

extern u32 sFinishedTag;

extern SNDCommand *data_02044748;

extern u32 sCurrentTag;

extern SNDCommand *data_0204476c[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];

extern SNDSharedWork data_020447a0;

extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));

extern SNDSharedWork *data_02046280;

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern void OS_SpinWait(u32 cycles);

extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));

extern BOOL PXI_IsCallbackReady(int fifotag, int proc);

extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);

extern BOOL IsCommandAvailable(void);

extern void InitPXI(void);

extern void SNDi_InitSharedWork(SNDSharedWork *work);

extern u32 SNDi_GetFinishedCommandTag(void);

extern SNDCommand *SND_AllocCommand(u32 flags);

extern void SND_PushCommand(SNDCommand *command);

extern BOOL SND_FlushCommand(u32 flags);

void InitPXI (void)
{
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_SOUND, PxiFifoCallback);

    if (IsCommandAvailable()) {
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_SOUND, PXI_PROC_ARM7)) {
            OS_SpinWait(100);
        }
    }
}
