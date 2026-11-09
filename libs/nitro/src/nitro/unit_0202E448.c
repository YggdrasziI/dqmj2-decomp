/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct H {
    char _0[0x17];
    unsigned char x17;
    unsigned char x18;
};

int NTRi_GetRegionTableSize(const unsigned char *region, struct H *hdr)
{
    int v;
    if (region == 0 || hdr == 0) return 0;
    switch (*region) {
    case 'M':
        v = hdr->x18 << 1;
        return (v + 0x1c) & ~3;
    case 'J':
    case 'V':
        v = hdr->x17 << 1;
        return (v + 0x1c) & ~3;
    }
    return 0;
}
