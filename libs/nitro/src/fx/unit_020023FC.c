/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void FX_InvAsync(int x) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    *(volatile long long *)(div + 4) = (long long)0x1000 << 32;
    *(volatile long long *)(div + 6) = (long long)(unsigned)x;
}
