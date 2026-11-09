/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

typedef struct { char *metrics; int bitmap; } GlyphDraw;

extern unsigned short NNS_G2dFontFindGlyphIndex(int *font, unsigned ch);

extern char *NNS_G2dFontGetCharWidthsFromIndex(int *font, unsigned glyph);

extern const NNSiG2dCharCanvasVTable data_020c2120;

extern void InitCharCanvas (NNSG2dCharCanvas * pCC, void * charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode, const NNSiG2dCharCanvasVTable * vtable, u32 param);

void InitCharCanvas (NNSG2dCharCanvas * pCC, void * charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode, const NNSiG2dCharCanvasVTable * vtable, u32 param)
{

    pCC->areaWidth = areaWidth;
    pCC->areaHeight = areaHeight;
    pCC->dstBpp = colorMode;
    pCC->charBase = charBase;
    pCC->vtable = vtable;
    pCC->param = param;
}

int Text_DrawGlyph(int owner, int *font, int x, int y, int p5, unsigned short ch)
{
    GlyphDraw gd;
    unsigned glyph;
    unsigned char *G;

    glyph = NNS_G2dFontFindGlyphIndex(font, ch);
    if (glyph == 0xffff)
        glyph = *(unsigned short *)(*font + 2);
    gd.metrics = NNS_G2dFontGetCharWidthsFromIndex(font, glyph);
    gd.bitmap = glyph * *(unsigned short *)(*(int *)(*font + 8) + 2) + (*(int *)(*font + 8) + 8);
    G = *(unsigned char **)(*font + 8);
    switch (G[7]) {
    case 0:
    case 7:
        x += *(signed char *)gd.metrics;
        break;
    case 1:
    case 2:
        x -= G[0];
        y += *(signed char *)gd.metrics;
        break;
    case 3:
    case 4:
        x -= *(signed char *)gd.metrics + *(unsigned char *)(gd.metrics + 1);
        y -= G[1];
        break;
    case 5:
    case 6:
        y -= *(signed char *)gd.metrics + G[1];
        break;
    }
    (*(int (**)(int, int *, int, int, int, GlyphDraw *))(*(int *)(owner + 0x14)))
        (owner, font, x, y, p5, &gd);
    return *(signed char *)(gd.metrics + 2);
}

void NNS_G2dCharCanvasInitForBG (NNSG2dCharCanvas * pCC, void * charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode)
{

    InitCharCanvas(
        pCC,
        charBase, areaWidth, areaHeight, colorMode,
        &data_020c2120, (unsigned int)areaWidth
        );
}
