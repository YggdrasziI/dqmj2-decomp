/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern unsigned char data_020cdb60;

void SNDi_IncAlarmId(int n) {
    ++*(unsigned char *)((int)&data_020cdb60 + n * 0xc + 8);
}
