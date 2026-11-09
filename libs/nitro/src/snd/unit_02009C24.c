/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern unsigned char data_020cdb60;

void SND_AlarmInit(void) {
    int i;
    char *p = (char *)&data_020cdb60;

    for (i = 0; i < 8; i++) {
        *(int *)p = 0;
        *(int *)(p + 4) = 0;
        *(unsigned char *)(p + 8) = 0;
        p += 0xc;
    }
}
