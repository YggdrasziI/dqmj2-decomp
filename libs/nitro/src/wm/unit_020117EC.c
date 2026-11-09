/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int func_020117d0(void);

extern void DC_InvalidateRange(void *addr, unsigned int size);

extern char data_020ce680[];

int func_020117ec(void) {
    int r = func_020117d0();
    if (r == 0) {
        DC_InvalidateRange(*(void **)(*(int *)(data_020ce680 + 4) + 4), 2);
        if (**(unsigned short **)(*(int *)(data_020ce680 + 4) + 4) <= 1) {
            r = 3;
        } else {
            r = 0;
        }
        return r;
    }
    return r;
}
