/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void FSi_InitRom(int priority);

extern int data_020cdc58[];

void FS_Init(int priority) {
    if (data_020cdc58[0] == 0) {
        data_020cdc58[0] = 1;
        FSi_InitRom(priority);
    }
}
