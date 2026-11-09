/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef int (*FSArchiveReadProc)(char **arc, void *dst, u32 off, u32 len);

typedef int (*FSArchiveWriteProc)(char **arc, const void *src, u32 off, u32 len);

typedef struct {
    char pad00[0x1c];
    u32 flag;                  
    char pad20[0x8];
    u32 base;                  
    u32 field_2c;               
    u32 field_30;               
    u32 field_34;               
    u32 field_38;               
    u32 field_3c;               
    u32 field_40;               
    u32 field_44;               
    FSArchiveReadProc pRead;   
    FSArchiveWriteProc pWrite; 
    u32 field_50;                
} FSArchive;

extern int FSi_ReadMemCallback(char **arc, void *dst, u32 off, u32 len);

extern int FSi_WriteMemCallback(char **arc, const void *src, u32 off, u32 len);

BOOL FS_LoadArchive(FSArchive *arc, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5,
                     FSArchiveReadProc pRead, FSArchiveWriteProc pWrite)
{
    arc->base = p1;
    arc->field_30 = p3;
    arc->field_2c = arc->field_3c = p2;
    arc->field_38 = p5;
    arc->field_34 = arc->field_40 = p4;
    arc->pRead = pRead ? pRead : FSi_ReadMemCallback;
    arc->pWrite = pWrite ? pWrite : FSi_WriteMemCallback;
    arc->field_50 = (u32)arc->pRead;
    arc->field_44 = 0;
    arc->flag |= 2;
    return 1;
}
