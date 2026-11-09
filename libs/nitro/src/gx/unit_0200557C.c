/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#define GX_DMA_NOT_USE      ((u32) ~0)

#define GX_CPU_FASTER32_SIZE 0x30

typedef enum {
    GX_VRAM_BGEXTPLTT_NONE    = 0x0000,
    GX_VRAM_BGEXTPLTT_01_F    = 0x0020,
    GX_VRAM_BGEXTPLTT_23_G    = 0x0040,
    GX_VRAM_BGEXTPLTT_0123_E  = 0x0010,
    GX_VRAM_BGEXTPLTT_0123_FG = 0x0060
} GXVRamBGExtPltt;

typedef enum {
    GX_VRAM_OBJEXTPLTT_NONE = 0x0000,
    GX_VRAM_OBJEXTPLTT_0_F  = 0x0020,
    GX_VRAM_OBJEXTPLTT_0_G  = 0x0040
} GXVRamOBJExtPltt;

typedef int GXVRamTex;

extern u32 data_020c5ca4;

#define GXi_DmaId data_020c5ca4

extern void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

extern void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg);

extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

extern GXVRamBGExtPltt GX_ResetBankForBGExtPltt(void);

extern GXVRamOBJExtPltt GX_ResetBankForOBJExtPltt(void);

static inline void *G2_GetOBJCharPtr(void) { return (void *)HW_OBJ_VRAM; }

static inline void *G2S_GetOBJCharPtr(void) { return (void *)HW_DB_OBJ_VRAM; }

#define GX_RegionCheck_OBJ(a, b)

#define GX_RegionCheck_SubOBJ(a, b)

#define GX_RegionCheck_Tex(t, a, b)

static inline void GXi_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    if (dmaNo != GX_DMA_NOT_USE && size > GX_CPU_FASTER32_SIZE) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

static inline void GXi_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size,
                                      MIDmaCallback callback, void *arg)
{
    if (dmaNo != GX_DMA_NOT_USE) {
        MI_DmaCopy32Async(dmaNo, src, dest, size, callback, arg);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

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

void GX_LoadTex (const void *pSrc, u32 destSlotAddr, u32 szByte)
{
	void *pLCDC;

	GX_RegionCheck_Tex(sTex, destSlotAddr, destSlotAddr + szByte);

	if (0 == sTexLCDCBlk2) {
		pLCDC = (void *)(sTexLCDCBlk1 + destSlotAddr);
	} else {
		if (destSlotAddr + szByte < sSzTexBlk1) {
			pLCDC = (void *)(sTexLCDCBlk1 + destSlotAddr);
		} else if (destSlotAddr >= sSzTexBlk1)   {
			pLCDC = (void *)(sTexLCDCBlk2 + destSlotAddr - sSzTexBlk1);
		} else {
			void *pLCDC2 = (void *)sTexLCDCBlk2;
			u32 sz = sSzTexBlk1 - destSlotAddr;
			pLCDC = (void *)(sTexLCDCBlk1 + destSlotAddr);

			GXi_DmaCopy32(GXi_DmaId, pSrc, pLCDC, sz);
			GXi_DmaCopy32Async(GXi_DmaId, (void *)((u8 *)pSrc + sz), pLCDC2, szByte - sz, NULL, NULL);
			return;
		}
	}

	GXi_DmaCopy32Async(GXi_DmaId, pSrc, pLCDC, szByte, NULL, NULL);
}
