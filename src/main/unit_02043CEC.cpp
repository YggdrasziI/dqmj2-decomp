/*
 * Main unit 0x02043CEC-0x02044078: the table loaded from "EnmyKindTbl.bin"
 * (0x8C bytes per entry) and its accessors, and a name table formatted as "bc_%s".
 *
 * Bounds: hypothesis. The objects at 0x020DF8C4 and 0x020DF8CC are used only by this
 * range, and the .data 0x020C6A90-0x020C6B1C (a table of 23 names of 5 bytes,
 * "EnmyKindTbl.bin", "bc_%s") only here; the function before (func_02043cdc) belongs
 * to unit_02043938 and the functions after (from func_02044078) use none of this
 * data. Functions keep C linkage and their addresses as names. Real file name unknown.
 */

#include "types.h"

extern "C" {

typedef struct UnkEnemyKind {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ u16 unk4_0 : 8;
    /* 0x04 */ u16 unk4_8 : 4;
    /* 0x04 */ u16 unk4_12 : 3;
    /* 0x04 */ u16 unk4_15 : 1;
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ u8 unkc;
    /* 0x0D */ u8 unkd[0x59];
    /* 0x66 */ u8 flag0 : 1;
    /* 0x66 */ u8 flag1 : 1;
    /* 0x66 */ u8 flag2 : 1;
    /* 0x66 */ u8 flag3 : 1;
    /* 0x66 */ u8 flag4 : 1;
    /* 0x66 */ u8 flag5 : 1;
    /* 0x66 */ u8 flag6 : 1;
    /* 0x67 */ u8 unk67[8];
    /* 0x6F */ u8 unk6f[4];
    /* 0x73 */ u8 unk73[4];
    /* 0x77 */ u8 unk77[4];
    /* 0x7B */ u8 unk7b[4];
    /* 0x7F */ u8 unk7f[4];
    /* 0x83 */ u8 unk83[4];
    /* 0x87 */ u8 unk87[5];
} UnkEnemyKind; // size 0x8C

/* At 0x020DF8C4. */
typedef struct UnkEnemyKindTbl {
    /* 0x0 */ u8 *file;
    /* 0x4 */ UnkEnemyKind *entries; // file + 8
} UnkEnemyKindTbl;

UnkEnemyKindTbl data_020df8c4;
char data_020df8cc[0x14];

char data_020c6a90[23][5] = {
    "", "bon", "bon2", "mmz", "win", "win2", "wint", "let", "ose", "ose2", "lib", "reon",
    "reo", "sag", "deth", "yama", "anko", "est", "mast", "rap", "sura", "sulg", "hell",
};

u8 *func_0203c838(const char *path, int arg);
int func_0201d244(char *buf, const char *fmt, ...);

int func_02043cec(int arg) {
    u8 *file = func_0203c838("EnmyKindTbl.bin", arg);

    data_020df8c4.file = file;
    if (file != 0) {
        data_020df8c4.entries = (UnkEnemyKind *)(file + 8);
        return 1;
    }
    return 0;
}

UnkEnemyKind *func_02043d28(int id) {
    return &data_020df8c4.entries[id];
}

int func_02043d40(int level) {
    if (level <= 10) {
        return 1;
    }
    if (level <= 40) {
        return 2;
    }
    if (level <= 50) {
        return 3;
    }
    return 4;
}

u8 func_02043d68(int id, int level) {
    return data_020df8c4.entries[id].unk6f[func_02043d40(level) - 1];
}

u8 func_02043d9c(int id, int level) {
    return data_020df8c4.entries[id].unk73[func_02043d40(level) - 1];
}

u8 func_02043dd0(int id, int level) {
    return data_020df8c4.entries[id].unk77[func_02043d40(level) - 1];
}

u8 func_02043e04(int id, int level) {
    return data_020df8c4.entries[id].unk7b[func_02043d40(level) - 1];
}

u8 func_02043e38(int id, int level) {
    return data_020df8c4.entries[id].unk7f[func_02043d40(level) - 1];
}

u8 func_02043e6c(int id, int level) {
    return data_020df8c4.entries[id].unk83[func_02043d40(level) - 1];
}

int func_02043ea0(int id, int flag) {
    int ret = 0;

    switch (flag) {
    case 0:
        if (data_020df8c4.entries[id].flag0) {
            ret = 1;
        }
        break;
    case 1:
        if (data_020df8c4.entries[id].flag1) {
            ret = 1;
        }
        break;
    case 2:
        if (data_020df8c4.entries[id].flag2) {
            ret = 1;
        }
        break;
    case 3:
        if (data_020df8c4.entries[id].flag3) {
            ret = 1;
        }
        break;
    case 4:
        if (data_020df8c4.entries[id].flag4) {
            ret = 1;
        }
        break;
    case 5:
        if (data_020df8c4.entries[id].flag5) {
            ret = 1;
        }
        break;
    case 6:
        if (data_020df8c4.entries[id].flag6) {
            ret = 1;
        }
        break;
    }
    return ret;
}

u8 func_02043fd0(int id) {
    return data_020df8c4.entries[id].unk4_8 / 3;
}

u8 func_02044008(int id) {
    return data_020df8c4.entries[id].unkc;
}

char *func_02044024(int index) {
    func_0201d244(data_020df8cc, "bc_%s", data_020c6a90[index]);
    return data_020df8cc;
}

int func_02044054(int id) {
    return data_020df8c4.entries[id].unk4_15;
}

}
