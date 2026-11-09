/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/fx_types.h"

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
} NNSG3dJntAnmResult;

typedef struct NNSG3dJointScale {
    VecFx32 scale;
    VecFx32 inverseScale;
} NNSG3dJointScale;

typedef struct NNSG3dSbcNodeDesc {
    u8 opcode;
    u8 nodeId;
    u8 parentId;
    u8 flags;
} NNSG3dSbcNodeDesc;

typedef struct NNSG3dRenderState {
    u8 pad000[0xc4];
    u32 scaleCacheFlags[8];
} NNSG3dRenderState;

enum {
    JNT_SCALE_ONE = 0x01,
    JNT_SCALEEX0_ONE = 0x08,
    JNT_SCALE_READY = 0x10,
    JNT_MAYA_SSC = 0x20,
    NODEDESC_PARENT = 0x01,
    NODEDESC_STORE_SCALE = 0x02,
    NODEDESC_SKIP_SCALE = 0x04
};

extern NNSG3dRenderState *data_020d6af4;

extern u8 data_020d7904[];

extern u8 data_020d7908[];

extern u8 data_020d790c[];

void func_0202c430(NNSG3dJntAnmResult *result,
                   const NNSG3dJointScale *jointScale,
                   const NNSG3dSbcNodeDesc *command,
                   u32 options)
{
    u8 commandFlags = command->flags;

    if (options & NODEDESC_SKIP_SCALE) {
        result->flag |= JNT_SCALE_ONE;
        if (commandFlags & NODEDESC_STORE_SCALE) {
            u8 nodeId = command->nodeId;
            data_020d6af4->scaleCacheFlags[(u32)nodeId >> 5] |=
                1 << (nodeId & 0x1f);
        }
    } else {
        result->scale.x = jointScale->scale.x;
        result->scale.y = jointScale->scale.y;
        result->scale.z = jointScale->scale.z;
        if (commandFlags & NODEDESC_STORE_SCALE) {
            u8 nodeId = command->nodeId;
            int offset = (u16)nodeId * sizeof(NNSG3dJointScale);

            data_020d6af4->scaleCacheFlags[(u32)nodeId >> 5] &=
                ~(1 << (nodeId & 0x1f));
            *(fx32 *)(data_020d7904 + offset) = jointScale->inverseScale.x;
            *(fx32 *)(data_020d7908 + offset) = jointScale->inverseScale.y;
            *(fx32 *)(data_020d790c + offset) = jointScale->inverseScale.z;
        }
    }

    if (commandFlags & NODEDESC_PARENT) {
        u8 parentId = command->parentId;

        result->flag |= JNT_MAYA_SSC;
        if (data_020d6af4->scaleCacheFlags[(u32)parentId >> 5] &
            (1 << (parentId & 0x1f))) {
            result->flag |= JNT_SCALEEX0_ONE;
        } else {
            result->scaleEx0 = *(VecFx32 *)(data_020d7904 +
                parentId * sizeof(NNSG3dJointScale));
        }
    }

    result->flag |= JNT_SCALE_READY;
}
