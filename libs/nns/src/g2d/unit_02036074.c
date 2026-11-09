/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void NNS_G2dMapScrToChar256x16Pltt (void * areaBase, int areaWidth, int areaHeight, NNSG2d256x16PlttBGWidth scnWidth, int charNo, int cplt)
{
    u16 * pScrBase;
    int x, y;
    const u16 cplt_sft = (u16)(cplt << 12);

    pScrBase = areaBase;

    for (y = 0; y < areaHeight; ++y) {
        u16 * pScr = pScrBase;
        for (x = 0; x < areaWidth; ++x) {
            *pScr++ = (u16)(cplt_sft | charNo++);
        }
        pScrBase += scnWidth;
    }
}
