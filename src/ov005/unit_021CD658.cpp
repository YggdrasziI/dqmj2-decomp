/*
 * Overlay 5 unit 0x021CD658-0x021CD7A0: thin wrappers around main-module services
 * and an object at 0x021CE990 loaded from "world.e" / "world.ez<c>".
 *
 * Bounds: hypothesis. The objects at 0x021CE98C and 0x021CE990 are used only by
 * this range; the function before (func_ov005_021cd628) works on the object at
 * 0x021CE95C and the one after (func_ov005_021cd7a0) on 0x021CE88C. The two strings
 * of .data 0x021CE878-0x021CE88C are used only here, in this order. The unit owns
 * the .bss object at 0x021CE990 (size 0x8A0, a hypothesis: the same object in ov000
 * spans 0x8A0 bytes, and the next object used in ov005 is at 0x021CF230); the int
 * at 0x021CE98C is defined elsewhere. Functions keep C linkage and their addresses
 * as names. Real file name unknown.
 */

#include "types.h"

extern "C" {

typedef struct UnkOv005_021ce990 {
    /* 0x000 */ u8 unk0[4];
    /* 0x004 */ int unk4;
    /* 0x008 */ u8 unk8[0x448];
    /* 0x450 */ int unk450;
    /* 0x454 */ u8 unk454[0x44c];
} UnkOv005_021ce990; // size 0x8A0 (hypothesis: the same object in ov000, 0x0222BBD0, spans 0x8A0 bytes)

/* Not defined in this file: defining it makes mwccarm address the next object
 * from it (+4). */
extern int data_ov005_021ce98c;
/* Defined here: mwccarm then reaches the object through two pool words (stores
 * at +0x450 and the call argument), as in the original. */
UnkOv005_021ce990 data_ov005_021ce990 = {0};

void func_0205baac(void);
int func_0205bb18(int a, int b);
int func_0205c934(void);
void func_0205c94c(int handle);
void func_0203cbec(void);
int func_0203cbf4(void);
int func_0201d244(char *buf, const char *fmt, ...);
void func_0204abf0(UnkOv005_021ce990 *obj, const char *name, const char *path);
int func_02059204(void);
int func_020256b4(int x);
int func_0204ac78(UnkOv005_021ce990 *obj, int code);
int func_0204ace4(UnkOv005_021ce990 *obj);
int func_0204ac34(UnkOv005_021ce990 *obj);

void func_ov005_021cd658(void) {
    func_0205baac();
}

int func_ov005_021cd664(int x) {
    return func_0205bb18(-1, x);
}

void func_ov005_021cd678(void) {
    data_ov005_021ce98c = func_0205c934();
}

void func_ov005_021cd690(void) {
    func_0205c94c(data_ov005_021ce98c);
}

void func_ov005_021cd6a8(void) {
    char path[0x20];

    func_0203cbec();
    func_0201d244(path, "world.ez%c", func_0203cbf4());
    func_0204abf0(&data_ov005_021ce990, "world.e", path);
}

int func_ov005_021cd6ec(int code) {
    switch (code) {
    case 0x8c:
        data_ov005_021ce990.unk450 = func_020256b4(func_02059204());
        break;
    case 0x81:
        data_ov005_021ce990.unk450 = func_020256b4(func_02059204());
        break;
    case 0x80:
        break;
    default:
        return 0;
    }
    return func_0204ac78(&data_ov005_021ce990, code);
}

int func_ov005_021cd754(void) {
    return func_0204ace4(&data_ov005_021ce990);
}

int func_ov005_021cd768(void) {
    int result = 0;
    if (func_ov005_021cd754() != 0) {
        result = data_ov005_021ce990.unk4;
    }
    return result;
}

int func_ov005_021cd78c(void) {
    return func_0204ac34(&data_ov005_021ce990);
}

}
