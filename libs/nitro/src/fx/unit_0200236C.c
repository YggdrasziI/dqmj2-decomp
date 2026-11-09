/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int FX_GetSqrtResult(void);

int FX_Sqrt(int x) {
    volatile unsigned short *sqrtcnt = (volatile unsigned short *)0x40002b0;
    if (x <= 0) {
        return 0;
    }
    *sqrtcnt = 1;
    *(volatile int *)(sqrtcnt + 4) = 0;
    *(volatile int *)(sqrtcnt + 6) = x;
    return FX_GetSqrtResult();
}
