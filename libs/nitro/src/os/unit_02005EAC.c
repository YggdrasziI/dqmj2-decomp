/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void WaitByLoop(unsigned count);

extern int OSi_DoTryLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq);

int OSi_DoLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);

    while (prev > 0) {
        WaitByLoop(0x400);
        prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);
    }
    return prev;
}
