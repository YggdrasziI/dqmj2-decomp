/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OS_CreateThread(void *thread, void (*func)(void *), void *arg, void *stack, unsigned stackSize, unsigned prio);

extern void OS_WakeupThreadDirect(void *thread);

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void MIi_CpuFill24(void *p);

extern void JobQueue_WorkerLoop(void *arg);

extern void *data_020d4e88;

extern char data_020d4e8c;

extern char data_020d52b0;

void CTRDGi_InitTaskThread(char *p) {
    int state = OS_DisableInterrupts();
    if (data_020d4e88 == 0) {
        data_020d4e88 = p;
        MIi_CpuFill24(p + 0xc4);
        MIi_CpuFill24(&data_020d4e8c);
        *(int *)(p + 0xc0) = 0;
        OS_CreateThread(p, JobQueue_WorkerLoop, p, &data_020d52b0, 0x400, 0x14);
        OS_WakeupThreadDirect(p);
    }
    OS_RestoreInterrupts(state);
}
