/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern int data_020c5cb8;

extern int OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(int state);

extern void OS_SleepThread(void *queue);

extern void OS_WakeupThread(void *queue);

extern long long _s32_div_f(int a, int b);

int OS_GetConsoleType(void) {
    return data_020c5cb8 = 0x82000001;
}

void OS_InitMessageQueue(int *r0, int r1, int r2)
{
    r0[1] = 0;
    r0[0] = 0;
    r0[3] = 0;
    r0[2] = 0;
    r0[4] = r1;
    r0[5] = r2;
    r0[6] = 0;
    r0[7] = 0;
}

int OS_SendMessage(char *q, void *msg, int flags) {
    int enabled = OS_DisableInterrupts();
    while (*(int *)(q + 0x14) <= *(int *)(q + 0x1c)) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        OS_SleepThread(q);
    }
    (*(void ***)(q + 0x10))[(int)(_s32_div_f(
        *(int *)(q + 0x18) + *(int *)(q + 0x1c), *(int *)(q + 0x14)) >> 32)] = msg;
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) + 1;
    OS_WakeupThread(q + 8);
    OS_RestoreInterrupts(enabled);
    return 1;
}

int OS_ReceiveMessage(char *q, void **out, int flags) {
    int enabled = OS_DisableInterrupts();
    while (*(int *)(q + 0x1c) == 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        OS_SleepThread(q + 8);
    }
    if (out != 0) {
        *out = (*(void ***)(q + 0x10))[*(int *)(q + 0x18)];
    }
    *(int *)(q + 0x18) = (int)(_s32_div_f(
        *(int *)(q + 0x18) + 1, *(int *)(q + 0x14)) >> 32);
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) - 1;
    OS_WakeupThread(q);
    OS_RestoreInterrupts(enabled);
    return 1;
}

int OS_JamMessage(char *q, void *msg, int flags) {
    int enabled = OS_DisableInterrupts();
    void **slots;
    while (*(int *)(q + 0x14) <= *(int *)(q + 0x1c)) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        OS_SleepThread(q);
    }
    *(int *)(q + 0x18) = (int)(_s32_div_f(
        *(int *)(q + 0x18) + *(int *)(q + 0x14) - 1, *(int *)(q + 0x14)) >> 32);
    slots = *(void ***)(q + 0x10);
    slots[*(int *)(q + 0x18)] = msg;
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) + 1;
    OS_WakeupThread(q + 8);
    OS_RestoreInterrupts(enabled);
    return 1;
}
