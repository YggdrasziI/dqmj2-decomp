/* MSL; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#define K1 0x80808080

#define K2 0xfefefeff

typedef struct {
    signed char *pos;
    int eof;
} CharCursor;

int CharCursor_Control(CharCursor *s, int c, int cmd) {
    switch (cmd) {
    case 0: {
        signed char *p = s->pos;
        int ch = *p;
        if (ch == 0) {
            s->eof = 1;
            return -1;
        }
        s->pos = p + 1;
        return ch & 0xff;
    }
    case 1:
        if (s->eof == 0) {
            s->pos = s->pos - 1;
        } else {
            s->eof = 0;
        }
        return c;
    case 2:
        return s->eof;
    default:
        return 0;
    }
}

int strlen(const char *s) {
    int n = -1;
    char c;
    do {
        c = *s++;
        n++;
    } while (c != 0);
    return n;
}

char *strcpy(char *dst, const char *src)
{
    register unsigned char *destb, *fromb;
    register unsigned long w, t, align;

    fromb = (unsigned char *)src;
    destb = (unsigned char *)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0)
            return dst;
        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0)
                return dst;
        }
        ++destb;
        ++fromb;
    }

    w = *((int *)(fromb));

    t = w + K2;

    t &= ~w;
    t &= K1;
    if (t)
        goto bytecopy;
    --((int *)(destb));

    do {
        *(++((int *)(destb))) = w;
        w = *(++((int *)(fromb)));

        t = w + K2;
        t &= ~w;
        t &= K1;
        if (t)
            goto adjust;
    } while (1);

adjust:
    ++((int *)(destb));
bytecopy:
    if ((*destb = *fromb) == 0)
        return dst;

    do {
        if ((*(++destb) = *(++fromb)) == 0)
            return dst;
    } while (1);

    return dst;
}

char *strncpy(char *dst, const char *src, unsigned n) {
    char *d = dst;
    char *p;
    if (n == 0) {
        return dst;
    }
    do {
        p = d;
        *d++ = *src++;
        if (*p == 0) {
            while (--n != 0) {
                *d++ = 0;
            }
            return dst;
        }
    } while (--n != 0);
    return dst;
}

char *STD_StrCat(char *dst, const char *src) {
    char *p = dst;
    while (*p++ != 0) {
        ;
    }
    p--;
    while ((*p++ = *src++) != 0) {
        ;
    }
    return dst;
}

int strcmp(const char *str1, const char *str2)
{
    register unsigned char *left = (unsigned char *)str1;
    register unsigned char *right = (unsigned char *)str2;
    unsigned long align, l1, r1, x;

    l1 = *left;
    r1 = *right;
    if (l1 - r1)
        return l1 - r1;

    if ((align = ((int)left & 3)) != ((int)right & 3))
        goto bytecopy;

    if (align) {
        if (l1 == 0)
            return 0;
        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            if (l1 - r1)
                return l1 - r1;
            if (l1 == 0)
                return 0;
        }
        left++;
        right++;
    }

    l1 = *(int *)left;
    r1 = *(int *)right;
    x = l1 + K2;
    if (x & ~l1 & K1)
        goto adjust;

    while (l1 == r1) {
        l1 = *(++((int *)left));
        r1 = *(++((int *)right));
        x = l1 + K2;
        if (x & K1)
            goto adjust;
    }

    --left;
    --right;
    goto bytecopy;

adjust:
    l1 = *left;
    r1 = *right;
    if (l1 - r1)
        return l1 - r1;

bytecopy:
    if (l1 == 0)
        return 0;

    do {
        l1 = *(++left);
        r1 = *(++right);
        if (l1 - r1)
            return l1 - r1;
    } while (l1 != 0);

    return 0;
}

int strncmp(const unsigned char *s1, const unsigned char *s2, unsigned int n) {
    if (n != 0) {
        do {
            unsigned char b = *s2++;
            unsigned char a = *s1++;
            if (a != b) return (int)a - (int)b;
            if (a == 0) break;
        } while (--n != 0);
    }
    return 0;
}
