/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void GXx_SetMasterBrightness_(unsigned short *dst, int value)
{
    if (value == 0) {
        *dst = 0;
    } else if (value > 0) {
        *dst = value | 0x4000;
    } else {
        *dst = -value | 0x8000;
    }
}
