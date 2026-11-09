/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

void SND_DestroyWaveArc(struct SNDWaveArc * waveArc);

extern void DisposeCallback(void * mem, NNSSndArc * arc, u32 fileId);

extern void DisposeCallback (void * mem, NNSSndArc * arc, u32 fileId);

void SND_InvalidateWaveData(const void *start, const void *end);

void SND_SetWaveDataAddress(struct SNDWaveArc * waveArc, int index, const SNDWaveData * address);

const SNDWaveData * SND_GetWaveDataAddress(const struct SNDWaveArc * waveArc, int index);

void WaveArcTableDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDWaveArc * waveArc = (SNDWaveArc *)mem;
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    (void)size;

    DisposeCallback(mem, arc, fileId);
    SND_DestroyWaveArc(waveArc);
}

void SingleWaveDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDWaveArc * waveArc = (SNDWaveArc *)data1;
    u32 waveNo = data2;

    if (mem == SND_GetWaveDataAddress(waveArc, (int)waveNo)) {
        SND_SetWaveDataAddress(waveArc, (int)waveNo, NULL);
    }

    SND_InvalidateWaveData(mem, (u8 *)mem + size);
}
