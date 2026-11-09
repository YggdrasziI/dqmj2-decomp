/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

int NNSi_G2dFontGetStringWidth(const NNSG2dFont * pFont, int hSpace, const void * str, const void ** pPos);

extern int NNSi_G2dFontGetStringWidth (const NNSG2dFont * pFont, int hSpace, const void * str, const void ** pPos);

inline s8 NNS_G2dFontGetLineFeed (const NNSG2dFont * pFont)
{
    return pFont->pRes->linefeed;
}

NNSG2dTextRect NNSi_G2dFontGetTextRect (const NNSG2dFont * pFont, int hSpace, int vSpace, const void * txt)
{
    int lines = 1;
    NNSG2dTextRect rect = {0, 0};

    while (txt != NULL) {
        const int width = NNSi_G2dFontGetStringWidth(pFont, hSpace, txt, &txt);
        if (width > rect.width) {
            rect.width = width;
        }
        lines++;
    }

    rect.height = ((lines - 1) * (NNS_G2dFontGetLineFeed(pFont) + vSpace) - vSpace);

    return rect;
}
