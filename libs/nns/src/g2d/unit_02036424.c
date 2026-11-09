/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

u16 GetGlyphIndex (const NNSG2dFontCodeMap * pMap, u16 c)
{
    u16 index = NNS_G2D_GLYPH_INDEX_NOT_FOUND;

    switch (pMap->mappingMethod) {
    case NNS_G2D_MAPMETHOD_DIRECT:
    {
        u16 offset = pMap->mapInfo[0];
        index = (u16)(c - pMap->ccodeBegin + offset);
    }
    break;
    case NNS_G2D_MAPMETHOD_TABLE:
    {
        const int table_index = c - pMap->ccodeBegin;

        index = pMap->mapInfo[table_index];
    }
    break;
    case NNS_G2D_MAPMETHOD_SCAN:
    {
        const NNSG2dCMapInfoScan * const ws = (NNSG2dCMapInfoScan *)(pMap->mapInfo);
        const NNSG2dCMapScanEntry * st = &(ws->entries[0]);
        const NNSG2dCMapScanEntry * ed = &(ws->entries[ws->num - 1]);

        while (st <= ed) {
            const NNSG2dCMapScanEntry * md = st + (ed - st) / 2;

            if (md->ccode < c) {
                st = md + 1;
            } else if (c < md->ccode) {
                ed = md - 1;
            } else {
                index = md->index;
                break;
            }
        }
    }
    break;
    default:
    }

    return index;
}
