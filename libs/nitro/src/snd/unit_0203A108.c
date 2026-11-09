/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

struct S {
    char _0[0x110];
    int flags;
    char _114[0x150 - 0x114];
    int x150;
};

extern void func_0203a160(void *p);

extern void NNSi_SndFaderSet(void *p, int a, int b);

void SNDi_FreeVoiceChannel(struct S *p, int a)
{
    if (((p->flags << 30) >> 31) == 0) {
        func_0203a160(p);
        return;
    }
    if (a == 0) {
        func_0203a160(p);
        return;
    }
    NNSi_SndFaderSet((char *)p + 0xe8, 0, a);
    p->flags |= 8;
    p->x150 = 0;
}
