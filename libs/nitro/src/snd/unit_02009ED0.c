/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define SND_COMMAND_NOBLOCK 0

#define SND_COMMAND_BLOCK 1

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

#define SND_BANK_TO_WAVEARC_MAX 4

typedef struct SNDCommand {
    struct SNDCommand *next;      
    u32 id;                       
    u32 arg[4];                   
} SNDCommand;

enum {
    SND_COMMAND_START_SEQ = 0,
    SND_COMMAND_STOP_SEQ = 1,
    SND_COMMAND_PREPARE_SEQ = 2,
    SND_COMMAND_START_PREPARED_SEQ = 3,
    SND_COMMAND_PAUSE_SEQ = 4,
    SND_COMMAND_CHANNEL_PAN = 0x15,
    SND_COMMAND_LOCK_CHANNEL = 0x1a,
    SND_COMMAND_UNLOCK_CHANNEL = 0x1b
};

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;      
    u32 reserved[7];
    u32 waveCount;                
    u32 waveOffset[0];            
} SNDWaveArc;

typedef struct SNDWaveData SNDWaveData;

typedef struct SNDBankData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];   
    u32 instCount;                
    u32 instOffset[0];            
} SNDBankData;

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern void func_020094ec(void);

extern void func_02009500(void);

extern void DC_StoreRange(void *addr, u32 size);

void SND_AssignWaveArc(SNDBankData *bank, int index, SNDWaveArc *waveArc)
{
    SNDWaveArcLink *next;
    SNDWaveArcLink *prev;

    func_020094ec();

    if (bank->waveArcLink[index].waveArc != NULL) {
        if (waveArc == bank->waveArcLink[index].waveArc) {
            func_02009500();
            return;
        }

        if (&bank->waveArcLink[index] == bank->waveArcLink[index].waveArc->topLink) {
            bank->waveArcLink[index].waveArc->topLink = bank->waveArcLink[index].next;

            DC_StoreRange(bank->waveArcLink[index].waveArc, sizeof(SNDWaveArc));
        } else {
            prev = bank->waveArcLink[index].waveArc->topLink;
            while (prev != NULL) {
                if (&bank->waveArcLink[index] == prev->next)
                    break;
                prev = prev->next;
            }
            prev->next = bank->waveArcLink[index].next;

            DC_StoreRange(prev, sizeof(SNDWaveArcLink));
        }
    }

    next = waveArc->topLink;
    waveArc->topLink = &bank->waveArcLink[index];
    bank->waveArcLink[index].next = next;
    bank->waveArcLink[index].waveArc = waveArc;

    func_02009500();

    DC_StoreRange(bank, sizeof(SNDBankData));
    DC_StoreRange(waveArc, sizeof(SNDWaveArc));
}
