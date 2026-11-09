/*
 * Main unit 0x02042678-0x02043938: a state machine that drives overlay 1 through
 * the object at 0x020DF89C (state byte at +0x3), its setup and teardown, and the
 * accessors of that object.
 *
 * Bounds: hypothesis. The object at 0x020DF89C (0x28 bytes, up to the next object
 * at 0x020DF8C4) is used only by this range; the function before (func_02042660)
 * belongs to unit_02042508 and the one after (func_02043938) uses the .data strings
 * from 0x020C6A74 and none of this unit's data. The int of .data 0x020C6A70 is used
 * only here. Functions keep C linkage and their addresses as names. Real file name
 * unknown.
 */

#include "types.h"

extern "C" {

/* At 0x020DF89C. */
typedef struct UnkMain_020df89c {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 step;  // sequence step of func_02042ee8
    /* 0x02 */ s8 unk2;
    /* 0x03 */ u8 state; // state of func_020435a0
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkc;
    /* 0x10 */ int unk10;
    /* 0x14 */ u32 tick[2]; // OS_GetTick()
    /* 0x1C */ int unk1c;
    /* 0x20 */ u32 flags;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
} UnkMain_020df89c; // size 0x28

/* The entries returned by func_02062144 (three of them). */
typedef struct UnkEntry {
    /* 0x000 */ u8 unk0[0xc];
    /* 0x00C */ u8 unkc[3];
    /* 0x00F */ u8 unkf[0x1f];
    /* 0x02E */ s16 unk2e;
    /* 0x030 */ u16 unk30;
    /* 0x032 */ u8 unk32[0x16];
    /* 0x048 */ u8 unk48[0x40];
    /* 0x088 */ u8 unk88[0x20];
    /* 0x0A8 */ u8 unka8;
    /* 0x0A9 */ u8 unka9;
    /* 0x0AA */ u8 unkaa;
    /* 0x0AB */ u8 unkab;
    /* 0x0AC */ u8 unkac;
    /* 0x0AD */ u8 unkad[7];
    /* 0x0B4 */ u8 unkb4[0x14];
    /* 0x0C8 */ u8 unkc8[0x54];
    /* 0x11C */ u8 unk11c[4];
} UnkEntry;

/* The records returned by func_ov001_021ccec4. */
typedef struct UnkEntrySrc {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4[0x5e];
    /* 0x62 */ u8 unk62;
} UnkEntrySrc;

UnkMain_020df89c data_020df89c = {0};
int data_020c6a70 = 1;

void MIi_CpuClearFast(u32 data, void *dest, u32 size);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void GX_SetBankForTex(int bank);
void GX_SetBankForTexPltt(int bank);
void GX_SetBankForBG(int bank);
void GX_SetBankForOBJ(int bank);
void GX_SetGraphicsMode(int mode, int bgMode, int bg0As);
void G3X_ResetMtxStack(void);
u64 OS_GetTick(void);

void func_01ffa0e0(void);
u32 func_01ffa428(void);
u32 func_01ffa450(void);
void func_020045d8(void);
void func_02026f60(int x);
void func_02027df0(int x);
void func_02029828(int a, int b, int c);
void func_02029864(int x);
void func_02029898(int x);
void func_020298cc(int x);
void func_020298fc(int x);
int func_02029c2c(int a, int size);
void func_02029d10(int x);
s8 func_02029d8c(int x);
void func_0202a200(void);
int func_0202a250(void);
void func_0202a7bc(int a, int b);
void func_0203c738(void);
int func_0203cb88(void);
void func_0203cce4(int x);
int func_0203cde4(int x);
void func_0203ce3c(int x);
void func_0203ce5c(void);
void func_0203ce70(void);
void func_0203ce84(void);
void func_0203ff74(void);
void func_0203ff8c(void);
void func_02040be8(int x);
void func_02040c00(int x);
void func_02040e9c(void);
void func_02040fd0(int x);
int func_02041438(void);
int func_02041490(void);
void func_0205931c(int x);
void func_0205aad8(void);
void *func_0205b090(int a, int b, int c);
void func_0205c494(int a, int b, int c, int d);
void func_0205c568(int a, int b);
int func_0205c934(void);
void func_0205c94c(int handle);
u8 func_02060a6c(int x);
int func_02061f00(void);
int func_02062118(int i);
UnkEntry *func_02062144(int i);
int func_02062a10(void);
int func_02062a38(void);
void func_02062a94(void);
int func_02062cdc(void);
u8 func_02062d1c(void);
u8 *func_02062d2c(void);
void func_02062d38(int x);
void func_0207793c(int a, int b, void *c);
void func_02078030(int a, void *b, void *c);
u16 func_02078268(void *a, void *b);
void func_02078ff0(void *a, int b);
int func_02079074(void *a);

void func_ov000_021cb360(void);
void func_ov000_021cb4b0(void);
void func_ov000_021cd064(void);
void func_ov000_021d47c8(void);
void func_ov001_021cb408(void);
void func_ov001_021cb454(int a, int b);
void func_ov001_021cb494(void);
void func_ov001_021cc728(int x);
void func_ov001_021cc778(void);
void func_ov001_021cc7ac(void);
void func_ov001_021cc800(int x);
void func_ov001_021cc8d4(void);
void func_ov001_021cc914(void);
void func_ov001_021cc96c(void);
void func_ov001_021cc9a8(void);
int func_ov001_021cca30(void);
void func_ov001_021cca98(void);
int func_ov001_021ccb10(void);
void func_ov001_021ccb80(void);
int func_ov001_021ccc00(void);
void func_ov001_021ccc70(void);
int func_ov001_021ccce8(void);
void func_ov001_021ccd70(void);
void func_ov001_021ccd98(void);
void func_ov001_021ccd9c(int a, int b, int c, int d);
void func_ov001_021cce8c(void);
UnkEntrySrc *func_ov001_021ccec4(int i);
void *func_ov001_021ccedc(void);
void func_ov001_021ccee8(void);
void func_ov001_021ccfb4(void);
void func_ov001_021cd014(void);
void func_ov001_021cd028(void);
void func_ov001_021cd03c(void);
void func_ov001_021cd050(void);
void func_ov001_021cd388(void);
void func_ov001_021cd50c(void);
void func_ov001_021cdd68(int x);
void func_ov001_021cdde8(void);
void func_ov001_021cdff8(int x);
void func_ov001_021ce138(void);
void func_ov001_021ced8c(void);
void func_ov001_021cebb0(void);
u8 *func_ov001_021ceeb0(int a, int b);
void func_ov001_021cf0c4(void);
int func_ov001_021cf30c(u8 *p);
void func_ov001_021d0840(void);
void func_ov001_021d0864(void);
void func_ov001_021d2d94(void);
int func_ov001_021d33a4(void);
void func_ov001_021d414c(void);
int func_ov001_021d4600(void);
void func_ov001_021d4684(void);
void func_ov001_021d46ec(void);
void func_ov001_021d4708(void);
void func_ov001_021d4720(void);
void func_ov001_021d4738(void);
void func_ov001_021d4810(void);
void func_ov001_021d48d8(void);
void func_ov001_021d4944(void);
void func_ov001_021d4a60(void);
int func_ov001_021d72ac(void);
int func_ov001_021d73e8(void);
void func_ov001_021d9470(void);
void func_ov001_021d94bc(UnkEntry *e, UnkEntrySrc *src);
void func_ov001_021d9778(UnkEntry *e, UnkEntrySrc *src);
void func_ov001_021d9e60(void);
void func_ov001_021de254(void);
void func_ov001_021de8d4(void);
int func_ov001_021deae4(void);
void func_ov001_021dec08(void);
void func_ov001_021dec34(void);
void func_ov001_021e0548(void);
void func_ov001_021e0634(void);
void func_ov001_021e0674(void);
void func_ov001_021e0804(void);
void func_ov001_021e0f6c(void);
void func_ov001_021e6844(int x);
void func_ov001_021e68a0(void);
void func_ov001_021e6908(void);
void func_ov001_021e6a48(void);
void func_ov001_021e6a60(void);
void func_ov001_021e9678(void);
void func_ov001_021e96a4(void);
void func_ov001_021e9700(int x);
void func_ov001_021ef9b4(int x);
void func_ov001_021f0810(int x);
void func_ov001_021f0820(void);
int func_ov001_021f0834(void);
void func_ov001_021f8420(void);
void func_ov001_021f843c(void);
void func_ov001_021f84f0(void);
void func_ov001_021f8698(void);
int func_ov001_021fbac0(u8 *p);
int func_ov001_021fc848(int a, int b);
void func_ov001_021ff57c(void);
void func_ov001_021ff628(void);
void func_ov001_021ff868(int x);
void func_ov001_02203494(void);
void func_ov001_022034c0(void);
void func_ov001_0220356c(void);
void func_ov001_022035c4(void);
void func_ov001_02203630(void);
void func_ov001_0220368c(void);
int func_ov001_022036d4(void);
void func_ov001_022036e4(void);
int func_ov001_0220372c(void);
void func_ov001_02203758(void);
int func_ov001_022037a8(void);
void func_ov001_022037c4(void);
void func_ov001_02203824(void);
int func_ov001_0220386c(void);
void func_ov001_022038a0(void);
int func_ov001_022038e8(void);
void func_ov001_0220395c(void);
int func_ov001_022039a4(void);

int func_020437a4(u32 mask);
u32 func_020437d4(u32 flags);
u8 func_0204376c(void);
int func_02043828(void);
int func_02043858(void);
int func_02043874(void);
int func_020438b8(int x);
int func_020438d0(void);
u8 func_020438e0(void);
void func_02043918(u8 x);
u8 func_02043928(void);
void func_020436fc(void);
void func_0204371c(void);

#define REG_DISPCNT    (*(volatile u32 *)0x04000000)
#define REG_BG0CNT     (*(volatile u16 *)0x04000008)
#define REG_BG1CNT     (*(volatile u16 *)0x0400000a)
#define REG_BG2CNT     (*(volatile u16 *)0x0400000c)
#define REG_BG3CNT     (*(volatile u16 *)0x0400000e)
#define REG_DISP3DCNT  (*(volatile u16 *)0x04000060)

void func_02042678(void) {
    int size = 0x28000;

    if (func_02061f00() == 0x23 || func_02061f00() == 0x24) {
        size = 0x18000;
    }
    func_02029c2c(1, 0xe4000);
    func_02029c2c(4, 0xc800);
    if (func_02029c2c(2, size) == 0) {
        func_0202a200();
    }
    data_020df89c.unk2 = func_02029d8c(1);
    func_02027df0(4);
    func_02040be8(0x3f);
    func_02040c00(0x3f);
    func_02040fd0(2);
    func_0202a7bc(3, 0x10000);
    func_0203ce5c();
    func_0203ce70();
    func_0203ce84();
    func_0203c738();
    GX_SetBankForTex(0xb);
    GX_SetBankForTexPltt(0x10);
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x40);
    GX_SetGraphicsMode(1, 0, 1);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x10;
    MIi_CpuClearFast(0, (void *)0x06000000, 0x80000);
    MIi_CpuClearFast(0, (void *)0x06400000, 0x40000);
    MIi_CpuClearFast(0, (void *)0x07000000, 0x400);
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 0x8);
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (7 << 8));
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | (6 << 8));
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (0x17 << 8);
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 3);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 2);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 1);
    REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 0);
    func_ov001_021ccee8();
    func_ov000_021cb360();
    func_ov000_021cd064();
    func_ov001_021cd388();
    func_ov001_021d46ec();
    func_ov001_02203494();
    func_ov001_021de254();
    func_ov001_021ff57c();
    func_ov001_021e0548();
    func_ov001_021e9678();
    func_ov001_021f843c();
    func_ov001_021e6a48();
    func_02029828(0, 0, 0x1f);
    func_02029864(0x1f);
    func_02029898(0x3f);
    func_020298cc(0);
    func_020298fc(0x7fff);
    data_020df89c.unk8 = func_0205c934();
    func_02026f60(2);
    data_020df89c.unk5 = 0;
    data_020df89c.state = 0;
}

void func_020428b4(void) {
    func_ov001_021ff628();
    func_ov001_021e0804();
    func_ov001_021cb408();
    func_ov001_021e6a60();
    func_0205c94c(data_020df89c.unk8);
    func_02029d8c(data_020df89c.unk2);
    func_02029d10(2);
    func_02029d10(4);
    func_02029d10(1);
}

int func_02042900(UnkEntrySrc *src) {
    u32 flags = func_020437a4(0);
    u8 bits = src->unk62;
    u32 f = 0;

    if (bits & 0x1) {
        f |= 0x2;
    }
    if (bits & 0x2) {
        f |= 0x2000;
    }
    if (bits & 0x4) {
        f |= 0x80;
    }
    if (bits & 0x8) {
        f |= 0x40000000;
    }
    if (bits & 0x10) {
        f |= 0x80000000;
    }
    func_020437d4(f | flags);
    return 0;
}

int func_02042950(void) {
    int i;
    int id;
    int n;
    UnkEntrySrc *src;
    UnkEntry *e;
    int ids[3];

    n = 0;
    ids[0] = func_02062118(0);
    ids[1] = func_02062118(1);
    ids[2] = func_02062118(2);
    func_ov001_021ccd9c(1, ids[0], ids[1], ids[2]);
    for (i = 0; i < 3; i++) {
        e = func_02062144(i);
        if (ids[i] >= 0) {
            src = func_ov001_021ccec4(i);
            id = src->unk0;
            e->unk2e = id;
            e->unkab = src->unk2;
            e->unkac = src->unk3;
            e->unka9 = func_02060a6c(id);
            func_ov001_021d94bc(e, src);
            func_ov001_021d9778(e, src);
            func_0207793c(id, 0, e->unk48);
            func_02078030(id, e->unk48, e->unk88);
            MI_CpuCopy8(func_0205b090(2, 0, id), e->unkb4, 0x14);
            if (func_02043928()) {
                e->unk30 = func_02078268(e->unk11c, e->unk48);
                e->unka8 = 0x32;
            }
            func_02042900(src);
            n++;
        } else {
            e->unk2e = -1;
        }
    }
    func_ov001_021cce8c();
    return n;
}

int func_02042a90(void) {
    int i;
    int j;
    int n = 0;

    for (i = 0; i < 3; i++) {
        UnkEntry *e = func_02062144(i);
        if (e->unk2e >= 0) {
            for (j = 0; j < 3; j++) {
                e->unkc[j] = func_0203cde4(0xf9) + 7;
            }
            MI_CpuCopy8(func_0205b090(2, 0, (u16)e->unk2e), e->unkb4, 0x14);
            n++;
        }
    }
    return n;
}

int func_02042b1c(void) {
    int i;
    int n = 0;

    for (i = 0; i < 3; i++) {
        UnkEntry *e = func_02062144(i);
        if (e->unk2e >= 0) {
            e->unk30 = func_02078268(e->unk11c, e->unk48);
            e->unka8 = 0x32;
            n++;
        }
    }
    return n;
}

void func_02042b70(void) {
    u8 mode = data_020df89c.unk24;
    int x = func_020438e0() == 0;

    if (mode == 0) {
        func_02042950();
    } else if (mode == 2 && x) {
        func_02042950();
    } else if (mode == 3) {
        func_02042b1c();
    } else if (mode == 1) {
        func_02042a90();
    }
}

/* 99.09 %: the two zero stores after func_ov001_021cb454 swap r1 / r2 (the original
 * keeps the zero in r1 and the base in r2). Declaration forms, a pointer local, an
 * inline helper and the permuter (about 65000 variants) left it unchanged. */
int func_02042bd8(void) {
    if (func_02043874()) {
        func_020438b8(func_02062cdc());
        func_0203ce3c(func_020438d0());
    }
    *(u64 *)data_020df89c.tick = OS_GetTick();
    data_020df89c.unk25 = func_02062d1c();
    func_0203ff74();
    func_ov001_021d9470();
    func_ov001_021cb454(0x2e, 0);
    data_020df89c.unk1c = 0;
    data_020df89c.unk26 = 0;
    func_0203cce4(3);
    func_ov001_021d9e60();
    func_ov001_021d0864();
    data_020df89c.state = 1;
    return 1;
}

int func_02042c5c(void) {
    func_ov001_021e6844(data_020df89c.unk25);
    func_0205c494(1, data_020df89c.unk25, -1, -1);
    data_020df89c.state = 2;
    return 0;
}

int func_02042c9c(void) {
    func_ov001_021cd014();
    func_ov001_021ccd70();
    func_ov001_021e68a0();
    func_02042b70();
    func_ov001_021cc728(-1);
    func_ov001_021cc800(0);
    func_02041438();
    func_ov001_021d4708();
    func_ov001_021d4738();
    if (func_02062a38() != -1) {
        func_ov001_022034c0();
    }
    func_ov001_021e0634();
    func_ov001_021e96a4();
    data_020df89c.unk0 = 0;
    data_020df89c.state = 3;
    return 1;
}

int func_02042d08(void) {
    func_ov001_021cd388();
    func_ov001_021e68a0();
    func_ov001_021f84f0();
    func_ov001_021f8698();
    func_ov001_021f8420();
    func_ov001_021ff868(0);
    func_ov001_021ef9b4(0);
    if (func_02043874()) {
        func_0203ce3c(func_020438d0());
        func_ov001_021f0810(1);
    }
    data_020df89c.unk0 = 1;
    data_020df89c.state = 3;
    return 1;
}

int func_02042d68(void) {
    func_ov001_021cd03c();
    func_ov001_021cdde8();
    func_ov001_021cdd68(data_020df89c.unk5 == 0);
    data_020df89c.unk5 = 1;
    func_ov001_021cd50c();
    func_ov001_021e6908();
    data_020df89c.state = 4;
    return 1;
}

u8 func_02042db8(void) {
    switch (func_02062a10()) {
    case 0:
        if (func_ov001_021fc848(0, 1) > func_0203cde4(0x20)) {
            return 1;
        }
        if (func_ov001_021fc848(1, 1) > func_0203cde4(0x20)) {
            return 2;
        }
        return 0;
    case 1:
        return func_ov001_021fc848(0, 0xc) > func_0203cde4(0x20) ? 1 : 0;
    case 2:
        if (func_ov001_021fc848(1, 0x1b) > func_0203cde4(0x20)) {
            return 2;
        }
        return 0;
    case 3:
        return 0;
    }
    return 0;
}

int func_02042e88(void) {
    func_ov001_021d4810();
    if (func_ov001_022036d4()) {
        func_ov001_0220356c();
    }
    func_ov001_021ce138();
    if (!func_02043828()) {
        data_020df89c.unk27 = func_02042db8();
    } else {
        data_020df89c.unk27 = 0;
    }
    func_ov001_021cc8d4();
    func_ov001_021d2d94();
    data_020df89c.state = 5;
    return 1;
}

int func_02042ee8(void) {
    int done = 0;

    switch (data_020df89c.step) {
    case 0:
        func_ov001_021cc96c();
        data_020df89c.step++;
    case 1:
        if (func_0203cb88()) {
            data_020df89c.step++;
        }
        break;
    case 2:
        func_ov001_021cc9a8();
        data_020df89c.step++;
    case 3:
        if (func_ov001_021cca30()) {
            data_020df89c.step++;
        }
        break;
    case 4:
        func_ov001_021ccc70();
        data_020df89c.step++;
    case 5:
        if (func_ov001_021ccce8()) {
            data_020df89c.step++;
        }
        break;
    case 6:
        func_ov001_022036e4();
        data_020df89c.step++;
    case 7:
        if (func_ov001_0220372c()) {
            data_020df89c.step++;
        }
        break;
    case 8:
        func_ov001_02203758();
        data_020df89c.step++;
    case 9:
        if (func_ov001_022037a8()) {
            data_020df89c.step++;
        }
        break;
    case 10:
        func_ov001_02203824();
        data_020df89c.step++;
    case 11:
        if (func_ov001_0220386c()) {
            data_020df89c.step++;
        }
        break;
    case 12:
        func_ov001_022038a0();
        data_020df89c.step++;
    case 13:
        if (func_ov001_022038e8()) {
            data_020df89c.step++;
        }
        break;
    case 14:
        func_ov001_0220395c();
        data_020df89c.step++;
    case 15:
        if (func_ov001_022039a4()) {
            data_020df89c.step++;
        }
        break;
    case 16:
        func_02078ff0(func_ov001_021ccedc(), 0x328);
        data_020df89c.step++;
    case 17:
        if (func_02079074(func_ov001_021ccedc())) {
            data_020df89c.step++;
        }
        break;
    case 18:
        func_ov001_021cca98();
        data_020df89c.step++;
    case 19:
        if (func_ov001_021ccb10()) {
            data_020df89c.step++;
        }
        break;
    case 20:
        func_ov001_021ccb80();
        data_020df89c.step++;
    case 21:
        if (func_ov001_021ccc00()) {
            data_020df89c.step++;
        }
        break;
    case 22:
        if (func_ov001_021deae4()) {
            data_020df89c.step++;
        }
        break;
    case 23:
        func_ov001_021f0820();
        data_020df89c.step++;
        break;
    case 24:
        if (func_ov001_021f0834()) {
            data_020df89c.step++;
        }
        break;
    default:
        data_020df89c.step = 0;
        done = 1;
        break;
    }
    return done;
}

void func_02043224(void) {
    func_ov001_022037c4();
    func_0205aad8();
    func_ov001_021dec08();
}

int func_02043238(void) {
    func_ov001_021d414c();
    data_020df89c.state = 6;
    return 1;
}

int func_02043258(void) {
    if (!data_020df89c.unk7 && func_ov001_021d4600()) {
        data_020df89c.unk7 = 1;
    }
    if (!data_020df89c.unk6 && func_02042ee8()) {
        data_020df89c.unk6 = 1;
    }
    if (data_020df89c.unk7 && data_020df89c.unk6) {
        data_020df89c.unk7 = 0;
        data_020df89c.unk6 = 0;
        data_020df89c.state = 7;
    }
    func_020436fc();
    func_0204371c();
    return 0;
}

int func_020432e4(void) {
    func_ov001_021d4684();
    data_020df89c.state = 8;
    return 1;
}

int func_02043304(void) {
    int sides[2];
    int i;
    int j;
    int ret = 0;
    u8 *p;

    if (data_020df89c.unk0 == 0) {
        if (!func_02043858() || (u8)func_01ffa428() < func_01ffa450()) {
            sides[0] = 0;
            sides[1] = 1;
        } else {
            sides[0] = 1;
            sides[1] = 0;
        }
        for (i = 0; i < 2; i++) {
            int side = sides[i];
            p = func_ov001_021ceeb0(side, 0);
            for (j = 0; j < 3; j++) {
                if (func_ov001_021cf30c(p)) {
                    ret |= func_ov001_021fbac0(p);
                }
                p += 0x3e0;
            }
            p = func_ov001_021ceeb0(side + 2, 0);
            for (j = 0; j < 3; j++) {
                if (func_ov001_021cf30c(p)) {
                    ret |= func_ov001_021fbac0(p);
                }
                p += 0x3e0;
            }
        }
    }
    return ret;
}

int func_02043418(void) {
    func_ov001_021d0840();
    func_02043304();
    data_020df89c.state = 9;
    return 1;
}

int func_0204343c(void) {
    if (func_ov001_021d33a4()) {
        data_020df89c.state = 10;
    }
    return 0;
}

int func_02043460(void) {
    func_ov001_021d4a60();
    data_020df89c.state = 11;
    return 1;
}

int func_02043480(void) {
    if (func_ov001_021d72ac()) {
        data_020df89c.state = 12;
    }
    return 0;
}

int func_020434a4(void) {
    func_ov001_021cdff8(func_ov001_021d73e8() != 6);
    func_ov001_021d4720();
    func_02043224();
    func_ov001_021cf0c4();
    func_ov001_021cd050();
    if (func_ov001_021d73e8() == 6) {
        data_020df89c.state = 15;
    } else {
        data_020df89c.state = 14;
    }
    return 1;
}

int func_020434f4(void) {
    func_ov000_021d47c8();
    if (func_ov001_022036d4()) {
        func_ov001_0220368c();
    }
    func_ov001_021cc778();
    func_ov001_021cc914();
    func_02041490();
    func_ov001_021cd028();
    data_020df89c.state = 16;
    return 1;
}

int func_02043534(void) {
    int r;
    int ret;

    func_0205c568(1, 0);
    func_ov001_021ccd98();
    r = func_ov001_021d73e8();
    ret = data_020c6a70;
    func_02062a94();
    func_02062d38(data_020df89c.unk1c);
    func_ov001_021e9700(r);
    if (r == 1) {
        func_0205931c(3);
    }
    func_020437d4(0);
    func_02043918(0);
    return ret;
}

int func_020435a0(void) {
    int cont = 1;
    int ret = 2;

    data_020df89c.unk10 = func_0202a250();
    G3X_ResetMtxStack();
    func_020045d8();
    do {
        switch (data_020df89c.state) {
        case 0:
            cont = func_02042bd8();
            break;
        case 1:
            cont = func_02042c5c();
            break;
        case 2:
            cont = func_02042c9c();
            break;
        case 3:
            cont = func_02042d68();
            break;
        case 4:
            cont = func_02042e88();
            break;
        case 5:
            cont = func_02043238();
            break;
        case 6:
            cont = func_02043258();
            break;
        case 7:
            cont = func_020432e4();
            break;
        case 8:
            cont = func_02043418();
            break;
        case 9:
            cont = func_0204343c();
            break;
        case 10:
            cont = func_02043460();
            break;
        case 11:
            cont = func_02043480();
            break;
        case 12:
            cont = func_020434a4();
            break;
        case 14:
            cont = func_020434f4();
            break;
        case 15:
            cont = func_02042d08();
            break;
        case 16:
            ret = func_02043534();
            cont = 0;
            break;
        }
    } while (cont);
    func_ov001_021e0674();
    func_01ffa0e0();
    func_02040e9c();
    return ret;
}

void func_020436fc(void) {
    func_ov000_021cb4b0();
    func_ov001_021d48d8();
    func_ov001_022035c4();
    func_ov001_021cebb0();
    func_ov001_021de8d4();
    func_ov001_021e0f6c();
}

void func_0204371c(void) {
    func_ov001_021ccfb4();
    func_ov001_021cb494();
    func_ov001_021cc7ac();
    func_ov001_021d4944();
    func_ov001_02203630();
    func_ov001_021ced8c();
    func_ov001_021dec34();
    func_0203ff8c();
}

void func_02043744(int x) {
    data_020c6a70 = x;
}

u8 func_02043754(u8 x) {
    u8 old = data_020df89c.unk24;
    data_020df89c.unk24 = x;
    return old;
}

u8 func_0204376c(void) {
    return data_020df89c.unk24;
}

int func_0204377c(void) {
    return ++data_020df89c.unk1c;
}

int func_02043794(void) {
    return data_020df89c.unk1c;
}

int func_020437a4(u32 mask) {
    if (mask != 0) {
        return (data_020df89c.flags & mask) != 0;
    }
    return data_020df89c.flags;
}

u32 func_020437d4(u32 flags) {
    u32 old = data_020df89c.flags;
    data_020df89c.flags = flags;
    return old;
}

u8 func_020437ec(void) {
    return data_020df89c.unk0;
}

u8 func_020437fc(void) {
    return data_020df89c.unk26;
}

u8 func_0204380c(void) {
    return ++data_020df89c.unk26;
}

int func_02043828(void) {
    u8 mode = func_0204376c();

    if (func_02043858() || mode == 5) {
        return 1;
    }
    return 0;
}

int func_02043858(void) {
    u8 mode = func_0204376c();
    return mode == 2 || mode == 4;
}

int func_02043874(void) {
    return func_0204376c() == 2;
}

int func_0204388c(void) {
    return data_020c6a70 == 9;
}

u8 func_020438a8(void) {
    return data_020df89c.unk27;
}

int func_020438b8(int x) {
    int old = data_020df89c.unkc;
    data_020df89c.unkc = x;
    return old;
}

int func_020438d0(void) {
    return data_020df89c.unkc;
}

u8 func_020438e0(void) {
    return func_02062d2c()[0x10];
}

int func_020438f0(void) {
    if (func_02043858() && func_02061f00() == 2) {
        return 1;
    }
    return 0;
}

void func_02043918(u8 x) {
    data_020df89c.unk4 = x;
}

u8 func_02043928(void) {
    return data_020df89c.unk4;
}

}
