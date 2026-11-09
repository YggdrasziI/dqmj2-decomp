/* NitroSDK; built from twewy (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include <nitro/gx/gx.h>

#include <nitro/gx/gx_state.h>

#include <nitro/reg.h>

extern GXState data_020cbc04;

void GX_InitGxState(void);

void GX_VRAMCNT_SetLCDC_(u32 lcdc);

void GX_SetBankForBg(GXVRam bg);

void GX_SetBankForObj(GXVRam obj);

void GX_SetBankForBgExtPltt(GXVRam bgExtPltt);

void GX_SetBankForObjExtPltt(GXVRam objExtPltt);

void GX_SetBankForTex(GXVRam tex);

void GX_SetBankForTexPltt(GXVRam texPltt);

void GX_SetBankForLcdc(GXVRam lcdc);

void GX_SetBankForSubBg(GXVRam subBg);

void GX_SetBankForSubObj(GXVRam subObj);

void GX_SetBankForSubBgExtPltt(GXVRam subBgExtPltt);

void GX_SetBankForSubObjExtPltt(GXVRam subObjExtPltt);

GXVRam ResetBank(u16* bank);

GXVRam GX_ResetBankForBgExtPltt(void);

GXVRam GX_ResetBankForObjExtPltt(void);

GXVRam GX_ResetBankForTex(void);

GXVRam GX_ResetBankForTexPltt(void);

GXVRam GX_ResetBankForClearImage(void);

GXVRam GX_ResetBankForSubBg(void);

GXVRam GX_ResetBankForSubObj(void);

GXVRam GX_ResetBankForSubBgExtPltt(void);

GXVRam GX_ResetBankForSubObjExtPltt(void);

GXVRam DisableBank(u16* bank);

GXVRam GX_DisableBankForBg(void);

GXVRam GX_DisableBankForObj(void);

GXVRam GX_DisableBankForObjExtPltt(void);

GXVRam GX_DisableBankForTex(void);

GXVRam GX_DisableBankForTexPltt(void);

GXVRam GX_DisableBankForLcdc(void);

GXVRam GX_GetBankForBg(void);

GXVRam GX_GetBankForObj(void);

GXVRam GX_GetBankForBgExtPltt(void);

GXVRam GX_GetBankForObjExtPltt(void);

GXVRam GX_GetBankForTex(void);

GXVRam GX_GetBankForSubBg(void);

GXVRam GX_GetBankForSubObj(void);

GXVRam GX_GetBankForSubBgExtPltt(void);

GXVRam GX_GetBankForSubObjExtPltt(void);

u32 GetBankSize(u32 vram);

u32 GX_GetSizeOfBg(void);

u32 GX_GetSizeOfSubBg(void);

void GX_SetBankForClearImage(GXVRam clearImage) {
    data_020cbc04.lcdc       = (~clearImage & (data_020cbc04.lcdc | data_020cbc04.clearImage));
    data_020cbc04.clearImage = clearImage;

    switch (clearImage) {
        case GX_VRAM_AB:
            REG_VRAM_CNT_A = 147;
        case GX_VRAM_B:
            REG_VRAM_CNT_B = 155;
            REG_DISP3DCNT |= 0x4000;
            break;

        case GX_VRAM_CD:
            REG_VRAM_CNT_C = 147;
        case GX_VRAM_D:
            REG_VRAM_CNT_D = 155;
            REG_DISP3DCNT |= 0x4000;
            break;

        case GX_VRAM_NONE:
            REG_DISP3DCNT &= ~0x4000;
            break;

        case GX_VRAM_A:
            REG_VRAM_CNT_A = 155;
            REG_DISP3DCNT |= 0x4000;
            break;

        case GX_VRAM_C:
            REG_VRAM_CNT_C = 155;
            REG_DISP3DCNT |= 0x4000;
            break;

        default:
            break;
    }
    GX_VRAMCNT_SetLCDC_(data_020cbc04.lcdc);
}
