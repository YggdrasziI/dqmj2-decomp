/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#include "nitro/os.h"

#define SND_COMMAND_BLOCK (1 << 0)

#define SND_COMMAND_NOBLOCK 0

typedef struct {
    char unk0;
    char pad1[3];
    int unk4;
    int pad8;
    int unkC;
    void (*unk10)(void);
    int unk14;
    int pad18;
    void (*unk1C)(void);
    int unk20;
} S_0204a2d4;

void NNS_FndInitList(NNSFndList * list, u16 offset);

extern BOOL NewSection(NNSSndHeap * heap);

extern BOOL NewSection (NNSSndHeap * heap);

void NNS_FndAppendListObject(NNSFndList * list, void * object);

void * NNS_FndAllocFromFrmHeapEx(NNSFndHeapHandle heap, u32 size, int alignment);

extern void func_02037934(NNSSndHeapSection * section);

extern void func_02037934 (NNSSndHeapSection * section);

BOOL SND_FlushCommand(u32 flags);

void SND_WaitForCommandProc(u32 tag);

u32 SND_GetCurrentCommandTag(void);

extern void SND_Init(void);

extern void func_0200f218(void *p);

extern void func_0200f230(void *p);

extern void SndCapture_Reset(void);

extern void func_02037344(void);

extern void NNSi_SndPlayerInit(void);

extern void BeginSleep(void);

extern void func_02037bf0(void);

extern void *data_020dadf0;

extern void *data_020dadfc;

extern S_0204a2d4 data_020dade0;

const SNDCommand * SND_RecvCommandReply(u32 flags);

void func_0203735c(void);

void NNSi_SndPlayerMain(void);

void NNSi_SndArcStrmMain(void);

BOOL InitHeap (NNSSndHeap * heap, NNSFndHeapHandle handle)
{
    NNS_FND_INIT_LIST(&heap->sectionList, NNSSndHeapSection, link);
    heap->handle = handle;

    if (!NewSection(heap)) {
        return FALSE;
    }

    return TRUE;
}

BOOL NewSection (NNSSndHeap * heap)
{
    NNSSndHeapSection * section;

    section = (NNSSndHeapSection *)NNS_FndAllocFromFrmHeap(heap->handle, sizeof(NNSSndHeapSection));
    if (section == NULL) {
        return FALSE;
    }
    func_02037934(section);

    NNS_FndAppendListObject(&heap->sectionList, section);

    return TRUE;
}

void EraseSync (void)
{
    u32 commandTag;

    commandTag = SND_GetCurrentCommandTag();
    (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}

void NNS_SndInit(void)
{
    if (data_020dade0.unkC != 0) {
        return;
    }
    data_020dade0.unkC = 1;
    SND_Init();
    data_020dade0.unk10 = BeginSleep;
    data_020dade0.unk14 = 0;
    data_020dade0.unk1C = func_02037bf0;
    data_020dade0.unk20 = 0;
    func_0200f218(&data_020dadf0);
    func_0200f230(&data_020dadfc);
    SndCapture_Reset();
    func_02037344();
    NNSi_SndPlayerInit();
    data_020dade0.unk0 = -1;
    data_020dade0.unk4 = 1;
}

void NNS_SndMain (void)
{
    while (SND_RecvCommandReply(SND_COMMAND_NOBLOCK) != NULL) {
    }

    NNSi_SndPlayerMain();
    func_0203735c();
#ifndef SDK_SMALL_BUILD
    NNSi_SndArcStrmMain();
#endif

    (void)SND_FlushCommand(SND_COMMAND_NOBLOCK);
}
