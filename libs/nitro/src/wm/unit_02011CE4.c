/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern char *data_020ce680;

unsigned short func_02011ce4(void) {
    int enabled = OS_DisableInterrupts();
    char *session = *(char **)((char *)&data_020ce680 + 4);
    int value;
    if (session != 0) {
        value = *(int *)(session + 0x14c);
    } else {
        value = 0;
    }
    OS_RestoreInterrupts(enabled);
    return (unsigned short)value;
}
