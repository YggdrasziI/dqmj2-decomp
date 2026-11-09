/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

/* used by header macros under the reference's names */
#define GX_ResetBankForTex func_02003b64

typedef int GXVRamTex;

extern GXVRamTex func_02003b64(void);

extern const struct {
    u16 blk1;
    u16 blk2;
    u16 szBlk1;
} data_020c0f24[16];

#define sTexStartAddrTable data_020c0f24

extern struct {
    u32 pad0;                     
    u32 sTexLCDCBlk1;             
    u32 sTexPlttLCDCBlk;          
    int sTexPltt;                 
    u32 pad10;                    
    GXVRamTex sTex;               
    u32 sTexLCDCBlk2;             
    u32 sSzTexBlk1;               
} data_020cbc3c;

#define sTexLCDCBlk1 data_020cbc3c.sTexLCDCBlk1

#define sTex data_020cbc3c.sTex

#define sTexLCDCBlk2 data_020cbc3c.sTexLCDCBlk2

#define sSzTexBlk1 data_020cbc3c.sSzTexBlk1

void GX_BeginLoadTex(void)
{
    sTex = func_02003b64();

    sTexLCDCBlk1 = (u32)(sTexStartAddrTable[sTex].blk1 << 12);
    sTexLCDCBlk2 = (u32)(sTexStartAddrTable[sTex].blk2 << 12);
    sSzTexBlk1 = (u32)(sTexStartAddrTable[sTex].szBlk1 << 12);
}
