/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern char *data_020cc080;

int SND_CountReservedCommand(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_020cc080;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}
