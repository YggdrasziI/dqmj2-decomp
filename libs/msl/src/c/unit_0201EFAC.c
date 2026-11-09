/* MSL; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    char *NextChar;
    int NullCharDetected;
} __InStrCtrl;

extern unsigned long __strtoul(int base, int max, int (*ReadProc)(void *, int, int),
                                   void *ReadProcArg, int *chars_scanned, int *negative,
                                   int *overflow);

extern int CharCursor_Control(void *isc, int ch, int action);

extern int data_020d52b0;

long strtol(const char *str, char **end, int base)
{
    unsigned long value;
    int count, negative, overflow;
    __InStrCtrl isc;

    isc.NextChar = (char *)str;
    isc.NullCharDetected = 0;

    value = __strtoul(base, 0x7fffffff, CharCursor_Control, (void *)&isc, &count, &negative, &overflow);

    if (end)
        *end = (char *)str + count;

    if (overflow || (!negative && value > 0x7fffffff) || (negative && value > 0x80000000)) {
        value = (negative ? 0x80000000 : 0x7fffffff);
        data_020d52b0 = 0x22;
    } else if (negative)
        value = -value;

    return (long)value;
}
