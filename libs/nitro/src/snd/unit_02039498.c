/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef struct SNDBinaryFileHeader {
    u32 signature;
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

typedef struct NNSSndHeap *NNSSndHeapHandle;

typedef void (*NNSSndHeapDisposeCallback)(void *mem, u32 size, u32 data1, u32 data2);

extern struct SNDWaveArc;

extern const SNDWaveData *SND_GetWaveDataAddress(const SNDWaveArc *waveArc, s32 wave);

extern u32 func_0200a24c(const SNDWaveArc *waveArc);

extern void SND_SetWaveDataAddress(SNDWaveArc *waveArc, s32 wave, const SNDWaveData *address);

extern void DC_StoreRange(void *address, u32 size);

extern void *NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

extern s32 func_02038ca0(u32 fileId, void *buffer, s32 size, s32 offset);

extern void SingleWaveDisposeCallback(void *mem, u32 size, u32 data1, u32 data2);

BOOL SndLoadWaveData(SNDWaveArc *waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap)
{
    SNDWaveData *buffer;
    u32 len;
    u32 begin;
    u32 end;
    u32 waveCount;

    if (SND_GetWaveDataAddress(waveArc, waveNo) != 0) {
        return 1;
    }

    waveCount = func_0200a24c(waveArc);

    {
        const SNDWaveArc *entry = (const SNDWaveArc *)((const char *)waveArc +
            (waveArc->waveCount + waveNo) * sizeof(u32));

        begin = entry->waveOffset[0];
        if (waveNo < waveCount - 1) {
            end = entry->waveOffset[1];
        } else {
            end = waveArc->fileHeader.fileSize;
        }
        len = end - begin;

        if (heap == 0) {
            return 0;
        }

        buffer = (SNDWaveData *)NNS_SndHeapAlloc(
            heap,
            len + 32,
            SingleWaveDisposeCallback,
            (u32)waveArc,
            (u32)waveNo
        );
        if (buffer == 0) {
            return 0;
        }

        if (func_02038ca0(fileId, buffer, (s32)len, (s32)begin) != len) {
            return 0;
        }

        DC_StoreRange(buffer, len);
        SND_SetWaveDataAddress(waveArc, waveNo, buffer);

        return 1;
    }
}
