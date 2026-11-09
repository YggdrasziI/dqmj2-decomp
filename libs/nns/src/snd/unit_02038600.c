/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

const NNSSndSeqArcSeqInfo * NNSi_SndSeqArcGetSeqInfo (const NNSSndSeqArc * seqArc, int index)
{

    if (index < 0) return NULL;
    if (index >= seqArc->count) return NULL;
    if (seqArc->info[ index ].offset == NNS_SND_SEQ_ARC_INVALID_OFFSET) return NULL;

    return &seqArc->info[ index ];
}
