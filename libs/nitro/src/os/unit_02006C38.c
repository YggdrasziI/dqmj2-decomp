/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();

extern void OS_RestoreInterrupts(int mask);

extern int data_020cbcc0[];

int OS_SetIrqWorkField30(int arg0) {
    int mask;
    int old;
    mask = OS_DisableInterrupts();
    old = data_020cbcc0[0xc];
    data_020cbcc0[0xc] = arg0;
    OS_RestoreInterrupts(mask);
    return old;
}
