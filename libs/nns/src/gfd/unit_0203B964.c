/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nnsys/gfd.h"

extern NNSGfdFuncAllocTexVram data_020c69a0;

extern NNSGfdFuncFreeTexVram data_020c69a4;

void NNSi_GfdSetTexNrmSearchArray(int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);

NNSGfdTexKey NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4comp, u32 opt);

int func_0203bbd0(NNSGfdTexKey memKey);

void NNS_GfdResetFrmTexVramState(void);

extern NNSGfdFrmTexVramMnager data_020dea5c;

extern void NNSi_GfdSetTexNrmSearchArray (int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);

extern void NNS_GfdResetFrmTexVramState (void);

extern NNSGfdTexKey NNS_GfdAllocFrmTexVram (u32 szByte, BOOL is4x4comp, u32 opt);

extern int func_0203bbd0 (NNSGfdTexKey texKey);

void NNS_GfdInitFrmTexVramManager (u16 numSlot, BOOL useAsDefault)
{

    if ( numSlot <= 2 ) {
        NNSi_GfdSetTexNrmSearchArray(4, 3, 2, 0, 1);
    } else {
        NNSi_GfdSetTexNrmSearchArray(4, 3, 0, 2, 1);
    }

    data_020dea5c.numSlot = numSlot;
    NNS_GfdResetFrmTexVramState();

    if (useAsDefault) {
        data_020c69a0 = NNS_GfdAllocFrmTexVram;
        data_020c69a4 = func_0203bbd0;
    }
}
