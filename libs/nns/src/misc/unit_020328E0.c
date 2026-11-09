/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

#include "nnsys/g3d.h"

extern BOOL getRotDataByIdx_(MtxFx33 *pRot, const void *pArrayRot3,
                          const void *pArrayRot5, u32 info);

extern void Vec_Normalize(const VecFx32 *src, VecFx32 *dst);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    fx32 x, y, z;
    x = (a->y * b->z - a->z * b->y) >> 12;
    y = (a->z * b->x - a->x * b->z) >> 12;
    z = (a->x * b->y - a->y * b->x) >> 12;
    axb->x = x;
    axb->y = y;
    axb->z = z;
}

void func_020328e0(fx32 *s_invs, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    u32 frame = (u32)(Frame >> 12);
    const void *pArray = (const void *)((u8 *)pJntAnm + *(pData + 1));
    u32 info = *pData;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto SCALE_NONINTERP;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto SCALE_NONINTERP;
            } else {
                idx = frame >> 1;
                goto SCALE_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto SCALE_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto SCALE_NONINTERP;
            }

            if (frame & 1) {
                fx32 v, v_sub;
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                if (info & 0x20000000) {
                    const fx16 *p_fx16 = (const fx16 *)pArray;
                    v = *(p_fx16 + 2 * idx);
                    v_sub = *(p_fx16 + 2 * idx_sub);
                    s_invs[0] = (v + (v << 1) + v_sub) >> 2;

                    v = *(p_fx16 + 2 * idx + 1);
                    v_sub = *(p_fx16 + 2 * idx_sub + 1);
                    s_invs[1] = (v + (v << 1) + v_sub) >> 2;
                } else {
                    const fx32 *p_fx32 = (const fx32 *)pArray;
                    v = *(p_fx32 + 2 * idx);
                    v_sub = *(p_fx32 + 2 * idx_sub);
                    s_invs[0] = (fx32)(((fx64)v + v + v + v_sub) >> 2);

                    v = *(p_fx32 + 2 * idx + 1);
                    v_sub = *(p_fx32 + 2 * idx_sub + 1);
                    s_invs[1] = (fx32)(((fx64)v + v + v + v_sub) >> 2);
                }
                return;
            } else {
                idx = frame >> 2;
                goto SCALE_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto SCALE_NONINTERP;
        }
    }

SCALE_NONINTERP:
    if (info & 0x20000000) {
        const fx16 *p_fx16 = (const fx16 *)pArray;
        s_invs[0] = *(p_fx16 + 2 * idx);
        s_invs[1] = *(p_fx16 + 2 * idx + 1);
    } else {
        const fx32 *p_fx32 = (const fx32 *)pArray;
        s_invs[0] = *(p_fx32 + 2 * idx);
        s_invs[1] = *(p_fx32 + 2 * idx + 1);
    }
    return;

SCALE_INTERP_2:
    if (info & 0x20000000) {
        const fx16 *p_fx16 = (const fx16 *)pArray;
        s_invs[0] = (*(p_fx16 + 2 * idx) + *(p_fx16 + 2 * idx + 2)) >> 1;
        s_invs[1] = (*(p_fx16 + 2 * idx + 1) + *(p_fx16 + 2 * idx + 3)) >> 1;
    } else {
        const fx32 *p_fx32 = (const fx32 *)pArray;
        s_invs[0] = (*(p_fx32 + 2 * idx) + (*(p_fx32 + 2 * idx + 2))) >> 1;
        s_invs[1] = (*(p_fx32 + 2 * idx + 1) + (*(p_fx32 + 2 * idx + 3))) >> 1;
    }
}

void func_02032ac8(fx32 *s_invs, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    u32 info = *pData;
    u32 last_interp;
    u32 idx0, idx1;
    fx32 remainder;
    int step;
    u32 step_shift;
    u32 frame;

    frame = (u32)(Frame >> 12);

    if (frame == pJntAnm->numFrame - 1) {
        if (!(info & 0xc0000000)) {
            idx0 = frame;
        } else if (info & 0x40000000) {
            idx0 = (frame >> 1) + (frame & 1);
        } else {
            idx0 = (frame >> 2) + (frame & 3);
        }

        if (pJntAnm->flag & 2) {
            idx1 = 0;
            goto SCALE_EX_0_1;
        } else {
            if (info & 0x20000000) {
                const fx16 *p_fx16 = (const fx16 *)pArray;
                s_invs[0] = *(p_fx16 + 2 * idx0);
                s_invs[1] = *(p_fx16 + 2 * idx0 + 1);
            } else {
                const fx32 *p_fx32 = (const fx32 *)pArray;
                s_invs[0] = *(p_fx32 + 2 * idx0);
                s_invs[1] = *(p_fx32 + 2 * idx0 + 1);
            }
            return;
        }
    }

    if (!(info & 0xc0000000)) {
        goto SCALE_EX_0;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame >= last_interp) {
            idx0 = last_interp >> 1;
            idx1 = idx0 + 1;
            goto SCALE_EX_0_1;
        } else {
            idx0 = frame >> 1;
            idx1 = idx0 + 1;
            remainder = Frame & (0x1000 * 2 - 1);
            step = 2;
            step_shift = 1;
            goto SCALE_EX;
        }
    } else {
        if (frame >= last_interp) {
            idx0 = (frame >> 2) + (frame & 3);
            idx1 = idx0 + 1;
            goto SCALE_EX_0_1;
        } else {
            idx0 = frame >> 2;
            idx1 = idx0 + 1;
            remainder = Frame & (0x1000 * 4 - 1);
            step = 4;
            step_shift = 2;
            goto SCALE_EX;
        }
    }

SCALE_EX_0:
    idx0 = (u32)frame;
    idx1 = idx0 + 1;
SCALE_EX_0_1:
    remainder = Frame & (0x1000 - 1);
    step = 1;
    step_shift = 0;
SCALE_EX:
    {
        fx32 s0, s1;
        fx32 inv0, inv1;

        if (info & 0x20000000) {
            const fx16 *p_fx16 = (const fx16 *)pArray;
            s0 = *(p_fx16 + 2 * idx0);
            inv0 = *(p_fx16 + 2 * idx0 + 1);
            s1 = *(p_fx16 + 2 * idx1);
            inv1 = *(p_fx16 + 2 * idx1 + 1);
        } else {
            const fx32 *p_fx32 = (const fx32 *)pArray;
            s0 = *(p_fx32 + 2 * idx0);
            inv0 = *(p_fx32 + 2 * idx0 + 1);
            s1 = *(p_fx32 + 2 * idx1);
            inv1 = *(p_fx32 + 2 * idx1 + 1);
        }

        s_invs[0] = ((s0 * step) + (((s1 - s0) * remainder) >> 12)) >> step_shift;
        s_invs[1] = ((inv0 * step) + (((inv1 - inv0) * remainder) >> 12)) >> step_shift;
    }
}

void func_02032c5c(MtxFx33 *pRot, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    u32 frame = (u32)(Frame >> 12);
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    const void *pArrayRot3 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot3);
    const void *pArrayRot5 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot5);
    u32 info = *pData;
    const u16 *p = (const u16 *)pArray;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto ROT_NONINTERP;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto ROT_NONINTERP;
            } else {
                idx = frame >> 1;
                goto ROT_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto ROT_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto ROT_NONINTERP;
            }

            if (frame & 1) {
                MtxFx33 tmp;
                BOOL doCross = 0;
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                doCross |= getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, p[idx]);
                doCross |= getRotDataByIdx_(&tmp, pArrayRot3, pArrayRot5, p[idx_sub]);

                pRot->_00 = (pRot->_00 * 3 + tmp._00) >> 0;
                pRot->_01 = (pRot->_01 * 3 + tmp._01) >> 0;
                pRot->_02 = (pRot->_02 * 3 + tmp._02) >> 0;
                pRot->_10 = (pRot->_10 * 3 + tmp._10) >> 0;
                pRot->_11 = (pRot->_11 * 3 + tmp._11) >> 0;
                pRot->_12 = (pRot->_12 * 3 + tmp._12) >> 0;

                Vec_Normalize((VecFx32 *)&pRot->_00, (VecFx32 *)&pRot->_00);
                Vec_Normalize((VecFx32 *)&pRot->_10, (VecFx32 *)&pRot->_10);

                if (!doCross) {
                    pRot->_20 = (pRot->_20 * 3 + tmp._20) >> 0;
                    pRot->_21 = (pRot->_21 * 3 + tmp._21) >> 0;
                    pRot->_22 = (pRot->_22 * 3 + tmp._22) >> 0;
                    Vec_Normalize((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
                } else {
                    vecCross_((const VecFx32 *)&pRot->_00,
                              (const VecFx32 *)&pRot->_10,
                              (VecFx32 *)&pRot->_20);
                }
                return;
            } else {
                idx = frame >> 2;
                goto ROT_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto ROT_NONINTERP;
        }
    }

ROT_INTERP_2:
    {
        MtxFx33 tmp;
        BOOL doCross = 0;
        doCross |= getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, p[idx]);
        doCross |= getRotDataByIdx_(&tmp, pArrayRot3, pArrayRot5, p[idx + 1]);

        pRot->_00 = (pRot->_00 + tmp._00) >> 0;
        pRot->_01 = (pRot->_01 + tmp._01) >> 0;
        pRot->_02 = (pRot->_02 + tmp._02) >> 0;
        pRot->_10 = (pRot->_10 + tmp._10) >> 0;
        pRot->_11 = (pRot->_11 + tmp._11) >> 0;
        pRot->_12 = (pRot->_12 + tmp._12) >> 0;

        Vec_Normalize((VecFx32 *)&pRot->_00, (VecFx32 *)&pRot->_00);
        Vec_Normalize((VecFx32 *)&pRot->_10, (VecFx32 *)&pRot->_10);

        if (!doCross) {
            pRot->_20 = (pRot->_20 + tmp._20) >> 0;
            pRot->_21 = (pRot->_21 + tmp._21) >> 0;
            pRot->_22 = (pRot->_22 + tmp._22) >> 0;
            Vec_Normalize((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
        } else {
            vecCross_((const VecFx32 *)&pRot->_00,
                      (const VecFx32 *)&pRot->_10,
                      (VecFx32 *)&pRot->_20);
        }
        return;
    }

ROT_NONINTERP:
    if (getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, p[idx])) {
        vecCross_((const VecFx32 *)&pRot->_00,
                  (const VecFx32 *)&pRot->_10,
                  (VecFx32 *)&pRot->_20);
    } else {
        Vec_Normalize((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
    }
}
