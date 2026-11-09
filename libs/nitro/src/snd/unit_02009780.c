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

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern SNDCommandMgr data_020cc080;

void SND_PushCommand(SNDCommand *command) {
    SNDCommand *tail;
    int state;

    state = OS_DisableInterrupts();
    tail = data_020cc080.reservedTail;
    
    if (tail == 0) {
        data_020cc080.reservedHead = command;
        data_020cc080.reservedTail = command;
    } else {
        tail->next = command;
        data_020cc080.reservedTail = command;
    }
    command->next = 0;
    OS_RestoreInterrupts(state);
}
