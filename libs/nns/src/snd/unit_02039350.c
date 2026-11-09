/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

extern OSIntrMode OS_DisableInterrupts(void);

extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

NNSSndArc * func_0203896c(NNSSndArc * arc);

void * NNS_SndArcGetFileAddress(u32 fileId);

void NNS_SndArcSetFileAddress(u32 fileId, void * address);

void DisposeCallback (void * mem, NNSSndArc * arc, u32 fileId)
{
    NNSSndArc * oldArc;
    OSIntrMode old;

    if (arc == NULL) return;

    old = OS_DisableInterrupts();
    oldArc = func_0203896c(arc);

    if (mem == NNS_SndArcGetFileAddress(fileId)) {
        NNS_SndArcSetFileAddress(fileId, NULL);
    }

    (void)func_0203896c(oldArc);
    (void)OS_RestoreInterrupts(old);
}
