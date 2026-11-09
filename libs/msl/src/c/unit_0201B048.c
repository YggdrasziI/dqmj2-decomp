/* MSL; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

int Mem_CompareBytes(unsigned char *a, unsigned char *b, int n) {
    while (n != 0) {
        if (*a++ != *b++) {
            return (a[-1] < b[-1]) ? -1 : 1;
        }
        n--;
    }
    return 0;
}
