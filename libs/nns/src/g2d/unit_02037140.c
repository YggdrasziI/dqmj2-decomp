/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nnsys/g2d.h"

typedef struct { signed char dx, dy; } AxisOffset;

typedef struct { int w, h; } TextDimsAlias;

extern NNSG2dTextRect NNSi_G2dFontGetTextRect(const NNSG2dFont *pFont, int hSpace, int vSpace,
                                              const void *txt);

extern void Text_DrawAlignedLines(int *ctx, int x, int y, int w, int mode, int flags, int p6, AxisOffset off);

void Text_AlignAnchor(int *ctx, int x, int y, int mode, int flags, int p6, AxisOffset off)
{
    NNSG2dTextRect work;
    NNSG2dTextRect dims;
    TextDimsAlias hview;
    int t;

    dims = NNSi_G2dFontGetTextRect((const NNSG2dFont *)ctx[1], ctx[2], ctx[3], (const void *)p6);
    hview = *(TextDimsAlias *)&dims;
    work = dims;
    if (flags & 0x10)      { t = -(hview.w + 1) / 2; x = t * off.dx + x; y = t * off.dy + y; }
    else if (flags & 0x20) {                         x = -hview.w * off.dx + x; y = -hview.w * off.dy + y; }
    if (flags & 2)         { t = -(work.height + 1) / 2;  x = t * -off.dy + x; y = t * off.dx + y; }
    else if (flags & 4)    { t = -work.height;            x = t * -off.dy + x; y = t * off.dx + y; }
    Text_DrawAlignedLines(ctx, x, y, work.width, mode, flags, p6, off);
}
