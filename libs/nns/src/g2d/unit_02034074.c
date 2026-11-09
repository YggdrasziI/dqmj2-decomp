/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void NNS_G2dUnpackNAN(NNSG2dAnimBankData * pData);

NNSG2dBinaryBlockHeader * NNS_G2dFindBinaryBlock(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);

extern void NNS_G2dUnpackNAN (NNSG2dAnimBankData * pData);

NNSG2dBinaryBlockHeader * NNS_G2dFindBinaryBlock (NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature)
{

    {
        NNSG2dBinaryBlockHeader * pCursor = (NNSG2dBinaryBlockHeader *)((u32)pBinFileHeader + (u32)pBinFileHeader->headerSize);

        u16 count = 0;
        while (count < pBinFileHeader->dataBlocks) {

            if (pCursor->kind == signature) {
                return pCursor;
            }
            pCursor = (NNSG2dBinaryBlockHeader *)((u32)pCursor + pCursor->size);
            count++;
        }
    }

    return NULL;
}

void NNSi_G2dUnpackUserExCellAttrBank (NNSG2dUserExCellAttrBank * pCellAttrBank)
{
    u16 i;

    pCellAttrBank->pCellAttrArray
        = NNS_G2D_UNPACK_OFFSET_PTR(pCellAttrBank->pCellAttrArray,
                                    pCellAttrBank);
    for (i = 0; i < pCellAttrBank->numCells; i++) {
        pCellAttrBank->pCellAttrArray[i].pAttr
            = NNS_G2D_UNPACK_OFFSET_PTR(pCellAttrBank->pCellAttrArray[i].pAttr,
                                        pCellAttrBank);
    }
}

BOOL GetUnpackedAnimBankImpl_ (void * pNanrFile, NNSG2dAnimBankData ** ppAnimBank)
{
    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNanrFile;
        {
            NNSG2dAnimBankDataBlock * pAnimBankBlk =
                (NNSG2dAnimBankDataBlock *)NNS_G2dFindBinaryBlock(pBinFile,
                                                                  NNS_G2D_BLKSIG_ANIMBANK);
            if (pAnimBankBlk) {
                NNS_G2dUnpackNAN((void *)&pAnimBankBlk->animBankData);
                *ppAnimBank = &pAnimBankBlk->animBankData;
                return TRUE;
            }
        }
    }

    *ppAnimBank = NULL;
    return FALSE;
}
