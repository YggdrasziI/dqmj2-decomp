/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

inline u16 NNS_G2dGetNumAnimSequence (const NNSG2dAnimBankData * pAnimBank)
{
    return pAnimBank->numSequences;
}

const NNSG2dAnimSequenceData * NNS_G2dGetAnimSequenceByIdx (const NNSG2dAnimBankData * pAnimBank, u16 idx)
{

    if (NNS_G2dGetNumAnimSequence(pAnimBank) > idx) {
        return &pAnimBank->pSequenceArrayHead[idx];
    } else {
        return NULL;
    }
}
