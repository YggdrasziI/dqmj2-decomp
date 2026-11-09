/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void OS_InitMutex(int *mutex)
{
    mutex[1] = 0;
    mutex[0] = 0;
    mutex[2] = 0;
    mutex[3] = 0;
}
