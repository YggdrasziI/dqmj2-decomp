/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

/* used by header macros under the reference's names */
#define GX_ResetBankForOBJExtPltt func_02003b40

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

extern u32 data_020422b8;

#define GXi_DmaId data_020422b8

extern void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

extern void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg);

extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

extern GXVRamBGExtPltt GX_ResetBankForBGExtPltt(void);

extern GXVRamOBJExtPltt func_02003b40(void);

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
    u32 sSubBGExtPltt;            
    u32 sOBJExtPlttLCDCBlk;       
    GXVRamOBJExtPltt sOBJExtPltt; 
    u32 sBGExtPlttLCDCOffset;     
    u32 sBGExtPlttLCDCBlk;        
    GXVRamBGExtPltt sBGExtPltt;   
    u32 sSubOBJExtPltt;           
} data_020cbc20;

#define sOBJExtPlttLCDCBlk data_020cbc20.sOBJExtPlttLCDCBlk

#define sOBJExtPltt data_020cbc20.sOBJExtPltt

#define sBGExtPlttLCDCOffset data_020cbc20.sBGExtPlttLCDCOffset

#define sBGExtPlttLCDCBlk data_020cbc20.sBGExtPlttLCDCBlk

#define sBGExtPltt data_020cbc20.sBGExtPltt

void GX_BeginLoadOBJExtPltt (void)
{

	sOBJExtPltt = func_02003b40();

	switch (sOBJExtPltt) {
	case GX_VRAM_OBJEXTPLTT_0_F:
		sOBJExtPlttLCDCBlk = HW_LCDC_VRAM_F;
		break;
	case GX_VRAM_OBJEXTPLTT_0_G:
		sOBJExtPlttLCDCBlk = HW_LCDC_VRAM_G;
		break;
	case GX_VRAM_OBJEXTPLTT_NONE:
		break;
	default:
		break;
	}
}
