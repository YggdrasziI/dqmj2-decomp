/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern unsigned short func_020060dc(void *lock);

extern int func_02006024(int owner);

extern void WaitByLoop(int count);

extern void OS_UnLockCartridge();

void CTRDGi_LockByProcessor(int owner, char *out) {
    for (;;) {
        *(int *)(out + 4) = OS_DisableInterrupts();
        *(int *)out = func_020060dc((void *)0x027fffe8) & 0x40;
        if (*(int *)out != 0) {
            return;
        }
        if (func_02006024(owner) == 0) {
            return;
        }
        OS_RestoreInterrupts(*(int *)(out + 4));
        WaitByLoop(1);
    }
}

void CTRDGi_UnlockByProcessor(int id, int *ctx) {
    if (ctx[0] == 0) {
        OS_UnLockCartridge(id);
    }
    OS_RestoreInterrupts(ctx[1]);
}
