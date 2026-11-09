/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define MATH_ROUNDUP(x, base) (((x) + ((base) - 1)) & ~((base) - 1))

#define MATH_ROUNDDOWN(x, base) ((x) & ~((base) - 1))

#define CHARACTER_WIDTH 8

#define CHARACTER_HEIGHT 8

extern void ClearChar (void * pChar, int x, int y, int w, int h, u32 cl8, int bpp);

static inline int GetCharacterSize (const NNSG2dCharCanvas * pCC)
{
    return 8 * 8 * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32 (const NNSG2dCharCanvas * pCC, int cl)
{
    u32 val = (u32)cl;
    if ( pCC->dstBpp == 4 ) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }
    return val;
}

void ClearAreaLine (const NNSG2dCharCanvas * pCC, int cl, int x, int y, int w, int h)
{
    int ix, iy;
    int cx, cy, cw, ch;
    const int xw = x + w;
    const int yh = y + h;
    u32 cl8;

    cl8 = SpreadColor32(pCC, cl);

    {
        const int left = MATH_ROUNDDOWN(x, CHARACTER_WIDTH);
        const int top = MATH_ROUNDDOWN(y, CHARACTER_HEIGHT);
        const int right = MATH_ROUNDUP(xw, CHARACTER_WIDTH);
        const int bottom = MATH_ROUNDUP(yh, CHARACTER_HEIGHT);

        const int charSize = GetCharacterSize(pCC);
        const int charBaseLineOffset = (int)(pCC->param * charSize);
        const int bpp = pCC->dstBpp;
        u8 * pCharBase;
        u8 * pChar;

        pCharBase = pCC->charBase + ((top / CHARACTER_HEIGHT) * pCC->param + (left / CHARACTER_WIDTH)) * charSize;

        for (iy = top; iy < bottom; iy += CHARACTER_HEIGHT) {
            cy = (iy < y) ? y - iy: 0;
            ch = ((yh - iy > CHARACTER_HEIGHT) ? CHARACTER_HEIGHT: yh - iy) - cy;
            pChar = pCharBase;

            for (ix = left; ix < right; ix += CHARACTER_WIDTH) {
                cx = (ix < x) ? x - ix: 0;
                cw = ((xw - ix > CHARACTER_WIDTH) ? CHARACTER_WIDTH: xw - ix) - cx;

                ClearChar(pChar, cx, cy, cw, ch, cl8, bpp);
                pChar += charSize;
            }

            pCharBase += charBaseLineOffset;
        }
    }
}
