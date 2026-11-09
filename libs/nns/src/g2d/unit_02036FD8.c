/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct { signed char dx, dy; } TextDir;

extern int  NNSi_G2dFontGetStringWidth(int font, int opts, int s, int *outNext);

extern void Text_DrawLine(int *ctx, int x, int y, int p5, int s, int *pNext, TextDir dir);

void Text_DrawAlignedLines(int *ctx, int x, int y, int width, int p5,
                   unsigned int flags, int str, TextDir dir)
{
    int step = ctx[3] + *(signed char *)(*(int *)ctx[1] + 1);
    int stepx = step * -dir.dy;
    int stepy = step * dir.dx;
    int px, py;
    int ox, oy;
    int s = str;

    if (str != 0) {
        ox = 0;
        oy = 0;
        do {
            px = x + ox;
            py = y + oy;
            if (flags & 0x800) {
                int w = NNSi_G2dFontGetStringWidth(ctx[1], ctx[2], s, 0);
                w = width - w;
                px += w * dir.dx;
                py += w * dir.dy;
            } else if (flags & 0x400) {
                int w = NNSi_G2dFontGetStringWidth(ctx[1], ctx[2], s, 0);
                w = (width + 1) / 2 - (w + 1) / 2;
                px += w * dir.dx;
                py += w * dir.dy;
            }
            Text_DrawLine(ctx, px, py, p5, s, &s, dir);
            ox += stepx;
            oy += stepy;
        } while (s != 0);
    }
}
