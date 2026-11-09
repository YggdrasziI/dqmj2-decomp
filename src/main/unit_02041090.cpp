/*
 * Main unit 0x02041090-0x0204164C: model resources loaded by name ("%s.m", "%s.a",
 * "%s.nsbca", "%s.mp") into three tables, and the setup of an object that uses them.
 *
 * Bounds: hypothesis. The three .bss tables (0x020DEFEC, 0x020DF0F4, 0x020DF48C,
 * contiguous up to 0x020DF88C) and the .data strings 0x020C69F0-0x020C6A50 are used
 * only by this range; the function before belongs to unit_02040BD8 and the functions
 * after (from func_0204164c) use none of this data. Functions keep C linkage and
 * their addresses as names. Real file name unknown.
 */

#include "types.h"

extern "C" {

/* A model resource (0x58 bytes); the loader functions are outside this unit. */
typedef struct UnkModelRes {
    /* 0x00 */ u8 unk0[0x39];
    /* 0x39 */ u8 loaded;
    /* 0x3A */ u8 unk3a[0x1e];
} UnkModelRes; // size 0x58

/* An entry of the table at 0x020DF0F4 (10 entries), handled by func_0203ffa4 & co. */
typedef struct UnkResSlot {
    /* 0x00 */ u8 unk0[0x5c];
} UnkResSlot; // size 0x5C

/* An entry of the table at 0x020DF48C (64 entries). */
typedef struct UnkAnimRes {
    /* 0x00 */ int id;
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ void *unk8;
    /* 0x0C */ void *file;
} UnkAnimRes; // size 0x10

/* The "%s.mp" data as func_020411c4 reads it: 16 events of 6 bytes after 8 bytes. */
typedef struct UnkAnimEvent {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 type;
    /* 0x4 */ u16 value;
} UnkAnimEvent; // size 0x6

typedef struct UnkAnimMp {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ UnkAnimEvent events[16];
} UnkAnimMp;

typedef struct UnkModelInfo {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 parts[5];
} UnkModelInfo;

typedef struct UnkModelObj {
    /* 0x000 */ u8 unk0[0xc];
    /* 0x00C */ u8 unkc;
    /* 0x00D */ u8 unkd[0xf];
    /* 0x01C */ int unk1c;
    /* 0x020 */ int unk20;
    /* 0x024 */ int unk24;
    /* 0x028 */ u8 unk28[0x30];
    /* 0x058 */ int unk58;
    /* 0x05C */ u8 unk5c[0x20];
    /* 0x07C */ int unk7c;
    /* 0x080 */ int unk80;
    /* 0x084 */ int unk84;
    /* 0x088 */ u8 unk88[0xd4];
    /* 0x15C */ u8 unk15c;
    /* 0x15D */ u8 unk15d;
    /* 0x15E */ u8 unk15e;
    /* 0x15F */ u8 unk15f;
    /* 0x160 */ u8 unk160;
    /* 0x161 */ u8 unk161;
    /* 0x162 */ u8 unk162[2];
    /* 0x164 */ int unk164;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ s16 unk16a;
    /* 0x16C */ int unk16c;
    /* 0x170 */ s16 unk170;
    /* 0x172 */ s16 unk172;
    /* 0x174 */ s16 unk174;
    /* 0x176 */ s16 unk176;
    /* 0x178 */ u8 unk178[0x65];
    /* 0x1DD */ u8 unk1dd;
    /* 0x1DE */ u8 unk1de;
    /* 0x1DF */ u8 unk1df;
} UnkModelObj;

UnkModelRes data_020defec[3];
UnkResSlot data_020df0f4[10];
UnkAnimRes data_020df48c[64];

/* Model names by size. The ROM holds them in the order L, S, M: mwccarm emits a file's
 * data in reverse declaration order, so they are declared M, S, L. */
char data_020c6a08[] = "M_model.m";
char data_020c69fc[] = "S_model.m";
char data_020c69f0[] = "L_model.m";
const char *data_020c6a14[3] = {data_020c69fc, data_020c6a08, data_020c69f0};

void MI_CpuFill8(void *dest, u8 data, u32 size);
void func_02008c14(u32 value, void *dest, u32 size);
int func_0201d244(char *buf, const char *fmt, ...);
int func_020287f0(UnkModelObj *obj, UnkModelRes *res, int x);
void func_02028898(UnkModelObj *obj, const char *name);
int func_0203c8dc(const char *path, int x);
int func_0203cde4(int x);
UnkModelRes *func_0203ffa4(u32 id, UnkResSlot *slots, int count);
UnkModelRes *func_0203fff0(u32 id, UnkResSlot *slots, int count);
void func_0204005c(u32 id, UnkResSlot *slots, int count);
void *func_02040484(int file, const char *name);
int func_0204052c(UnkModelRes *res, const char *path, int x);
void func_020407d4(UnkModelObj *obj, UnkModelRes *res, int x);
int func_02040810(UnkModelRes *res);
int func_020408f0(int file, void *out, const char *name);
const char *func_02042538(u32 id);
const char *func_02042580(u32 id);
UnkModelInfo *func_02042660(int id);
void func_0205baac(int x);

void func_02041090(void) {
    MI_CpuFill8(data_020df0f4, 0, sizeof(data_020df0f4));
    MI_CpuFill8(data_020df48c, 0, sizeof(data_020df48c));
    MI_CpuFill8(data_020defec, 0, sizeof(data_020defec));
}

UnkModelRes *func_020410d4(u32 id) {
    return func_0203ffa4(id, data_020df0f4, 10);
}

int func_020410ec(u32 id) {
    char path[0x10];
    int ret = 0;
    UnkModelRes *res;

    if (id < 0x14c) {
        if (func_020410d4(id) == 0) {
            res = func_0203fff0(id, data_020df0f4, 10);
            if (res != 0) {
                func_0201d244(path, "%s.m", func_02042538(id));
                ret = func_0204052c(res, path, 1);
            }
        } else {
            ret = 1;
        }
    }
    return ret;
}

int func_02041170(u32 id) {
    int ret = 0;
    UnkModelRes *res;

    if (id <= 0x14c) {
        res = func_020410d4(id);
        if (res != 0 && res->loaded && func_02040810(res)) {
            func_0204005c(id, data_020df0f4, 10);
            ret = 1;
        }
    }
    return ret;
}

int func_020411c4(UnkAnimMp *mp) {
    int i;
    int n = 0;

    if (mp != 0) {
        for (i = 0; i < 16; i++) {
            // The explicit cast keeps the test, which mwccarm drops on a bare u16
            if (mp->events[i].type == 2 && (int)mp->events[i].value >= 0) {
                func_0205baac(mp->events[i].value);
                n++;
            }
        }
    }
    return n;
}

UnkAnimRes *func_02041210(int id) {
    int i;
    UnkAnimRes *found = 0;

    for (i = 0; i < 64; i++) {
        if (id == data_020df48c[i].id) {
            found = &data_020df48c[i];
            break;
        }
    }
    return found;
}

UnkAnimRes *func_02041244(int id) {
    UnkAnimRes *tbl = data_020df48c;
    int i;
    UnkAnimRes *e = 0;

    for (i = 0; i < 64; i++) {
        if (tbl[i].id == 0) {
            e = &tbl[i];
            func_02008c14(0, e->unk4, 4);
            e->unk8 = 0;
            tbl[i].id = id;
            break;
        }
    }
    return e;
}

int func_020412a0(int id) {
    int ret = 0;
    UnkAnimRes *tbl = data_020df48c;
    int i;
    UnkAnimRes *e;

    for (i = 0; i < 64; i++) {
        if (id == tbl[i].id) {
            e = &tbl[i];
            func_02008c14(0, e->unk4, 4);
            e->unk8 = 0;
            tbl[i].id = 0;
            ret = 1;
            break;
        }
    }
    return ret;
}

int func_020412fc(u32 id) {
    char path[0x20];
    int ret = 0;
    UnkAnimRes *e;
    const char *name;

    if (id < 0x67c) {
        if (func_02041210(id) == 0) {
            e = func_02041244(id);
            if (e != 0) {
                name = func_02042580(id);
                func_0201d244(path, "%s.a", name);
                e->file = (void *)func_0203c8dc(path, -1);
                if (e->file != 0) {
                    func_0201d244(path, "%s.nsbca", name);
                    if (func_020408f0((int)e->file, e->unk4, path)) {
                        func_0201d244(path, "%s.mp", name);
                        e->unk8 = func_02040484((int)e->file, path);
                        if (e->unk8 != 0) {
                            func_020411c4((UnkAnimMp *)e->unk8);
                        }
                        ret = 1;
                    }
                }
            }
        } else {
            ret = 2;
        }
    }
    return ret;
}

int func_020413e4(int id) {
    int ret = 0;
    int i;

    if (func_020410ec(func_02042660(id)->unk2)) {
        for (i = 0; i < 5; i++) {
            s16 part = func_02042660(id)->parts[i];
            if (part <= 0) {
                break;
            }
            func_020412fc(part);
        }
        ret = 1;
    }
    return ret;
}

int func_02041438(void) {
    int ret = 0;
    int i;
    UnkModelRes *res = data_020defec;

    for (i = 0; i < 3; i++) {
        if (!res->loaded) {
            ret |= func_0204052c(res, data_020c6a14[i], 1);
        }
        res++;
    }
    return ret;
}

int func_02041490(void) {
    int ret = 0;
    int i;
    UnkModelRes *res = data_020defec;

    for (i = 0; i < 3; i++) {
        if (res->loaded) {
            ret |= func_02040810(res);
        }
        res++;
    }
    return ret;
}

int func_02041544(UnkModelObj *obj, int a, int b, int c);

int func_020414d4(UnkModelObj *obj, int x, int idx) {
    int ret = 0;

    if (data_020defec[idx].loaded) {
        if (func_020287f0(obj, &data_020defec[idx], 0)) {
            obj->unk58 = x;
            func_02041544(obj, 0x19a, 0x19a, 0x19a);
            ret = 1;
        }
    }
    return ret;
}

int func_02041544(UnkModelObj *obj, int a, int b, int c) {
    if (!obj->unkc) {
        return 0;
    }
    obj->unk1c = a;
    obj->unk20 = b;
    obj->unk24 = c;
    return 1;
}

int func_02041568(UnkModelObj *obj, int id) {
    int ret = 0;
    UnkModelRes *res;

    if (obj->unk15c == 0) {
        res = func_020410d4(func_02042660(id)->unk2);
        if (res->loaded) {
            func_020407d4(obj, res, 0);
            func_02028898(obj, "UpperBody");
            obj->unk16a = id;
            obj->unk15d = func_02042660(id)->unk0;
            obj->unk164 = -1;
            obj->unk168 = -1;
            obj->unk160 = 0x1f;
            obj->unk7c = 0x19a;
            obj->unk80 = 0x19a;
            obj->unk84 = 0x19a;
            obj->unk161 = func_0203cde4(8);
            ret = 1;
            obj->unk15e = 1;
            obj->unk16c = 0x1000;
            obj->unk170 = 0;
            obj->unk172 = 0;
            obj->unk174 = 0;
            obj->unk176 = 0;
            obj->unk1dd = 0;
            obj->unk1df = 1;
            obj->unk15c = 1;
        }
    }
    return ret;
}

}
