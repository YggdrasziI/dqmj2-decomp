/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern char *SND_AllocCommand(int wait);

extern void SND_PushCommand(char *cmd);

void PushCommand_impl(int cmd, int a, int b, int c, int d) {
    char *slot = SND_AllocCommand(1);
    if (slot == 0) {
        return;
    }
    *(int *)(slot + 4) = cmd;
    *(int *)(slot + 8) = a;
    *(int *)(slot + 0xc) = b;
    *(int *)(slot + 0x10) = c;
    *(int *)(slot + 0x14) = d;
    SND_PushCommand(slot);
}
