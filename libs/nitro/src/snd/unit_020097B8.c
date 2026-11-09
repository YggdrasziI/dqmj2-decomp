/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct SNDCommand {
    struct SNDCommand *next;
    unsigned int id;
    unsigned int arg[4];
} SNDCommand;

typedef struct SNDCommandMgr {
    SNDCommand *freeHead;
    unsigned int processedTag;
    SNDCommand *reservedHead;
    SNDCommand *reservedTail;
    SNDCommand *freeTail;
    unsigned int unk14;
    int sentRingIndex;
    int sentBlockCount;
    unsigned int nextTag;
} SNDCommandMgr;

extern SNDCommandMgr data_020cc080;

extern SNDCommand *data_020cc0a4[8];

extern SNDCommand data_020cc360[0x100];

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void DC_FlushRange(void *address, unsigned int size);

extern SNDCommand *SND_RecvCommandReply(int block);

extern int PXI_SendWordByFifo(int channel, unsigned int data, int err);

extern void RequestCommandProc(void);

int SND_FlushCommand(unsigned int flags) {
    int state = OS_DisableInterrupts();

    if (data_020cc080.reservedHead == 0) {
        OS_RestoreInterrupts(state);
        return 1;
    }

    if (data_020cc080.sentBlockCount >= 8) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return 0;
        }
        do {
            SND_RecvCommandReply(1);
        } while (data_020cc080.sentBlockCount >= 8);
        if (data_020cc080.reservedHead == 0) {
            OS_RestoreInterrupts(state);
            return 1;
        }
    }

    DC_FlushRange(data_020cc360, sizeof(data_020cc360));

    if (PXI_SendWordByFifo(7, (unsigned int)data_020cc080.reservedHead, 0) < 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return 0;
        }
        while (data_020cc080.sentBlockCount >= 8 ||
               PXI_SendWordByFifo(7, (unsigned int)data_020cc080.reservedHead, 0) < 0) {
            OS_RestoreInterrupts(state);
            SND_RecvCommandReply(0);
            state = OS_DisableInterrupts();
            DC_FlushRange(data_020cc360, sizeof(data_020cc360));
            if (data_020cc080.reservedHead == 0) {
                OS_RestoreInterrupts(state);
                return 1;
            }
        }
    }

    data_020cc0a4[data_020cc080.sentRingIndex] = data_020cc080.reservedHead;
    data_020cc080.sentRingIndex++;
    if (data_020cc080.sentRingIndex > 8) {
        data_020cc080.sentRingIndex = 0;
    }
    data_020cc080.reservedHead = 0;
    data_020cc080.reservedTail = 0;
    data_020cc080.sentBlockCount++;
    data_020cc080.nextTag++;
    OS_RestoreInterrupts(state);

    if ((flags & 2) != 0) {
        RequestCommandProc();
    }
    return 1;
}
