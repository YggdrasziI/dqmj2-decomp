/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int OS_GetInitArenaHi(int arena);

extern void OS_SetArenaHi(int arena, int hi);

extern int func_02007644(int arena);

extern void OS_SetArenaLo(int arena, int lo);

extern int OS_GetConsoleType(void);

extern void func_0200775c(unsigned int v);

extern void func_02007764(unsigned int v);

extern int data_020cbf3c[];

void OS_InitArenaEx(void) {
    OS_SetArenaHi(2, OS_GetInitArenaHi(2));
    OS_SetArenaLo(2, func_02007644(2));
    if (data_020cbf3c[1] != 0) {
        if ((OS_GetConsoleType() & 3) != 1) {
            return;
        }
    }
    func_0200775c(0x200002b);
    func_02007764(0x23e0021);
}
