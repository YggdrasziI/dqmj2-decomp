/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/mi.h"

#include "nitro/pxi.h"

#include "nitro/spi.h"

#include "nitro/rtc.h"

#include "nitro/snd.h"

#include "nitro/wm.h"

#include "nnsys/g3d.h"

typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;

typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);

typedef void (*MBCommPStateCallback) (u16 child_aid, u32 status, void * arg);

typedef void (*MBCommCStateCallbackFunc) (u32 status, void * arg);

typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);

typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);

extern NNSGfdFuncFreeTexVram data_020c69a4;

extern NNSGfdFuncFreePlttVram data_020c699c;

void NNS_G3dTexReleaseTexKey(NNSG3dResTex * pTex, NNSG3dTexKey * texKey, NNSG3dTexKey * tex4x4Key);

NNSG3dPlttKey NNS_G3dPlttReleasePlttKey(NNSG3dResTex * pTex);

void NNS_G3dReleaseMdlSet(NNSG3dResMdlSet * pMdlSet);

NNSG3dResMdlSet * NNS_G3dGetMdlSet(const NNSG3dResFileHeader * header);

NNSG3dResTex * NNS_G3dGetTex(const NNSG3dResFileHeader * header);

inline int NNS_GfdFreeTexVram (NNSGfdTexKey memKey)
{
    return (*data_020c69a4)(memKey);
}

inline int NNS_GfdFreePlttVram (NNSGfdPlttKey plttKey)
{
    return (*data_020c699c)(plttKey);
}

void NNS_G3dResDefaultRelease (void * pResData)
{
    u8 * binFile = (u8 *)pResData;
    BOOL failed = FALSE;

    switch (*(u32 *)&binFile[0]) {
    case NNS_G3D_SIGNATURE_NSBMD:
    {
        NNSG3dResTex * tex;
        NNSG3dResMdlSet * mdlSet = NNS_G3dGetMdlSet(pResData);
        tex = NNS_G3dGetTex((NNSG3dResFileHeader *) pResData);

        if (tex) {

            NNS_G3dReleaseMdlSet(mdlSet);
        }
    }

    case NNS_G3D_SIGNATURE_NSBTX:
    {
        NNSG3dResTex * tex;
        NNSG3dPlttKey plttKey;
        NNSG3dTexKey texKey, tex4x4Key;
        int status;
        tex = NNS_G3dGetTex((NNSG3dResFileHeader *) pResData);

        if (tex) {
            plttKey = NNS_G3dPlttReleasePlttKey(tex);
            NNS_G3dTexReleaseTexKey(tex, &texKey, &tex4x4Key);

            if (plttKey > 0) {
                status = NNS_GfdFreePlttVram(plttKey);
            }

            if (tex4x4Key > 0) {
                status = NNS_GfdFreeTexVram(tex4x4Key);
            }

            if (texKey > 0) {
                status = NNS_GfdFreeTexVram(texKey);
            }
        }
    }
    break;
    case NNS_G3D_SIGNATURE_NSBCA:
    case NNS_G3D_SIGNATURE_NSBVA:
    case NNS_G3D_SIGNATURE_NSBMA:
    case NNS_G3D_SIGNATURE_NSBTP:
    case NNS_G3D_SIGNATURE_NSBTA:
        break;
    default:
        break;
    };
}
