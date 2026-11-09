/*
 * Main unit 0x02042508-0x02042678: the model tables ("ModelTbl.bin",
 * "MotionTbl.bin" and an info table) and their accessors by model id.
 *
 * Bounds: hypothesis. Every reference to the object at 0x020DF88C comes from this
 * range; the function before (func_020424f8) works on a model object (+0x1DD) and
 * the one after (func_02042678) on 0x020DF89C. The two strings of .data
 * 0x020C6A50-0x020C6A70 are used only here, in this order. Functions keep C linkage
 * and their addresses as names. Real file name unknown.
 */

#include "types.h"

extern "C" {

typedef struct UnkModelInfo UnkModelInfo; // 0xE bytes per model (unit_02041090.cpp)

/* At 0x020DF88C. */
typedef struct UnkModelTables {
    /* 0x0 */ u8 infoIsUserBuffer; // set when the info table was read into a caller's buffer
    /* 0x4 */ u8 *motions;         // "MotionTbl.bin": 9 bytes per model
    /* 0x8 */ u8 *models;          // "ModelTbl.bin": 6 bytes per model
    /* 0xC */ u8 *infos;           // 0xE bytes per model
} UnkModelTables;

UnkModelTables data_020df88c = {0};

void *func_0203c838(const char *path, int arg);
u32 func_0202a4c4(void *file);
int func_0202a3fc(void *file, void *buf, u32 size, int x);
void func_0202a044(void *heap, void *mem);

int func_02042508(int arg) {
    data_020df88c.models = (u8 *)func_0203c838("ModelTbl.bin", arg);
    return data_020df88c.models != 0;
}

const char *func_02042538(int id) {
    return (const char *)(data_020df88c.models + id * 6);
}

int func_02042550(int arg) {
    data_020df88c.motions = (u8 *)func_0203c838("MotionTbl.bin", arg);
    return data_020df88c.motions != 0;
}

const char *func_02042580(int id) {
    return (const char *)(data_020df88c.motions + id * 9);
}

int func_02042598(const char *path, int arg) {
    data_020df88c.infos = (u8 *)func_0203c838(path, arg);
    data_020df88c.infoIsUserBuffer = 0;
    return data_020df88c.infos != 0;
}

int func_020425c4(void *file, void *buf, u32 bufSize) {
    u32 size = func_0202a4c4(file);

    if (size <= bufSize && func_0202a3fc(file, buf, size, 0)) {
        data_020df88c.infos = (u8 *)buf;
        data_020df88c.infoIsUserBuffer = 1;
        return 1;
    }
    return 0;
}

int func_0204261c(void *heap) {
    if (data_020df88c.infos != 0) {
        if (!data_020df88c.infoIsUserBuffer) {
            func_0202a044(heap, data_020df88c.infos);
        }
        data_020df88c.infos = 0;
        return 1;
    }
    return 0;
}

UnkModelInfo *func_02042660(int id) {
    return (UnkModelInfo *)(data_020df88c.infos + id * 0xe);
}

}
