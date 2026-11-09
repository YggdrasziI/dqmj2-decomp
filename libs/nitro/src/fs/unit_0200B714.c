/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

extern struct FSArchive;

typedef struct FSDirPos {
    struct FSArchive *arc;
    u16 own_id;
    u16 index;
    u32 pos;
} FSDirPos;

typedef struct FSArchiveName {
    u32 pack;
} FSArchiveName;

typedef struct FSArchive {
    FSArchiveName name;       
    struct FSArchive *next;   
    struct FSArchive *prev;   
    u32 pad0c;                
    u32 pad10;
    u32 pad14;
    u32 pad18;
    u32 flag;                 
} FSArchive;

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode);

extern u32 FSi_GetPackedName(const char *name, int name_len);

extern FSArchive *FS_FindArchive(const char *name, int name_len);

struct FSArcListGlobal {
    FSArchive *arc_list;
    FSDirPos current_dir_pos;
};

extern struct FSArcListGlobal data_020cdc48;

#define arc_list         data_020cdc48.arc_list

#define current_dir_pos  data_020cdc48.current_dir_pos

BOOL FS_RegisterArchiveName(FSArchive *p_arc, const char *name, int name_len)
{
    BOOL ret = 0;
    OSIntrMode bak_psr = OS_DisableInterrupts();
    if (!FS_FindArchive(name, name_len))
    {
        FSArchive *p_tail = arc_list;
        if (!p_tail)
        {
            arc_list = p_arc;
            current_dir_pos.arc = p_arc;
            current_dir_pos.pos = 0;
            current_dir_pos.index = 0;
            current_dir_pos.own_id = 0;
        }
        else
        {
            while (p_tail->next)
                p_tail = p_tail->next;
            p_tail->next = p_arc;
            p_arc->prev = p_tail;
        }
        p_arc->name.pack = FSi_GetPackedName(name, name_len);
        p_arc->flag |= 1;
        ret = 1;
    }
    (void)OS_RestoreInterrupts(bak_psr);
    return ret;
}
