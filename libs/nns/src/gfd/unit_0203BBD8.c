/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/gfd.h"

extern NNSGfdFrmTexRegionState data_020c6920[5 ];

void NNS_GfdGetFrmTexVramState (NNSGfdFrmTexVramState * pState)
{
    int i;

    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++)
    {
        pState->address[i * 2 + 0] = data_020c6920[i].head;
        pState->address[i * 2 + 1] = data_020c6920[i].tail;
    }
}
