/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/gfd.h"

extern NNSGfdFrmTexVramMnager data_020dea5c;

extern NNSGfdFrmTexRegionState data_020c6920[5 ];

static inline void ResetRegionNormal_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 ;
}

static inline void ResetRegionHalf_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 / 2;
}

void NNS_GfdResetFrmTexVramState (void)
{
    int i;
    u16 numSlot = data_020dea5c.numSlot;

    const numRegion = (numSlot > 1) ? numSlot + 1 : numSlot + 0;

    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++) {
        if ( i < numRegion ) {
            data_020c6920[i].bActive = TRUE;
        } else {
            data_020c6920[i].bActive = FALSE;
        }

        if ( data_020c6920[i].bHalfSize ) {
            ResetRegionHalf_(&data_020c6920[i]);
        } else {
            ResetRegionNormal_(&data_020c6920[i]);
        }
    }
}
