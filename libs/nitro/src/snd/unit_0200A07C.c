/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/snd.h"

SNDInstPos SND_GetFirstInstDataPos(const SNDBankData *bank)
{
    SNDInstPos pos;
    (void)bank;
    pos.prgNo = 0;
    pos.index = 0;
    return pos;
}
