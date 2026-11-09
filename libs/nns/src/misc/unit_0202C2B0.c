/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void func_0202e018();

void UploadNodeMatricesByFlags(unsigned int *param_1)
{
    unsigned int f = *param_1;
    if ((f & 4) == 0) {
        if ((f & 2) == 0)
            func_0202e018(0x19, param_1 + 10, 0xc);
        else
            func_0202e018(0x1c, param_1 + 0x13, 3);
    } else if ((f & 2) == 0) {
        func_0202e018(0x1a, param_1 + 10, 9);
    }
    if ((*param_1 & 1) != 0)
        return;
    func_0202e018(0x1b, param_1 + 1, 3);
}
