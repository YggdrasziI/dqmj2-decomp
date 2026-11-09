/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

extern const void * GetPtrConst(const void * base, u32 offset);

extern const NNSSndArcOffsetTable * GetOffsetTable(const NNSSndArcInfo * info, u32 offset);

extern NNSSndArc * data_020ddac4;

static inline
const void * GetPtrConst (const void * base, u32 offset)
{
    if (offset == 0) return NULL ;
    return (const u8 *)base + offset;
}

static inline
const NNSSndArcOffsetTable * GetOffsetTable (const NNSSndArcInfo * info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}

const NNSSndArcSeqInfo * NNS_SndArcGetSeqInfo (int seqNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->seqOffset);
    if (table == NULL) return NULL;

    if (seqNo < 0) return NULL;
    if (seqNo >= table->count) return NULL;

    return (const NNSSndArcSeqInfo *)GetPtrConst(arc->info, table->offset[ seqNo ]);
}

const NNSSndArcSeqArcInfo * NNS_SndArcGetSeqArcInfo (int seqArcNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->seqArcOffset);
    if (table == NULL) return NULL;

    if (seqArcNo < 0) return NULL;
    if (seqArcNo >= table->count) return NULL;

    return (const NNSSndArcSeqArcInfo *)GetPtrConst(arc->info, table->offset[ seqArcNo ]);
}

const NNSSndArcBankInfo * NNS_SndArcGetBankInfo (int bankNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->bankOffset);
    if (table == NULL) return NULL;

    if (bankNo < 0) return NULL;
    if (bankNo >= table->count) return NULL;

    return (const NNSSndArcBankInfo *)GetPtrConst(arc->info, table->offset[ bankNo ]);
}

const NNSSndArcWaveArcInfo * NNS_SndArcGetWaveArcInfo (int waveArcNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->waveArcOffset);
    if (table == NULL) return NULL;

    if (waveArcNo < 0) return NULL;
    if (waveArcNo >= table->count) return NULL;

    return (const NNSSndArcWaveArcInfo *)GetPtrConst(arc->info, table->offset[ waveArcNo ]);
}

const NNSSndArcStrmInfo * NNS_SndArcGetStrmInfo (int strmNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->strmOffset);
    if (table == NULL) return NULL;

    if (strmNo < 0) return NULL;
    if (strmNo >= table->count) return NULL;

    return (const NNSSndArcStrmInfo *)GetPtrConst(arc->info, table->offset[ strmNo ]);
}

const NNSSndArcPlayerInfo * NNS_SndArcGetPlayerInfo (int playerNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->playerInfoOffset);
    if (table == NULL) return NULL;

    if (playerNo < 0) return NULL;
    if (playerNo >= table->count) return NULL;

    return (const NNSSndArcPlayerInfo *)GetPtrConst(arc->info, table->offset[ playerNo ]);
}

const NNSSndArcStrmPlayerInfo * NNS_SndArcGetStrmPlayerInfo (int playerNo)
{
    NNSSndArc * arc = data_020ddac4;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->strmPlayerInfoOffset);
    if (table == NULL) return NULL;

    if (playerNo < 0) return NULL;
    if (playerNo >= table->count) return NULL;

    return (const NNSSndArcStrmPlayerInfo *)GetPtrConst(arc->info, table->offset[ playerNo ]);
}

u32 NNS_SndArcGetFileOffset (u32 fileId)
{
    NNSSndArc * arc = data_020ddac4;

    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[ fileId ].offset;
}

u32 NNS_SndArcGetFileSize (u32 fileId)
{
    NNSSndArc * arc = data_020ddac4;

    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[ fileId ].size;
}
