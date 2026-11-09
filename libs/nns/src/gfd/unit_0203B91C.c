/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nnsys/gfd.h"

typedef struct {
    NNSGfdFrmTexRegionState *p4x4[2];    
    NNSGfdFrmTexRegionState *pNrm[5];    
} FrmTexSearchArrays;

extern NNSGfdFrmTexRegionState data_020c6920[];

extern FrmTexSearchArrays data_020c6904;

void NNSi_GfdSetTexNrmSearchArray(int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th) {
    data_020c6904.pNrm[0] = &data_020c6920[idx1st];
    data_020c6904.pNrm[1] = &data_020c6920[idx2nd];
    data_020c6904.pNrm[2] = &data_020c6920[idx3rd];
    data_020c6904.pNrm[3] = &data_020c6920[idx4th];
    data_020c6904.pNrm[4] = &data_020c6920[idx5th];
}
