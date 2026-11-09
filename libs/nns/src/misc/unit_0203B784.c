/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nnsys/gfd.h"

extern NNSGfdFrmPlttVramManager data_020dea50;

static inline u32 NNSi_GfdGetPlttKeyRoundupSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_PLTTSIZE_MIN;
    } else {
        return (size + 7) & ~7;
    }
}

static inline NNSGfdPlttKey NNS_GfdMakePlttKey(u32 addr, u32 size)
{
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    return ((size >> 3) << 16) | (0xffff & (addr >> 3));
}

static inline u32 GetUpperSideAlignmentSize_(u32 addr, BOOL b4Pltt)
{
    if (b4Pltt) {
        return 7 & (8 - (addr & 7));
    } else {
        return 0xf & (0x10 - (addr & 0xf));
    }
}

static inline u32 GetLowerSideAlignmentSize_(u32 addr, BOOL b4Pltt)
{
    if (b4Pltt) {
        return addr & 7;
    } else {
        return addr & 0xf;
    }
}

static inline u32 GetCapacity_(void)
{
    (void)0;
    return data_020dea50.hiAddr - data_020dea50.loAddr;
}

static inline BOOL AllocFromLo_(u32 szByte, BOOL b4Pltt, u32 *pResAddr)
{
    const u32 addr = data_020dea50.loAddr;
    const u32 alignment = GetUpperSideAlignmentSize_(addr, b4Pltt);
    const u32 increase = szByte + alignment;

    (void)0;
    (void)0;

    if (GetCapacity_() >= increase) {
        const u32 tail = data_020dea50.loAddr + increase;

        if (b4Pltt) {
            if (tail > NNS_GFD_4PLTT_MAX_ADDR) {
                return FALSE;
            }
        }

        *pResAddr = data_020dea50.loAddr + alignment;
        data_020dea50.loAddr += increase;
        return TRUE;
    } else {
        return FALSE;
    }
}

static inline BOOL AllocFromHi_(u32 szByte, BOOL b4Pltt, u32 *pResAddr)
{
    (void)0;
    (void)0;

    if (data_020dea50.hiAddr >= szByte) {
        const u32 addr = data_020dea50.hiAddr - szByte;
        const u32 alignment = GetLowerSideAlignmentSize_(addr, b4Pltt);
        const u32 increase = szByte + alignment;

        if (GetCapacity_() >= increase) {
            const u32 tail = data_020dea50.hiAddr;

            if (b4Pltt) {
                if (tail > NNS_GFD_4PLTT_MAX_ADDR) {
                    return FALSE;
                }
            }

            data_020dea50.hiAddr -= increase;
            *pResAddr = data_020dea50.hiAddr;
            return TRUE;
        }
    }
    return FALSE;
}

NNSGfdPlttKey func_0203b784(u32 szByte, BOOL bPltt4, u32 allocFrom)
{
    u32 addr = 0;
    BOOL result = FALSE;

    (void)0;
    {
        szByte = NNSi_GfdGetPlttKeyRoundupSize(szByte);
        if (szByte >= NNS_GFD_PLTTSIZE_MAX) {
            (void)0;
            return NNS_GFD_ALLOC_ERROR_PLTTKEY;
        }
        (void)0;
    }

    if (allocFrom == NNS_GFD_ALLOC_FROM_LOW) {
        result = AllocFromLo_(szByte, bPltt4, &addr);
    } else {
        result = AllocFromHi_(szByte, bPltt4, &addr);
    }

    if (result) {
        return NNS_GfdMakePlttKey(addr, szByte);
    }
    (void)0;
    return NNS_GFD_ALLOC_ERROR_PLTTKEY;
}
