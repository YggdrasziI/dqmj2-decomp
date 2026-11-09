/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

NNSG2dCellTransferState * GlobalArrayEntryPtr30(u32 handle);

extern NNSG2dCellTransferState * GlobalArrayEntryPtr30 (u32 handle);

void NNS_G2dSetCellTransferStateRequested (u32 handle, u32 srcOffset, u32 szByte)
{

    {
        NNSG2dCellTransferState * pState = GlobalArrayEntryPtr30(handle);

        pState->bTransferRequested = 0xFFFFFFFF;
        pState->srcOffset = srcOffset;
        pState->szByte = szByte;
    }
}
