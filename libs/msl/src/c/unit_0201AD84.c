/* MSL; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern const unsigned char data_020c1b34[];

static inline int FoldCase(int c)
{
    if (c < 0 || c >= 0x80) {
        return c;
    }
    return data_020c1b34[c];
}

int abs(int x){ if (x < 0) x = -x; return x; }

int StrNCaseCmp(const signed char *a, const signed char *b, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        signed char ca = FoldCase(*a++);
        signed char cb = FoldCase(*b++);

        if (ca < cb) {
            return -1;
        }
        if (ca > cb) {
            return 1;
        }
        if (ca == 0) {
            return 0;
        }
    }
    return 0;
}
