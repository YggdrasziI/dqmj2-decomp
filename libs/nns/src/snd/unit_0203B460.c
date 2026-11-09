/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

extern void ForceStopStrm(NNSSndStrm * stream);

extern void ForceStopStrm (NNSSndStrm * stream);

void NNS_SndStrmStop (NNSSndStrm * stream)
{

    if (!stream->activeFlag) return;

    ForceStopStrm(stream);
}
