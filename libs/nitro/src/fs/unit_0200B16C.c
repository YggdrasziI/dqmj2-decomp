/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

unsigned FSi_GetPackedName(const char *name, int len) {
    unsigned packed = 0;
    if (len <= 3) {
        int i = 0;
        if (len > 0) {
            int shift = 0;
            do {
                unsigned c = (unsigned char)name[i];
                if (c == 0) {
                    break;
                }
                {
                    int d = (int)c - 0x41;
                    if ((unsigned)d <= 0x19) {
                        c = (unsigned)(d + 0x61);
                    } else {
                        c = (unsigned)(d + 0x41);
                    }
                }
                i++;
                packed |= c << shift;
                shift += 8;
            } while (i < len);
        }
    }
    return packed;
}
