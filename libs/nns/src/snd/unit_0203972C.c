/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

const NNSSndSeqArcSeqInfo * NNSi_SndSeqArcGetSeqInfo(const struct NNSSndSeqArc * seqArc, int seqNo);

const NNSSndArcSeqArcInfo * NNS_SndArcGetSeqArcInfo(int seqNo);

void * NNS_SndArcGetFileAddress(u32 fileId);

extern BOOL StartSeqArc(NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndSeqArcSeqInfo * sound, const NNSSndSeqArc * seqArc, int seqArcNo, int index);

extern BOOL StartSeqArc (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndSeqArcSeqInfo * sound, const NNSSndSeqArc * seqArc, int seqArcNo, int index);

BOOL NNS_SndArcPlayerStartSeqArc (NNSSndHandle * handle, int seqArcNo, int index)
{
    const NNSSndArcSeqArcInfo * info;
    const NNSSndSeqArcSeqInfo * sound;
    const NNSSndSeqArc * seqArc;

    info = NNS_SndArcGetSeqArcInfo(seqArcNo);
    if (info == NULL) return FALSE;
    seqArc = (NNSSndSeqArc *)NNS_SndArcGetFileAddress(info->fileId);
    if (seqArc == NULL) return FALSE;
    sound = NNSi_SndSeqArcGetSeqInfo(seqArc, index);
    if (sound == NULL) return FALSE;

    return StartSeqArc(
        handle,
        sound->param.playerNo,
        sound->param.bankNo,
        sound->param.playerPrio,
        sound,
        seqArc,
        seqArcNo,
        index
        );
}
