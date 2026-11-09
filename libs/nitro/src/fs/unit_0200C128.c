/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nitro/fs.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

extern FSResult (*const (data_0204185c[]))(FSFile *);

static inline BOOL FS_IsBusy (volatile const FSFile * p_file)
{
    return (p_file->stat & 0x00000001 ) ? 1 : 0 ;
}

void FS_CancelFile (FSFile *p_file)
{

	{
		OSIntrMode bak_psr = OS_DisableInterrupts();

		if (FS_IsBusy(p_file)) {
			p_file->stat |= FS_FILE_STATUS_CANCEL;
			p_file->arc->flag |= FS_ARCHIVE_FLAG_CANCELING;
		}

		(void)OS_RestoreInterrupts(bak_psr);
	}
}
