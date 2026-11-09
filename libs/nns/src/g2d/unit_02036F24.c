/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct { signed char dx, dy; } TextDir;

extern int Text_DrawGlyph(int a, int *font, int x, int y, int p5, int ch);

void Text_DrawLine(int *ctx, int x, int y, int p5, int s, int *pNext, TextDir dir)
{
    int opts = ctx[2];
    int *font = (int *)ctx[1];
    int c = s;
    int (*getNext)(int *) = (int (*)(int *))font[1];
    int ch = getNext(&c);

    if (ch != 0) {
        do {
            int adv, w;
            if (ch == 10) break;
            adv = Text_DrawGlyph(ctx[0], font, x, y, p5, ch);
            w = opts + adv;
            x += w * dir.dx;
            y += w * dir.dy;
            ch = getNext(&c);
        } while (ch != 0);
    }
    if (pNext != 0)
        *pNext = (ch == 10) ? c : 0;
}
