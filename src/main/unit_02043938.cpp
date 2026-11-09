/*
 * Main unit 0x02043938-0x02043CEC: an object (0x34 bytes) that plays back a path of
 * two point tracks loaded from "<name>.cap" and "<name>.can" / "<name>_<nn>.can",
 * one point per frame, plus an angle test on three points.
 *
 * Bounds: hypothesis. The three strings of .data 0x020C6A74-0x020C6A90 are used only
 * by func_02043938, in this order; the functions up to func_02043cdc work on the same
 * object layout (offsets 0x0-0x30); the function before belongs to unit_02042678 and
 * the one after (func_02043cec) loads "EnmyKindTbl.bin". Functions keep C linkage and
 * their addresses as names. Real file name unknown.
 */

#include "types.h"

extern "C" {

typedef struct UnkVec {
    int x;
    int y;
    int z;
} UnkVec;

typedef struct UnkMtx33 {
    int m[3][3];
} UnkMtx33;

/* The loaded path data: two tables of `count` points, found by their offsets. */
typedef struct UnkPathData {
    /* 0x0 */ int unk0;
    /* 0x4 */ int count;
    /* 0x8 */ int offsets[2];
} UnkPathData;

typedef struct UnkPathPlayer {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 loop;
    /* 0x04 */ int frame;
    /* 0x08 */ UnkVec point1; // from track 0, plus the offset
    /* 0x14 */ UnkVec point0; // from track 1, plus the offset
    /* 0x20 */ UnkVec offset;
    /* 0x2C */ int rotation;
    /* 0x30 */ UnkPathData *data;
} UnkPathPlayer; // size 0x34

void MI_CpuFill8(void *dest, u8 data, u32 size);
void MTX_Identity33_(UnkMtx33 *m);
void MTX_MultVec33(const UnkVec *v, const UnkMtx33 *m, UnkVec *dst);
int FX_Atan2(int y, int x);
int func_0200235c(int a, int b);
int func_0201d244(char *buf, const char *fmt, ...);
void func_02027bd4(UnkMtx33 *m, int rotation);
int func_02027ce8(int angle);
u32 func_02027ee0(int x);
void func_02027f88(int x, int a, int b, int c);
void func_02027fa8(int x, int a, int b, int c);
void func_0202a0c8(void *mem);
UnkPathData *func_0203cb2c(const char *cap, const char *can, int x);
UnkPathData *func_0203cb3c(const char *cap, const char *can, int x);

int func_02043938(const char *name, int index, UnkPathPlayer *player, int alt) {
    char cap[0x20];
    char can[0x20];
    UnkPathData *data;
    int ret = 0;

    func_0201d244(cap, "%s.cap", name);
    if (index >= 0) {
        func_0201d244(can, "%s_%02d.can", name, index);
    } else {
        func_0201d244(can, "%s.can", name);
    }
    if (alt == 0) {
        data = func_0203cb2c(cap, can, -1);
    } else {
        data = func_0203cb3c(cap, can, -1);
    }
    if (data != 0) {
        MI_CpuFill8(player, 0, sizeof(UnkPathPlayer));
        player->data = data;
        ret = 1;
    }
    return ret;
}

int func_020439ec(UnkPathPlayer *player) {
    if (player->data == 0) {
        return 0;
    }
    func_0202a0c8(player->data);
    MI_CpuFill8(player, 0, sizeof(UnkPathPlayer));
    return 1;
}

UnkVec *func_02043a20(UnkPathData *data, int frame, int track) {
    UnkVec *p = 0;

    if (frame < data->count) {
        p = (UnkVec *)((u8 *)data + data->offsets[track]) + frame;
    }
    return p;
}

int func_02043a4c(UnkPathPlayer *player, int apply) {
    UnkVec v1;
    UnkVec v0;
    UnkMtx33 m;
    UnkVec *p1;
    UnkVec *p0;
    int ret = 0;

    if (player != 0 && player->active) {
        p1 = func_02043a20(player->data, player->frame, 0);
        p0 = func_02043a20(player->data, player->frame, 1);
        if (p1 != 0 && p0 != 0) {
            v0 = *p0;
            v1 = *p1;
            if (player->rotation != 0) {
                MTX_Identity33_(&m);
                func_02027bd4(&m, player->rotation);
                MTX_MultVec33(&v0, &m, &v0);
                MTX_MultVec33(&v1, &m, &v1);
            }
            player->point0.x = v0.x + player->offset.x;
            player->point0.y = v0.y + player->offset.y;
            player->point0.z = v0.z + player->offset.z;
            player->point1.x = v1.x + player->offset.x;
            player->point1.y = v1.y + player->offset.y;
            player->point1.z = v1.z + player->offset.z;
            if (apply) {
                func_02027fa8(0, player->point0.x, player->point0.y, player->point0.z);
                func_02027f88(0, player->point1.x, player->point1.y, player->point1.z);
            }
        }
        if (++player->frame >= player->data->count) {
            if (player->loop) {
                player->frame = 0;
            } else {
                player->active = 0;
                ret = 1;
            }
        }
    } else {
        ret = -1;
    }
    return ret;
}

int func_02043be4(UnkPathPlayer *player) {
    int ret = 0;

    if (player->data != 0) {
        player->active = 1;
        player->frame = 0;
        ret = 1;
    }
    return ret;
}

int func_02043c0c(UnkPathPlayer *player) {
    int ret = 0;

    if (player->data != 0) {
        player->active = 0;
        player->frame = 0;
        ret = 1;
    }
    return ret;
}

int func_02043c2c(UnkPathPlayer *player, u8 loop) {
    int old = -1;

    if (player->data != 0) {
        old = player->loop;
        player->loop = loop;
    }
    return old;
}

/* 90.33 %: the original loads c->z and b->z before c->x and b->x and keeps `half` in
 * the register of c (r5, four callee-saved registers); here c stays in r8. Local
 * forms, inline helpers and the permuter left it unchanged. */
int func_02043c48(UnkVec *a, UnkVec *b, UnkVec *c) {
    u32 half = func_02027ee0(0);
    int angC = func_0200235c(FX_Atan2(c->x - b->x, c->z - b->z), 0x47);
    int angA = func_0200235c(FX_Atan2(a->x - b->x, a->z - b->z), 0x47);

    return func_02027ce8(angC - angA) + half < half * 2;
}

void func_02043ccc(UnkPathPlayer *player, int x, int y, int z) {
    player->offset.x = x;
    player->offset.y = y;
    player->offset.z = z;
}

int func_02043cdc(UnkPathPlayer *player, int rotation) {
    int old = player->rotation;
    player->rotation = rotation;
    return old;
}

}
