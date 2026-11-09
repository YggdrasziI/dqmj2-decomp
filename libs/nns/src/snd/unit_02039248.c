/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void * NNSi_SndArcLoadFile(u32 fileId, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2, NNSSndHeapHandle heap);

NNSSndArc * func_02038984(void);

void * NNS_SndArcGetFileAddress(u32 fileId);

void NNS_SndArcSetFileAddress(u32 fileId, void * address);

extern s32 func_02038ca0(u32 fileId, void *buffer, s32 size, s32 offset);

extern void *NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

extern void WaveArcTableDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);

extern void MI_CpuCopy8(const void *src, void *dest, u32 size);

extern void MI_CpuFill8(void *dest, u8 data, u32 size);

extern void DC_StoreRange(const void *startAddr, u32 nBytes);


SNDWaveArc * NNS_SndArcLoadWaveArcTable (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr)
{
    u32 fileSize;
    SNDWaveArc * waveArc;
    u32 waveCount;
    u32 tableSize;
    s32 result;
    /* The file header, read before the table is allocated: a function static (two
     * pool words for one address, as in the ROM); it owns .bss 0x020DDAC8-0x020DDB04. */
    static SNDWaveArc data_020ddac8;

    waveArc = (SNDWaveArc *)NNS_SndArcGetFileAddress(fileId);
    if (waveArc == NULL) {
        if (func_02038ca0(fileId, &data_020ddac8, 0x3c, 0) != 0x3c) {
            return NULL;
        }
        waveCount = data_020ddac8.waveCount;
        tableSize = waveCount * sizeof(u32);
        fileSize = tableSize * 2;
        if (heap == NULL) {
            return NULL;
        }
        waveArc = (SNDWaveArc *)NNS_SndHeapAlloc(heap, fileSize + 0x5c, WaveArcTableDisposeCallback,
                                              bSetAddr ? (u32)func_02038984() : 0, fileId);
        if (waveArc == NULL) {
            return NULL;
        }
        result = func_02038ca0(fileId, waveArc, (s32)(tableSize + 0x3c), 0);
        if (result != tableSize + 0x3c) {
            return NULL;
        }
        MI_CpuCopy8(waveArc->waveOffset, &waveArc->waveOffset[waveArc->waveCount], tableSize);
        MI_CpuFill8(waveArc->waveOffset, 0, tableSize);
        DC_StoreRange(waveArc, fileSize + 0x3c);
        if (bSetAddr) {
            NNS_SndArcSetFileAddress(fileId, waveArc);
        }
    }
    return waveArc;
}
