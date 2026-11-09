/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *NNS_G2dFindBinaryBlock();

extern void Res_RelocateField14();

int GetResourceSubBlock_CHAR(int this_, int *arg1) {
    void *r = NNS_G2dFindBinaryBlock(this_, 0x43484152);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    Res_RelocateField14((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
