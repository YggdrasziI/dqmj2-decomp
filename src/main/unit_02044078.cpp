/*
 * Main unit 0x02044078-0x020444FC: offset tables (a count, then count + 1 offsets),
 * one entry of such a table read from a file into a heap block, the setup of four
 * 0x30-byte blocks, and dispatchers by background number to the 2D library.
 *
 * Bounds: hypothesis. The .bss 0x020DF8E0-0x020DF9BC (an int, a 0x18-byte block and
 * four 0x30-byte blocks) is used only by this range; the function before
 * (func_02044054) belongs to unit_02043CEC, and the one after (func_020444fc) works
 * on the object at 0x020DF9BC. Functions keep C linkage and their addresses as
 * names. Real file name unknown.
 */

#include "types.h"

extern "C" {

typedef struct UnkFile {
    u8 data[0x48];
} UnkFile; // FSFile

/* An offset table: `count` entries, each from offsets[i] to offsets[i + 1]. */
typedef struct UnkOffsetTbl {
    /* 0x0 */ u32 count;
    /* 0x4 */ u32 offsets[1];
} UnkOffsetTbl;

/* An entry of an offset table: its address and its size. */
typedef struct UnkTblEntry {
    /* 0x0 */ void *data;
    /* 0x4 */ u32 size;
} UnkTblEntry;

typedef struct UnkBlock {
    /* 0x00 */ u8 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unka[6];
    /* 0x10 */ int unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17[0x19];
} UnkBlock; // size 0x30

int data_020df8e0;          // result of func_02044114: 0 ok, 1 read error, 2 open error
/* Words, not bytes: a u8 array moves after the other objects of .bss at link time. */
u32 data_020df8e4[6];
UnkBlock data_020df8fc;
UnkBlock data_020df92c[3];

void OS_Terminate(void);
void DC_FlushRange(const void *start, u32 size);
void FS_InitFile(UnkFile *file);
int FS_OpenFile(UnkFile *file, const char *path);
int FS_CloseFile(UnkFile *file);
int FS_SeekFile(UnkFile *file, int offset, int origin);
int func_0200c180(UnkFile *file, void *dst, int len);
void *G2_GetBG0CharPtr(void);
void *G2_GetBG1CharPtr(void);
void *G2_GetBG2CharPtr(void);
void *G2_GetBG3CharPtr(void);
void *G2S_GetBG0CharPtr(void);
void *G2S_GetBG1CharPtr(void);
void *G2S_GetBG2CharPtr(void);
void *G2S_GetBG3CharPtr(void);
void func_02004e58(int a, int b, int c);
void func_02004eb8(int a, int b, int c);
void func_02004f18(int a, int b, int c);
void func_02004f78(int a, int b, int c);
void func_02004fd8(int a, int b, int c);
void func_02005038(int a, int b, int c);
void func_02005098(int a, int b, int c);
void func_020050f8(int a, int b, int c);
void func_02008c14(u32 value, void *dest, u32 size);
int func_02029dfc(void);
void *func_02029f28(int heap, u32 size, int align);
void func_0202a044(int heap, void *mem);
void func_02044f20(void);

int func_0204435c(int bg, int a, int b, int c);
int func_020443e0(int bg, int a, int b, int c);
void func_0204431c(UnkBlock *block);
void func_020442e4(void);
void func_02044350(void);

void *func_02044078(UnkOffsetTbl *tbl, int index) {
    if (tbl == 0) {
        OS_Terminate();
    }
    return (u8 *)tbl + tbl->offsets[index];
}

u32 func_0204409c(UnkOffsetTbl *tbl, u32 index) {
    if (tbl == 0) {
        OS_Terminate();
    }
    if (tbl->count <= index) {
        OS_Terminate();
    }
    {
        /* The byte offset of offsets[index], reused for both loads */
        u32 off = index * 4 + 4;
        return *(u32 *)((u8 *)tbl + off + 4) - *(u32 *)((u8 *)tbl + off);
    }
}

UnkTblEntry *func_020440dc(UnkTblEntry *e, UnkOffsetTbl *tbl, int index) {
    e->data = func_02044078(tbl, index);
    e->size = func_0204409c(tbl, index);
    return e;
}

void *func_02044114(const char *path, u32 index, int heap, u32 *ioSize) {
    UnkFile file;
    u32 count;
    int start;
    int end;
    u32 size;
    void *buf = 0;

    data_020df8e0 = 0;
    if (heap == -1) {
        heap = func_02029dfc();
    }
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path)) {
        func_0200c180(&file, &count, 4);
        if (count <= index) {
            OS_Terminate();
        }
        FS_SeekFile(&file, index * 4 + 4, 0);
        func_0200c180(&file, &start, 4);
        func_0200c180(&file, &end, 4);
        if (end < start) {
            OS_Terminate();
        }
        if (ioSize == 0 || (size = *ioSize) == 0) {
            size = end - start;
            if (ioSize != 0) {
                *ioSize = size;
            }
        }
        buf = func_02029f28(heap, (size + 3) & ~3, 4);
        FS_SeekFile(&file, start, 0);
        if (func_0200c180(&file, buf, size) <= 0) {
            data_020df8e0 = 1;
        } else {
            DC_FlushRange(buf, size);
            data_020df8e0 = 0;
        }
        FS_CloseFile(&file);
    } else {
        data_020df8e0 = 2;
    }
    return buf;
}

void func_0204427c(int heap, void *mem) {
    func_0202a044(heap, mem);
}

void func_02044288(void) {
    func_02008c14(0, data_020df8e4, sizeof(data_020df8e4));
    func_020442e4();
    func_02044350();
}

int func_020442ac(int sub, int bg, int a, int b, int c) {
    if (sub == 0) {
        func_0204435c(bg, a, b, c);
    } else {
        func_020443e0(bg, a, b, c);
    }
    return 0;
}

void func_020442e4(void) {
    int i;

    func_0204431c(&data_020df8fc);
    for (i = 0; i < 3; i++) {
        func_0204431c(&data_020df92c[i]);
    }
}

void func_0204431c(UnkBlock *block) {
    block->unk0 = 5;
    block->unk2 = -1;
    block->unk4 = 5;
    block->unk6 = 0;
    block->unk8 = 0;
    block->unk10 = 0;
    block->unk14 = 0;
    block->unk15 = 0;
    block->unk16 = 0;
}

void func_02044350(void) {
    func_02044f20();
}

int func_0204435c(int bg, int a, int b, int c) {
    switch (bg) {
    case 0:
        func_02004e58(a, b, c);
        break;
    case 1:
        func_02004f18(a, b, c);
        break;
    case 2:
        func_02004fd8(a, b, c);
        break;
    case 3:
        func_02005098(a, b, c);
        break;
    default:
        OS_Terminate();
        return 0;
    }
    return 1;
}

int func_020443e0(int bg, int a, int b, int c) {
    switch (bg) {
    case 0:
        func_02004eb8(a, b, c);
        break;
    case 1:
        func_02004f78(a, b, c);
        break;
    case 2:
        func_02005038(a, b, c);
        break;
    case 3:
        func_020050f8(a, b, c);
        break;
    default:
        OS_Terminate();
        return 0;
    }
    return 1;
}

void *func_02044464(int bg) {
    switch (bg) {
    case 0:
        return G2_GetBG0CharPtr();
    case 1:
        return G2_GetBG1CharPtr();
    case 2:
        return G2_GetBG2CharPtr();
    case 3:
        return G2_GetBG3CharPtr();
    }
    OS_Terminate();
    return 0;
}

void *func_020444b0(int bg) {
    switch (bg) {
    case 0:
        return G2S_GetBG0CharPtr();
    case 1:
        return G2S_GetBG1CharPtr();
    case 2:
        return G2S_GetBG2CharPtr();
    case 3:
        return G2S_GetBG3CharPtr();
    }
    OS_Terminate();
    return 0;
}

}
