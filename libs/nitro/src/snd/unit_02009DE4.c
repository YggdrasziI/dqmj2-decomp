/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct SndSharedWorkSlot {
    short cells[16];
    int val;
} SndSharedWorkSlot;

typedef struct SndSharedWork {
    int field_00;
    int field_04;
    short field_08;
    short field_0a;
    unsigned char pad_0c[0x20 - 0x0c];
    SndSharedWorkSlot slots[16];
    short field_260[16];
} SndSharedWork;

extern void DC_FlushRange(void *address, unsigned int size);

void SNDi_InitSharedWork(SndSharedWork *self) {
    int i;
    int j;

    self->field_04 = 0;
    self->field_08 = 0;
    self->field_0a = 0;
    self->field_00 = 0;

    for (i = 0; i < 16; i++) {
        self->slots[i].val = 0;
        for (j = 0; j < 16; j++) {
            self->slots[i].cells[j] = -1;
        }
    }

    for (j = 0; j < 16; j++) {
        self->field_260[j] = -1;
    }

    DC_FlushRange(self, 0x280);
}
