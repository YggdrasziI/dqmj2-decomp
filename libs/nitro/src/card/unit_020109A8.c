/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void CARDi_SetRomOp(unsigned int hi, unsigned int lo) {
    volatile unsigned char *cmd;
    while (*(volatile unsigned int *)0x40001a4 & 0x80000000) {
        ;
    }
    cmd = (volatile unsigned char *)0x40001a1;
    cmd[0] = 0xc0;
    cmd[7] = (unsigned char)(hi >> 24);
    cmd[8] = (unsigned char)(hi >> 16);
    cmd[9] = (unsigned char)(hi >> 8);
    cmd[10] = (unsigned char)hi;
    cmd[11] = (unsigned char)(lo >> 24);
    cmd[12] = (unsigned char)(lo >> 16);
    cmd[13] = (unsigned char)(lo >> 8);
    cmd[14] = (unsigned char)lo;
}
