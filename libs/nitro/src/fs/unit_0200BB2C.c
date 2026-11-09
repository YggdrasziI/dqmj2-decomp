/* NitroSDK; built from twewy (CC0) per-function sources, edited where this
 * build differs (comments below); checked by tools/lib_unit_gen.py --source.
 * File bounds are a hypothesis. */
#pragma force_active on

/* twewy's headers name this build's OS_DisableInterrupts and OS_RestoreInterrupts
 * OS_DisableIRQ and OS_RestoreIRQ, and give their names to other declarations:
 * those are set aside while the headers are read */
#define OS_DisableInterrupts twewy_OS_DisableInterrupts
#define OS_RestoreInterrupts twewy_OS_RestoreInterrupts
/* names used by the headers' inline functions */
#define OS_PauseThread OS_SleepThread

#include <nitro/fs.h>

#include <nitro/os/cpustat.h>

#undef OS_DisableInterrupts
#undef OS_RestoreInterrupts
u32 OS_DisableInterrupts(void);
u32 OS_RestoreInterrupts(u32 state);
#define OS_DisableIRQ OS_DisableInterrupts
#define OS_RestoreIRQ OS_RestoreInterrupts


#define ALIGN_MASK(align)         ((align) - 1)

#define ALIGN_BYTE(target, align) (((u32)target + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

extern FS_Record* Record_List;

extern FS_FilePosition Record_Position;

u32 FS_RecordCondenseName(const char* name, s32 nameLen);

FS_CommandResult FS_RecordCommandReadCB(FS_Record* record, void* dest, u32 pos, u32 size);

FS_CommandResult FS_RecordCommandWriteCB(FS_Record* record, const void* src, u32 pos, u32 size);

FS_CommandResult FS_RecordCommandRead(FS_Record* record, void* dest, u32 pos, u32 size);

FS_File* FSi_NextCommand(FS_Record* record);

void FSi_ExecuteAsyncCommand(FS_File* file);

BOOL FS_RecordCommandExecute(FS_File* file);

BOOL FS_RecordCommandSend(FS_File* file, u32 command);

void FS_RecordInit(FS_Record* record);

FS_Record* FS_RecordFind(const char* name, s32 name_len);

BOOL FS_RecordRegister(FS_Record* record, const char* name, u32 name_len);

void FS_RecordRelease(FS_Record* record);

BOOL FS_RecordLoad(FS_Record* record, u32 baseOffset, u32 fat, u32 fatSize, u32 fnt, u32 fntSize, FS_RecordReadCB readCB,
                   FS_RecordWriteCB writeCB);

BOOL FS_RecordUnload(FS_Record* record);

u32 FS_RecordLoadTable(FS_Record* record, void* buffer, u32 max_size);

void FS_RecordSetMethod(FS_Record* record, FS_RecordMethodCB callback, u32 flags);

void FS_RecordNotifyEnd(FS_Record* record, FS_CommandResult result);

BOOL FS_RecordWait(FS_Record* record) {
    ENTER_CRITICAL_SECTION();
    BOOL isHalted = !FS_IsRecordHalted(record);
    if (isHalted) {
        if (FS_IsRecordActive(record)) {
            record->flags |= FS_RECORD_FLAG_WAITING;
            do {
                OS_SleepThread(&record->unk_14);
            } while (FS_IsRecordWaiting(record));
        } else {
            record->flags |= FS_RECORD_FLAG_HALTED;
        }
    }
    LEAVE_CRITICAL_SECTION();
    return isHalted;
}

BOOL FS_RecordResume(FS_Record* record) {
    FS_File* file = NULL;
    ENTER_CRITICAL_SECTION();
    BOOL isHalted = !FS_IsRecordHalted(record);
    if (isHalted == FALSE) {
        record->flags &= ~FS_RECORD_FLAG_HALTED;
        file = FSi_NextCommand(record);
    }
    LEAVE_CRITICAL_SECTION();
    if (file != NULL) {
        FSi_ExecuteAsyncCommand(file);
    }
    return isHalted;
}
