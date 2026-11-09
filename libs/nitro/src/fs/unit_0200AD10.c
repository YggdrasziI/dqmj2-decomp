/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/mi.h"

#define FS_FILE_NAME_MAX    127

#define FS_ARCHIVE_NAME_LEN_MAX 3

#define FS_DMA_NOT_USE      ((u32) ~0)

#define FS_FILE_STATUS_BUSY                 0x00000001

#define FS_FILE_STATUS_CANCEL               0x00000002

#define FS_FILE_STATUS_SYNC                 0x00000004

#define FS_FILE_STATUS_ASYNC                0x00000008

#define FS_FILE_STATUS_IS_FILE              0x00000010

#define FS_FILE_STATUS_IS_DIR               0x00000020

#define FS_FILE_STATUS_OPERATING            0x00000040

#define FS_ARCHIVE_FLAG_REGISTER              0x00000001

#define FS_ARCHIVE_FLAG_LOADED                0x00000002

#define FS_ARCHIVE_FLAG_TABLE_LOAD            0x00000004

#define FS_ARCHIVE_FLAG_SUSPEND               0x00000008

#define FS_ARCHIVE_FLAG_RUNNING               0x00000010

#define FS_ARCHIVE_FLAG_CANCELING             0x00000020

#define FS_ARCHIVE_FLAG_SUSPENDING            0x00000040

#define FS_ARCHIVE_FLAG_UNLOADING             0x00000080

#define FS_ARCHIVE_FLAG_IS_ASYNC              0x00000100

#define FS_ARCHIVE_FLAG_IS_SYNC               0x00000200

#define FS_ARCHIVE_PROC_READFILE        (1 << FS_COMMAND_READFILE)

#define FS_ARCHIVE_PROC_WRITEFILE       (1 << FS_COMMAND_WRITEFILE)

#define FS_ARCHIVE_PROC_ASYNC           (FS_ARCHIVE_PROC_READFILE | FS_ARCHIVE_PROC_WRITEFILE)

#define FS_ARCHIVE_PROC_SEEKDIR         (1 << FS_COMMAND_SEEKDIR)

#define FS_ARCHIVE_PROC_READDIR         (1 << FS_COMMAND_READDIR)

#define FS_ARCHIVE_PROC_FINDPATH        (1 << FS_COMMAND_FINDPATH)

#define FS_ARCHIVE_PROC_GETPATH         (1 << FS_COMMAND_GETPATH)

#define FS_ARCHIVE_PROC_OPENFILEFAST    (1 << FS_COMMAND_OPENFILEFAST)

#define FS_ARCHIVE_PROC_OPENFILEDIRECT  (1 << FS_COMMAND_OPENFILEDIRECT)

#define FS_ARCHIVE_PROC_CLOSEFILE       (1 << FS_COMMAND_CLOSEFILE)

#define FS_ARCHIVE_PROC_SYNC \
    (FS_ARCHIVE_PROC_SEEKDIR | FS_ARCHIVE_PROC_READDIR | \
     FS_ARCHIVE_PROC_FINDPATH | FS_ARCHIVE_PROC_GETPATH | \
     FS_ARCHIVE_PROC_OPENFILEFAST | FS_ARCHIVE_PROC_OPENFILEDIRECT | FS_ARCHIVE_PROC_CLOSEFILE)

#define FS_ARCHIVE_PROC_ACTIVATE        (1 << FS_COMMAND_ACTIVATE)

#define FS_ARCHIVE_PROC_IDLE            (1 << FS_COMMAND_IDLE)

#define FS_ARCHIVE_PROC_SUSPENDING      (1 << FS_COMMAND_SUSPEND)

#define FS_ARCHIVE_PROC_RESUME          (1 << FS_COMMAND_RESUME)

#define FS_ARCHIVE_PROC_STATUS \
    (FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE | FS_ARCHIVE_PROC_SUSPENDING | FS_ARCHIVE_PROC_RESUME)

#define FS_ARCHIVE_PROC_ALL (~0)

#define BIT_MASK(n) ((1 << (n)) - 1)

typedef void *OSMessage;

typedef enum {
    FS_SEEK_SET,
    FS_SEEK_CUR,
    FS_SEEK_END
} FSSeekFileMode;

typedef enum {
    FS_COMMAND_ASYNC_BEGIN = 0,
    FS_COMMAND_READFILE = FS_COMMAND_ASYNC_BEGIN,
    FS_COMMAND_WRITEFILE,
    FS_COMMAND_ASYNC_END,
    FS_COMMAND_SYNC_BEGIN = FS_COMMAND_ASYNC_END,
    FS_COMMAND_SEEKDIR = FS_COMMAND_SYNC_BEGIN,
    FS_COMMAND_READDIR,
    FS_COMMAND_FINDPATH,
    FS_COMMAND_GETPATH,
    FS_COMMAND_OPENFILEFAST,
    FS_COMMAND_OPENFILEDIRECT,
    FS_COMMAND_CLOSEFILE,
    FS_COMMAND_SYNC_END,
    FS_COMMAND_STATUS_BEGIN = FS_COMMAND_SYNC_END,
    FS_COMMAND_ACTIVATE = FS_COMMAND_STATUS_BEGIN,
    FS_COMMAND_IDLE,
    FS_COMMAND_SUSPEND,
    FS_COMMAND_RESUME,
    FS_COMMAND_STATUS_END,
    FS_COMMAND_INVALID
} FSCommandType;

typedef enum {
    FS_RESULT_SUCCESS = 0,
    FS_RESULT_FAILURE,
    FS_RESULT_BUSY,
    FS_RESULT_CANCELED,
    FS_RESULT_UNSUPPORTED,
    FS_RESULT_ERROR,
    FS_RESULT_PROC_ASYNC,
    FS_RESULT_PROC_DEFAULT,
    FS_RESULT_PROC_UNKNOWN
} FSResult;

typedef FSResult (*FS_ARCHIVE_PROC_FUNC)(struct FSFile *, FSCommandType);

typedef FSResult (*FS_ARCHIVE_READ_FUNC)(struct FSArchive *p, void *dst, u32 pos, u32 size);

typedef FSResult (*FS_ARCHIVE_WRITE_FUNC)(struct FSArchive *p, const void *src, u32 pos, u32 size);

typedef struct FSFileLink {
    struct FSFile *prev;
    struct FSFile *next;
} FSFileLink;

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct FSArchiveFAT {
    u32 top;
    u32 bottom;
} FSArchiveFAT;

typedef struct FSArchiveFNT {
    u32 start;
    u16 index;
    u16 parent;
} FSArchiveFNT;

typedef struct FSArchive {
    union {
        char ptr[FS_ARCHIVE_NAME_LEN_MAX + 1];
        u32 pack;
    } name;                       
    struct FSArchive *next;       
    struct FSArchive *prev;       
    OSThreadQueue sync_q;         
    OSThreadQueue stat_q;         
    u32 flag;                     
    FSFileLink list;              
    u32 base;                     
    u32 fat;                      
    u32 fat_size;                 
    u32 fnt;                      
    u32 fnt_size;                 
    u32 fat_bak;                  
    u32 fnt_bak;                  
    void *load_mem;               
    FS_ARCHIVE_READ_FUNC read_func;    
    FS_ARCHIVE_WRITE_FUNC write_func;  
    FS_ARCHIVE_READ_FUNC table_func;   
    FS_ARCHIVE_PROC_FUNC proc;    
    u32 proc_flag;                
} FSArchive;

typedef struct {
    struct FSArchive *arc;
    u16 own_id;
    u16 index;
    u32 pos;
} FSDirPos;

typedef struct {
    struct FSArchive *arc;
    u32 file_id;
} FSFileID;

typedef struct {
    union {
        FSFileID file_id;
        FSDirPos dir_id;
    };
    u32 is_directory;
    u32 name_len;
    char name[FS_FILE_NAME_MAX + 1];
} FSDirEntry;

typedef struct {
    FSDirPos pos;
} FSSeekDirInfo;

typedef struct {
    FSDirEntry *p_entry;
    BOOL skip_string;
} FSReadDirInfo;

typedef struct {
    FSDirPos pos;
    const char *path;
    BOOL find_directory;
    union {
        FSFileID *file;
        FSDirPos *dir;
    } result;
} FSFindPathInfo;

typedef struct {
    u8 *buf;
    u32 buf_len;
    u16 total_len;
    u16 dir_id;
} FSGetPathInfo;

typedef struct {
    FSFileID id;
} FSOpenFileFastInfo;

typedef struct {
    u32 top;
    u32 bottom;
    u32 index;
} FSOpenFileDirectInfo;

typedef struct {
    u32 reserved;
} FSCloseFileInfo;

typedef struct {
    void *dst;
    u32 len_org;
    u32 len;
} FSReadFileInfo;

typedef struct {
    const void *src;
    u32 len_org;
    u32 len;
} FSWriteFileInfo;

typedef struct FSFile {
    FSFileLink link;              
    struct FSArchive *arc;        
    u32 stat;                     
    FSCommandType command;        
    FSResult error;               
    OSThreadQueue queue[1];       
    union {
        struct {
            u32 own_id;
            u32 top;
            u32 bottom;
            u32 pos;
        } file;
        struct {
            FSDirPos pos;
            u32 parent;
        } dir;
    } prop;                       
    union {
        FSReadFileInfo readfile;
        FSWriteFileInfo writefile;
        FSSeekDirInfo seekdir;
        FSReadDirInfo readdir;
        FSFindPathInfo findpath;
        FSGetPathInfo getpath;
        FSOpenFileFastInfo openfilefast;
        FSOpenFileDirectInfo openfiledirect;
        FSCloseFileInfo closefile;
    } arg;                        
} FSFile;

typedef struct {
    FSArchive *arc;
    u32 pos;
} FSiSyncReadParam;

extern struct FSFile;

extern struct FSArchive;

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern void OS_SleepThread(OSThreadQueue *queue);

extern void OS_WakeupThread(OSThreadQueue *queue);

extern FSResult FSi_ReadTable(FSiSyncReadParam *p, void *dst, u32 len);

extern void FSi_SeekDirDirect(FSFile *p_dir, u32 id);

extern int FSi_StrNICmp(const char *str1, const char *str2, u32 len);

extern FSResult FSi_TranslateCommand(FSFile *p_file, FSCommandType command);

extern void FSi_ReleaseCommand(FSFile *p_file, FSResult ret);

extern void FSi_ExecuteAsyncCommand(FSFile *p_file);

extern FSFile *FSi_NextCommand(FSArchive *p_arc);

extern BOOL FSi_SendCommand(FSFile *p_file, FSCommandType command);

extern void FS_InitFile(FSFile *p_file);

extern BOOL FS_CloseFile(FSFile *p_file);

extern BOOL FS_OpenFileDirect(FSFile *p_file, FSArchive *p_arc, u32 image_top, u32 image_bottom, u32 file_index);

extern BOOL FS_OpenFileFast(FSFile *p_file, FSFileID file_id);

extern int FS_ReadFile(FSFile *p_file, void *dst, s32 len);

extern BOOL FS_WaitAsync(FSFile *p_file);

extern FSArchive *FS_FindArchive(const char *name, int name_len);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern void MI_CpuFill8(void *dst, u8 data, u32 size);

extern const char data_020c5cbc[];

static inline BOOL FS_IsBusy(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_BUSY) ? TRUE : FALSE;
}

static inline BOOL FS_IsCanceling(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_CANCEL) ? TRUE : FALSE;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile *p_file)
{
    return (p_file->error == FS_RESULT_SUCCESS) ? TRUE : FALSE;
}

static inline BOOL FS_IsFile(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_FILE) ? TRUE : FALSE;
}

static inline BOOL FS_IsDir(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_DIR) ? TRUE : FALSE;
}

static inline BOOL FS_IsFileSyncMode(const volatile FSFile *p)
{
    return (p->stat & FS_FILE_STATUS_SYNC) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_LOADED) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveTableLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_TABLE_LOAD) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveSuspended(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_SUSPEND) ? TRUE : FALSE;
}

static inline void FSi_CutFromListCore(FSFileLink *trg)
{
    FSFile *const pr = trg->prev;
    FSFile *const nx = trg->next;
    if (pr)
        pr->link.next = nx;
    if (nx)
        nx->link.prev = pr;
}

static inline void FSi_CutFromList(FSFile *elem)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    trg->next = trg->prev = NULL;
}

static inline void FSi_AppendToList(FSFile *elem, FSFile *list)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    {
        while (list->link.next)
            list = list->link.next;
        list->link.next = elem;
        trg->prev = list;
        trg->next = NULL;
    }
}

static inline BOOL FSi_IsSlash(u32 c)
{
    return (c == '/') || (c == '\\');
}

static inline BOOL FSi_IsArchiveRunning(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_RUNNING) != 0);
}

static inline BOOL FSi_IsArchiveCanceling(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_CANCELING) != 0);
}

static inline BOOL FSi_IsArchiveSuspending(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_SUSPENDING) != 0);
}

static inline BOOL FSi_IsArchiveAsync(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_IS_ASYNC) != 0);
}

static inline BOOL FSi_IsArchiveSync(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_IS_SYNC) != 0);
}

static inline u8 MI_ReadByte(const void *address) { return *(const u8 *)address; }

static inline void MI_WriteByte(void *address, u8 value) { *(u8 *)address = value; }

FSResult FSi_GetPathCommand (FSFile *p_file)
{
	FSArchive *const p_arc = p_file->arc;
	FSGetPathInfo *p_info = &p_file->arg.getpath;
	FSDirEntry entry;
	FSFile tmp;
	u32 dir_id;
	u32 file_id;
	u32 id;
	u32 len;

	enum {
        INVALID_ID = 0x10000
    };

	FS_InitFile(&tmp);
	tmp.arc = p_file->arc;

	if (FS_IsDir(p_file)) {
		dir_id = p_file->prop.dir.pos.own_id;
		file_id = INVALID_ID;
	} else {
		file_id = p_file->prop.file.own_id;
		if (p_info->total_len != 0) {
			dir_id = p_info->dir_id;
		} else {
			u32 pos = 0;
			u32 num_dir = 0;
			dir_id = INVALID_ID;

			do {
				FSi_SeekDirDirect(&tmp, pos);
				if (!pos)
					num_dir = tmp.prop.dir.parent;

				tmp.arg.readdir.p_entry = &entry;
				tmp.arg.readdir.skip_string = TRUE;

				while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
					if (!entry.is_directory && (entry.file_id.file_id == file_id)) {
						dir_id = tmp.prop.dir.pos.own_id;
						break;
					}
				}
			} while ((dir_id == INVALID_ID) && (++pos < num_dir));
		}
	}

	if (dir_id == INVALID_ID) {
		p_info->total_len = 0;
		return FS_RESULT_FAILURE;
	}

	if (p_info->total_len == 0) {
		len = 0;

		if (p_arc->name.pack <= 0x000000FF)
			len += 1;
		else if (p_arc->name.pack <= 0x0000FF00)
			len += 2;
		else
			len += 3;
		len += 1 + 1;

		if (file_id != INVALID_ID)
			len += entry.name_len;

		id = dir_id;

		if (id != 0) {
			FSi_SeekDirDirect(&tmp, id);

			do {
				FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
				tmp.arg.readdir.p_entry = &entry;
				tmp.arg.readdir.skip_string = TRUE;
				while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
					if (entry.is_directory && (entry.dir_id.own_id == id)) {
						len += entry.name_len + 1;
						break;
					}
				}
				id = tmp.prop.dir.pos.own_id;
			} while (id != 0);
		}

		p_info->total_len = (u16)(len + 1);
		p_info->dir_id = (u16)dir_id;
	}

	if (!p_info->buf)
		return FS_RESULT_SUCCESS;

	if (p_info->buf_len < p_info->total_len)
		return FS_RESULT_FAILURE;

	else {
		u8 *dst = p_info->buf;
		u32 total = p_info->total_len;
		u32 pos = 0;

		if (p_arc->name.pack <= 0x000000FF)
			len = 1;
		else if (p_arc->name.pack <= 0x0000FF00)
			len = 2;
		else
			len = 3;

		MI_CpuCopy8(p_arc->name.ptr, dst + pos, len);
		pos += len;

		MI_CpuCopy8(data_020c5cbc, dst + pos, 2);
		pos += 2;

		id = dir_id;
		FSi_SeekDirDirect(&tmp, id);

		if (file_id != INVALID_ID) {
			tmp.arg.readdir.p_entry = &entry;
			tmp.arg.readdir.skip_string = FALSE;
			while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
				if (!entry.is_directory && (entry.file_id.file_id == file_id))
					break;
			}
			len = entry.name_len + 1;
			MI_CpuCopy8(entry.name, dst + total - len, len);
			total -= len;
		} else {
			MI_WriteByte(dst + total - 1, '\0');
			total -= 1;
		}

		if (id != 0) {
			do {
				FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
				tmp.arg.readdir.p_entry = &entry;
				tmp.arg.readdir.skip_string = FALSE;

				MI_WriteByte(dst + total - 1, '/');
				total -= 1;

				while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
					if (entry.is_directory && (entry.dir_id.own_id == id)) {
						len = entry.name_len;
						MI_CpuCopy8(entry.name, dst + total - len, len);
						total -= len;
						break;
					}
				}
				id = tmp.prop.dir.pos.own_id;
			} while (id != 0);
		}
	}

	return FS_RESULT_SUCCESS;
}
