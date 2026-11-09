/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int SND_CountReservedCommand(void);

extern int func_02009a98(void);

int SND_CountWaitingCommand(void) {
    int reserved = SND_CountReservedCommand();
    return 0x100 - reserved - func_02009a98();
}
