/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define NNS_FROM_TOOL

extern NNSSndArc * data_020ddac4;

FSFileID NNS_SndArcGetFileID (void)
{
    NNSSndArc * arc = data_020ddac4;

    return arc->fileId;
}

void * NNS_SndArcGetFileAddress (u32 fileId)
{
    NNSSndArc * arc = data_020ddac4;

    if (fileId >= arc->fat->count) return NULL;
    return arc->fat->files[ fileId ].mem;
}

void NNS_SndArcSetFileAddress (u32 fileId, void * address)
{
    NNSSndArc * arc = data_020ddac4;

    arc->fat->files[ fileId ].mem = address;
}

void InfoDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;

    (void)mem;
    (void)size;
    (void)data2;

    arc->info = NULL;
}

void FatDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;
    int i;

    (void)mem;
    (void)size;
    (void)data2;

    for (i = 0; i < arc->fat->count; i++) {
#ifndef NNS_FROM_TOOL
#endif
    }

    arc->fat = NULL;
}

void SymbolDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;

    (void)mem;
    (void)size;
    (void)data2;

    arc->symbol = NULL;
}
