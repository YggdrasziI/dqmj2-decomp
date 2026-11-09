/*
 * Main unit 0x02040BD8-0x02041090: brightness fades of the two 2D engines
 * (include/game/unk_fade.h). Each operation takes a fade and has two wrappers, one
 * for each of the fades at 0x020DEF6C and 0x020DEF80.
 *
 * Bounds: hypothesis. Every reference to the object at 0x020DEF68 (and its two
 * fades) comes from this range and none from outside; the function before
 * (func_02040bac) and the one after (func_02041090) use other data. The object
 * itself (.bss 0x020DEF68-0x020DEF94) is left outside the unit: the owner of the
 * unreferenced bytes up to 0x020DEFEC is unknown. Functions keep C linkage and their
 * addresses as names. Real file name unknown.
 */

#include "game/unk_fade.h"

extern "C" {

extern Unk020def68 data_020def68;
extern UnkFade data_020def6c; // data_020def68.fadeB
extern UnkFade data_020def80; // data_020def68.fadeA

void G2x_SetBlendBrightness_(volatile u16 *reg, int plane, int brightness);
int func_0203cd08(void);

#define REG_BLDCNT_A ((volatile u16 *)0x04000050)
#define REG_BLDCNT_B ((volatile u16 *)0x04001050)

int func_02040bd8(UnkFade *fade, int plane) {
    int old = fade->plane;
    fade->plane = plane;
    return old;
}

int func_02040be8(int plane) {
    return func_02040bd8(&data_020def80, plane);
}

int func_02040c00(int plane) {
    return func_02040bd8(&data_020def6c, plane);
}

int func_02040c18(UnkFade *fade, u8 type, u8 dir, int duration) {
    fade->type = type;
    fade->dir = dir;
    if (duration <= 0) {
        duration = 1;
    }
    fade->duration = duration;
    fade->frame = 0;
    fade->state = 1;
    fade->target = 0;
    return 1;
}

int func_02040c48(u8 type, u8 dir, int duration) {
    return func_02040c18(&data_020def80, type, dir, duration);
}

int func_02040c70(u8 type, u8 dir, int duration) {
    return func_02040c18(&data_020def6c, type, dir, duration);
}

void func_02040c98(int target) {
    if (target < 0) {
        data_020def68.fadeA.target = -target;
    } else {
        data_020def68.fadeA.target = target;
    }
}

void func_02040cb4(int target) {
    if (target < 0) {
        data_020def68.fadeB.target = -target;
    } else {
        data_020def68.fadeB.target = target;
    }
}

int func_02040cd0(UnkFade *fade) {
    int target = fade->target;
    int level;
    int done = 0;
    u8 dir;
    int finished;

    if (target == 0) {
        target = fade->type == 0 ? 0 : 16;
    }
    if (fade->state == 1) {
        fade->frame++;
        dir = fade->dir;
        if (dir == 2) {
            target = -target;
        }
        level = (16 / (16 - fade->target)) * ((fade->frame * (16 - fade->target)) / fade->duration);
        if (fade->type == 0) {
            level = 16 - level;
        }
        if (dir == 2) {
            level = -level;
        }
        if (func_0203cd08() == 2) {
            if ((fade == &data_020def80 && data_020def68.swapped == 0) ||
                (fade != &data_020def80 && data_020def68.swapped != 0)) {
                G2x_SetBlendBrightness_(REG_BLDCNT_A, fade->plane, level);
            } else {
                G2x_SetBlendBrightness_(REG_BLDCNT_B, fade->plane, level);
            }
        } else if (fade == &data_020def80) {
            G2x_SetBlendBrightness_(REG_BLDCNT_A, fade->plane, level);
        } else {
            G2x_SetBlendBrightness_(REG_BLDCNT_B, fade->plane, level);
        }
        fade->level = level;
        if (fade->dir == 2) {
            if (fade->type == 0) {
                finished = level >= target;
            } else {
                finished = level <= target;
            }
        } else if (fade->type == 0) {
            finished = level <= target;
        } else {
            finished = level >= target;
        }
        if (finished) {
            fade->state = 2;
            done = 1;
        }
    }
    return done;
}

int func_02040e74(void) {
    return func_02040cd0(&data_020def80);
}

int func_02040e88(void) {
    return func_02040cd0(&data_020def6c);
}

int func_02040e9c(void) {
    return 0;
}

int func_02040ea4(void) {
    return 0;
}

void func_02040eac(int swap) {
    if (swap == 0) {
        G2x_SetBlendBrightness_(REG_BLDCNT_A, data_020def68.fadeA.plane, data_020def68.fadeA.level);
        G2x_SetBlendBrightness_(REG_BLDCNT_B, data_020def68.fadeB.plane, data_020def68.fadeB.level);
        data_020def68.swapped = 0;
    } else {
        G2x_SetBlendBrightness_(REG_BLDCNT_A, data_020def68.fadeB.plane, data_020def68.fadeB.level);
        G2x_SetBlendBrightness_(REG_BLDCNT_B, data_020def68.fadeA.plane, data_020def68.fadeA.level);
        data_020def68.swapped = 1;
    }
}

u8 func_02040f30(UnkFade *fade) {
    return fade->state;
}

u8 func_02040f38(void) {
    return func_02040f30(&data_020def80);
}

u8 func_02040f4c(void) {
    return func_02040f30(&data_020def6c);
}

void func_02040f60(UnkFade *fade, int kind) {
    switch (kind) {
    case 0:
        func_02040c18(fade, 0, 2, 1);
        break;
    case 2:
        func_02040c18(fade, 1, 2, 1);
        break;
    case 3:
        func_02040c18(fade, 1, 3, 1);
        break;
    }
    while (func_02040cd0(fade) == 0) {
    }
}

void func_02040fd0(int kind) {
    func_02040f60(&data_020def80, kind);
}

void func_02040fe8(int kind) {
    func_02040f60(&data_020def6c, kind);
}

void func_02041000(UnkFade *fade, int a, int b) {
    fade->frame = (a * b) >> 4;
    if (fade->frame > fade->duration) {
        fade->frame = fade->duration;
    }
}

void func_02041020(int a, int b) {
    func_02041000(&data_020def80, a, b);
}

void func_02041040(int a, int b) {
    func_02041000(&data_020def6c, a, b);
}

s8 func_02041060(UnkFade *fade) {
    return fade->level;
}

s8 func_02041068(void) {
    return func_02041060(&data_020def80);
}

s8 func_0204107c(void) {
    return func_02041060(&data_020def6c);
}

}
