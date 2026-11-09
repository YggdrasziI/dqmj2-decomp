/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void FontResource_Relocate(int base) {
    unsigned int *p = (unsigned int *)(base + *(unsigned short *)(base + 0xc));
    int i = 0;
    if (i < (int)(unsigned int)*(unsigned short *)(base + 0xe)) {
        do {
            switch (*p) {
            case 0x46494e46:  
                p[4] += base;
                if (p[5] != 0) p[5] += base;
                if (p[6] != 0) p[6] += base;
                break;
            case 0x43574448:  
                if (p[3] != 0) p[3] += base;
                break;
            case 0x434d4150:  
                if (p[4] != 0) p[4] += base;
                break;
            case 0x43474c50:  
                break;
            }
            i++;
            p = (unsigned int *)((int)p + p[1]);
        } while (i < (int)(unsigned int)*(unsigned short *)(base + 0xe));
    }
}
