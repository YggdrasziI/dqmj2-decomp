/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#define reg_G3X_DISP3DCNT       (*(REGType16v *)REG_DISP3DCNT_ADDR)

#define reg_G2_BG0CNT           (*(REGType16v *)REG_BG0CNT_ADDR)

#define reg_G2_BG0OFS           (*(REGType32v *)REG_BG0OFS_ADDR)

#define reg_G3X_CLEAR_COLOR     (*(REGType32v *)REG_CLEAR_COLOR_ADDR)

#define reg_G3X_CLEAR_DEPTH     (*(REGType16v *)REG_CLEAR_DEPTH_ADDR)

#define reg_G3X_CLRIMAGE_OFFSET (*(REGType16v *)REG_CLRIMAGE_OFFSET_ADDR)

#define reg_G3X_FOG_COLOR       (*(REGType32v *)REG_FOG_COLOR_ADDR)

#define reg_G3X_FOG_OFFSET      (*(REGType16v *)REG_FOG_OFFSET_ADDR)

#define reg_G3_POLYGON_ATTR     (*(REGType32v *)REG_POLYGON_ATTR_ADDR)

#define reg_G3_TEXIMAGE_PARAM   (*(REGType32v *)REG_TEXIMAGE_PARAM_ADDR)

#define reg_G3_SHININESS        (*(REGType32v *)REG_SHININESS_ADDR)

#define reg_G3_END_VTXS         (*(REGType32v *)REG_END_VTXS_ADDR)

#define reg_G3X_GXSTAT          (*(REGType32v *)REG_GXSTAT_ADDR)

#define reg_G3X_ALPHA_TEST_REF  (*(REGType16v *)REG_ALPHA_TEST_REF_ADDR)

#define GX_DMA_NOT_USE          ((u32) ~0)

#define G3OP_MTX_MODE           0x10

#define G3OP_TEXPLTT_BASE       0x2b

#define GX_LIGHTMASK_NONE 0

#define GX_POLYGON_ATTR_MISC_NONE 0

#define GXi_DmaId data_020422b8

#define G2_BLENDTYPE_FADEIN  0x0080

#define G2_BLENDTYPE_FADEOUT 0x00c0

#include "nitro/fx.h"

#define reg_G3_MTX_MODE       (*(REGType32v *)0x4000440)

#define reg_G3_MTX_POP        (*(REGType32v *)0x4000448)

#define reg_G3_MTX_IDENTITY   (*(REGType32v *)0x4000454)

#define reg_G3_GXSTAT        (*(REGType32v *)0x4000600)

typedef enum { GX_SHADING_TOON = 0, GX_SHADING_HIGHLIGHT = 1 } GXShading;

typedef enum { GX_FIFOINTR_COND_DISABLE = 0, GX_FIFOINTR_COND_UNDERHALF = 1, GX_FIFOINTR_COND_EMPTY = 2 } GXFifoIntrCond;

typedef enum { GX_POLYGONMODE_MODULATE = 0 } GXPolygonMode;

typedef enum { GX_CULL_ALL = 0, GX_CULL_FRONT = 0x40, GX_CULL_BACK = 0x80, GX_CULL_NONE = 0xc0 } GXCull;

typedef enum { GX_TEXFMT_NONE = 0 } GXTexFmt;

typedef enum { GX_TEXGEN_NONE = 0 } GXTexGen;

typedef enum { GX_TEXSIZE_S8 = 0 } GXTexSizeS;

typedef enum { GX_TEXSIZE_T8 = 0 } GXTexSizeT;

typedef enum { GX_TEXREPEAT_NONE = 0 } GXTexRepeat;

typedef enum { GX_TEXFLIP_NONE = 0 } GXTexFlip;

typedef enum { GX_TEXPLTTCOLOR0_USE = 0 } GXTexPlttColor0;

extern u32 data_020422b8;

extern void G3X_ClearFifo(void);

extern void G3X_InitMtxStack(void);

extern void G3X_InitTable(void);

extern void func_020045d8(void);

extern void MI_DmaFill32Async(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg);

extern void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size);

extern void INITi_CpuClear32_0x01ff86fc(u32 data, void *destp, u32 size);

extern void GX_SendFifo48B(const void *src, void *dst);

extern void func_02008d0c(const void *src, void *dst);

extern void GXi_NopClearFifo128_(volatile unsigned int *fifo);

extern int G3X_GetMtxStackLevelPV(int *level);

extern int G3X_GetMtxStackLevelPJ(int *level);

extern void MI_Copy64B(const void *src, void *dst);

static inline BOOL G3X_IsGeometryBusy(void)
{
    return (BOOL)(reg_G3X_GXSTAT & REG_G3X_GXSTAT_GE_MASK);
}

static inline void G3_End(void)
{
    reg_G3_END_VTXS = 0;
}

static inline void G3X_ResetListRamOverflow(void)
{
    reg_G3X_DISP3DCNT |= REG_G3X_DISP3DCNT_GO_MASK;
}

static inline void G3X_ResetLineBufferUnderflow(void)
{
    reg_G3X_DISP3DCNT |= REG_G3X_DISP3DCNT_RO_MASK;
}

static inline void G3X_SetShading(GXShading shading)
{
    reg_G3X_DISP3DCNT = (u16)((reg_G3X_DISP3DCNT & ~(REG_G3X_DISP3DCNT_THS_MASK |
                                                     REG_G3X_DISP3DCNT_RO_MASK |
                                                     REG_G3X_DISP3DCNT_GO_MASK)) |
                              (shading << REG_G3X_DISP3DCNT_THS_SHIFT));
}

static inline void G3X_AntiAlias(BOOL enable)
{
    if (enable) {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK) |
                                  REG_G3X_DISP3DCNT_AAE_MASK);
    } else {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK |
                                    REG_G3X_DISP3DCNT_AAE_MASK));
    }
}

static inline void G3X_AlphaTest(BOOL enable, int ref)
{
    if (enable) {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK) |
                                  REG_G3X_DISP3DCNT_ATE_MASK);
        reg_G3X_ALPHA_TEST_REF = (u16)ref;
    } else {
        
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  (u16)~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK |
                                         REG_G3X_DISP3DCNT_ATE_MASK));
    }
}

static inline void G3X_ResetMtxStackOverflow(void)
{
    reg_G3X_GXSTAT |= REG_G3X_GXSTAT_SE_MASK;
}

static inline void G3X_SetFifoIntrCond(GXFifoIntrCond cond)
{
    reg_G3X_GXSTAT = ((reg_G3X_GXSTAT & ~REG_G3X_GXSTAT_FI_MASK) |
                      (cond << REG_G3X_GXSTAT_FI_SHIFT));
}

static inline void G2_SetBG0Priority(int priority)
{
    reg_G2_BG0CNT = (u16)((reg_G2_BG0CNT & ~REG_G2_BG0CNT_PRIORITY_MASK) | priority);
}

static inline void G3_Direct1(int op, u32 param0)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param0;
}

static inline void G3_PolygonAttr(int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc)
{
    reg_G3_POLYGON_ATTR = (u32)(light | (polyMode << REG_G3_POLYGON_ATTR_PM_SHIFT) | cullMode |
                                (polygonID << REG_G3_POLYGON_ATTR_ID_SHIFT) |
                                (alpha << REG_G3_POLYGON_ATTR_ALPHA_SHIFT) | misc);
}

static inline void G3_TexImageParam(GXTexFmt texFmt, GXTexGen texGen, GXTexSizeS s, GXTexSizeT t,
                                    GXTexRepeat repeat, GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr)
{
    reg_G3_TEXIMAGE_PARAM = (u32)(texFmt | texGen | s | t | repeat | flip | pltt0 | (addr >> 3));
}

void *G2_GetBG0ScrPtr(void) {
    int scrBase = (*(volatile unsigned short *)0x04000008 & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (scrBase << 11));
}

void *G2S_GetBG0ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}

void *G2_GetBG1ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400000a & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 11));
}

void *G2S_GetBG1ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}

void *G2_GetBG2ScrPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000c;
    unsigned base = ((*(volatile unsigned *)0x04000000 & 0x38000000) >> 27) << 16;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x06000000 + base + (slot << 11));
    case 5:
        if ((cnt & 0x80) != 0) {
            return (void *)(0x06000000 + (slot << 14));
        }
        return (void *)(0x06000000 + base + (slot << 11));
    case 6:
        return (void *)0x06000000;
    default:
        return 0;
    }
}

void *G2S_GetBG2ScrPtr(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x06200000 + (slot << 11));
    case 5:
        if ((cnt & 0x80) != 0) {
            slot <<= 14;
        } else {
            slot <<= 11;
        }
        return (void *)(0x06200000 + slot);
    case 6:
        return 0;
    default:
        return 0;
    }
}

void *G2_GetBG3ScrPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000e;
    unsigned base = ((*(volatile unsigned *)0x04000000 & 0x38000000) >> 27) << 16;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
        return (void *)(0x06000000 + base + (slot << 11));
    case 3:
    case 4:
    case 5:
        if ((cnt & 0x80) != 0) {
            return (void *)(0x06000000 + (slot << 14));
        }
        return (void *)(0x06000000 + base + (slot << 11));
    case 6:
        return 0;
    default:
        return 0;
    }
}

void *G2S_GetBG3ScrPtr(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100e;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
        return (void *)(0x06200000 + (slot << 11));
    case 3:
    case 4:
    case 5:
        if ((cnt & 0x80) != 0) {
            slot <<= 14;
        } else {
            slot <<= 11;
        }
        return (void *)(0x06200000 + slot);
    case 6:
        return 0;
    default:
        return 0;
    }
}

void *G2_GetBG0CharPtr(void) {
    int slot = (*(volatile unsigned short *)0x04000008 & 0x3c) >> 2;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 14));
}

void *G2S_GetBG0CharPtr(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}

void *G2_GetBG1CharPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400000a & 0x3c) >> 2;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 14));
}

void *G2S_GetBG1CharPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}

void *G2_GetBG2CharPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
        return (void *)(0x06000000 + (dispBase << 16) + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}

void *G2S_GetBG2CharPtr(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        return (void *)(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}

void *G2_GetBG3CharPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000e;
    if (mode < 3 || (mode < 6 && (cnt & 0x80) == 0)) {
        unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
        return (void *)(0x06000000 + (dispBase << 16) + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}

void *G2S_GetBG3CharPtr(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100e;
    if (mode < 3 || (mode < 6 && (cnt & 0x80) == 0)) {
        return (void *)(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}

void G2x_SetBlendAlpha_(unsigned int *r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int a5)
{
    *r0 = ((r1 | 0x40) | (r2 << 8)) | ((r3 | (a5 << 8)) << 16);
}

void G2x_SetBlendBrightness_(unsigned short *dst, unsigned int attr, int value)
{
    if (value < 0) {
        dst[0] = attr | 0xc0;
        dst[2] = -value;
    } else {
        dst[0] = attr | 0x80;
        dst[2] = value;
    }
}

void G2x_ChangeBlendBrightness_ (u32 addr, int brightness)
{
	u16 tmp;

	tmp = *((vu16 *)addr + 0);

	if (brightness < 0) {
		if (G2_BLENDTYPE_FADEIN == (tmp & REG_G2_BLDCNT_EFFECT_MASK)) {
			*((vu16 *)addr + 0) = (u16)((tmp & ~REG_G2_BLDCNT_EFFECT_MASK) | G2_BLENDTYPE_FADEOUT);
		}

		*((vu16 *)addr + 2) = (u16) - brightness;
	} else {
		if (G2_BLENDTYPE_FADEOUT == (tmp & REG_G2_BLDCNT_EFFECT_MASK)) {
			*((vu16 *)addr + 0) = (u16)((tmp & ~REG_G2_BLDCNT_EFFECT_MASK) | G2_BLENDTYPE_FADEIN);
		}

		*((vu16 *)addr + 2) = (u16)brightness;
	}
}

void G3_LoadMtx43(const MtxFx43 *m) {
    *(volatile unsigned int *)0x4000400 = 0x17;
    GX_SendFifo48B(m, (void *)0x4000400);
}

void G3_MultMtx43(const MtxFx43 *m) {
    *(volatile unsigned int *)0x4000400 = 0x19;
    GX_SendFifo48B(m, (void *)0x4000400);
}

void G3_MultMtx33(const MtxFx33 *m) {
    *(volatile unsigned int *)0x4000400 = 0x1a;
    func_02008d0c(m, (void *)0x4000400);
}

void G3X_Init (void)
{

	G3X_ClearFifo();
	G3_End();

	while ( G3X_IsGeometryBusy()) {
	}

	reg_G3X_DISP3DCNT = 0;
	reg_G3X_GXSTAT = 0;
	reg_G2_BG0OFS = 0;

	G3X_ResetListRamOverflow();
	G3X_ResetLineBufferUnderflow();
	G3X_SetShading(GX_SHADING_TOON);
	G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);

	G3X_ResetMtxStackOverflow();
	G3X_SetFifoIntrCond(GX_FIFOINTR_COND_EMPTY);
	G3X_InitMtxStack();

	reg_G3X_CLEAR_COLOR = 0;
	reg_G3X_CLEAR_DEPTH = 0x7fff;
	reg_G3X_CLRIMAGE_OFFSET = 0;
	reg_G3X_FOG_COLOR = 0;
	reg_G3X_FOG_OFFSET = 0;

	G2_SetBG0Priority(0);
	G3X_InitTable();
	G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_BACK, 0, 31, GX_POLYGON_ATTR_MISC_NONE);

	G3_TexImageParam(GX_TEXFMT_NONE,
	                 GX_TEXGEN_NONE,
	                 GX_TEXSIZE_S8, GX_TEXSIZE_T8, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, 0);

	G3_Direct1(G3OP_TEXPLTT_BASE, 0);
}

void G3X_ResetMtxStack (void)
{

	while (G3X_IsGeometryBusy()) {
	}

	G3X_ResetMtxStackOverflow();
	G3X_ResetListRamOverflow();
	G3X_ResetLineBufferUnderflow();
	func_020045d8();

	G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_BACK, 0, 31,
	               GX_POLYGON_ATTR_MISC_NONE);

	G3_TexImageParam(GX_TEXFMT_NONE,
	                 GX_TEXGEN_NONE,
	                 GX_TEXSIZE_S8, GX_TEXSIZE_T8, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE,
	                 GX_TEXPLTTCOLOR0_USE, 0);

	G3_Direct1(G3OP_TEXPLTT_BASE, 0);
}

void G3X_ClearFifo(void) {
    GXi_NopClearFifo128_((volatile unsigned int *)0x4000400);
    while (*(volatile unsigned int *)0x4000600 & 0x8000000) {
        ;
    }
}

void G3X_InitMtxStack(void) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    int levelPV;
    int levelPJ;

    *gxstat = *gxstat | 0x8000;

    while (G3X_GetMtxStackLevelPV(&levelPV) != 0) {}
    while (G3X_GetMtxStackLevelPJ(&levelPJ) != 0) {}

    reg_G3_MTX_MODE = 3;
    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 0;

    if (levelPJ != 0) {
        reg_G3_MTX_POP = levelPJ;
    }

    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 2;
    reg_G3_MTX_POP = levelPV;
    reg_G3_MTX_IDENTITY = 0;
}

void func_020045d8(void) {
    int pvLevel;
    int pjLevel;

    reg_G3_GXSTAT |= 0x8000;

    while (G3X_GetMtxStackLevelPV(&pvLevel) != 0) {}
    while (G3X_GetMtxStackLevelPJ(&pjLevel) != 0) {}

    reg_G3_MTX_MODE = 3;
    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 0;

    if (pjLevel != 0) {
        reg_G3_MTX_POP = pjLevel;
    }

    reg_G3_MTX_MODE = 2;
    reg_G3_MTX_POP = pvLevel;
    reg_G3_MTX_IDENTITY = 0;
}

int G3X_GetClipMtx(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    MI_Copy64B((const void *)(gxstat + 0x10), dst);
    return 0;
}

int G3X_GetVectorMtx(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    func_02008d0c((const void *)(gxstat + 0x20), dst);
    return 0;
}
