/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void NNS_G2dUnpackNCL(NNSG2dPaletteData * pPlttData);

NNSG2dBinaryBlockHeader * NNS_G2dFindBinaryBlock(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);

extern void NNS_G2dUnpackNCL (NNSG2dPaletteData * pPlttData);

BOOL NNS_G2dGetUnpackedPaletteData (void * pNclrFile, NNSG2dPaletteData ** ppPltData)
{

    {
        const NNSG2dBinaryFileHeader * pBinFile = pNclrFile;

    }

    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNclrFile;
        {
            NNSG2dPaletteDataBlock * pBinBlk =
                (NNSG2dPaletteDataBlock *)NNS_G2dFindBinaryBlock(pBinFile,
                                                                 NNS_G2D_BINBLK_SIG_PALETTEDATA);
            if (pBinBlk) {
                NNS_G2dUnpackNCL((void *)&pBinBlk->paletteData);
                *ppPltData = &pBinBlk->paletteData;
                return TRUE;
            } else {
                *ppPltData = NULL;
                return FALSE;

            }
        }
    }
}
