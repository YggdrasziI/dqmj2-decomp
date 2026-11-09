/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int PXI_SendWordByFifo(int a, int b, int c);

void PMi_SendPxiData(int arg0)
{
    while (PXI_SendWordByFifo(8, arg0, 0) != 0);
}
