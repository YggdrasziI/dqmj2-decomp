/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void *data_020cdbc8[];

void PXI_SetFifoRecvCallback(int tag, void *callback) {
    int enabled = OS_DisableInterrupts();
    int *shared = (int *)0x027ffc00;
    data_020cdbc8[tag] = callback;
    if (callback != 0) {
        shared[0xe2] |= 1 << tag;
    } else {
        shared[0xe2] &= ~(1 << tag);
    }
    OS_RestoreInterrupts(enabled);
}
