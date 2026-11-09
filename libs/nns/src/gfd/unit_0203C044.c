/* NitroSystem; built from khdays-decomp (CC0) per-function sources, edited where this
 * build differs (comments below). File bounds are a hypothesis. */
#pragma force_active on

/* The GFX command queue (0x14 bytes; GFXi_EnqueueCommand reads +0x10). Defined here:
 * mwcc then stores through one pool word and passes the address through a second
 * one, as in the ROM (khdays-decomp uses a second symbol instead). This unit owns its
 * .bss (0x020DEA60-0x020DEA74). */
typedef struct {
    int word0;      /* 0x00 */
    int word4;      /* 0x04 */
    int unk8[3];    /* 0x08 */
} GfxQueue;         /* 0x14 */

GfxQueue data_020dea60 = {0};

extern void *ResetTaskQueue_(GfxQueue *queue);

void *GfxQueue_Configure(int a, int b) {
    data_020dea60.word0 = a;
    data_020dea60.word4 = b;
    return ResetTaskQueue_(&data_020dea60);
}
