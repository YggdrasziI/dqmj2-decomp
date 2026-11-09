/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    int (*run)(void *);
    void (*done)(void *);
    int result;
    int rest[6];
} Ov_CardJob;

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void MI_CpuFill8(void *dst, int value, int size);

extern void OS_SleepThread(void *queue);

extern void OS_ExitThread(void);

extern char data_020d4e88;

void JobQueue_WorkerLoop(char *ctx) {
    Ov_CardJob job;
    void (*done)(void *);
    int enabled;
    for (;;) {
        MI_CpuFill8(&job, 0, 0x24);
        enabled = OS_DisableInterrupts();
        while (*(char *volatile *)(ctx + 0xc0) == 0) {
            OS_SleepThread(0);
        }
        job = *(Ov_CardJob *)*(char *volatile *)(ctx + 0xc0);
        OS_RestoreInterrupts(enabled);
        if (job.run != 0) {
            job.result = job.run(&job);
        }
        enabled = OS_DisableInterrupts();
        done = job.done;
        *((char *)&data_020d4e88 + 0x26) = 0;
        if (done != 0) {
            done(&job);
        }
        if (*(int *)&data_020d4e88 != 0) {
            *(char *volatile *)(ctx + 0xc0) = 0;
            OS_RestoreInterrupts(enabled);
        } else {
            OS_ExitThread();
            return;
        }
    }
}
