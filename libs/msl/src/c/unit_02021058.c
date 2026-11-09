/* MSL; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

int Wcslen(unsigned short *arg0) {
    int n = -1;
    unsigned short c;
    do {
        c = *arg0++;
        n++;
    } while (c != 0);
    return n;
}

unsigned short *StrCopy16(unsigned short *dst, unsigned short *src) {
    unsigned short *p = dst, *q;
    unsigned short v;
    do {
        q = p++;
        *q = *src++;
        v = *(volatile unsigned short *)q;
    } while (v != 0);
    return dst;
}

unsigned short *STD_WStrCat(unsigned short *dst, const unsigned short *src) {
    unsigned short *p = dst;
    while (*p++ != 0) {
        ;
    }
    p--;
    while ((*p++ = *src++) != 0) {
        ;
    }
    return dst;
}
