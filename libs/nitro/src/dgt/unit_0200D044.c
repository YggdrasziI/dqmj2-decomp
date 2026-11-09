/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

typedef struct DGTHash2Context {
    u32 h0, h1, h2, h3, h4;
    u32 Nl;
    u32 Nh;
    int num;
    u8 data[64];
    int dummy[2];
} DGTHash2Context;

extern void MI_CpuCopy8(const void *src, void *dest, u32 size);

extern void (*data_020c5e94)(DGTHash2Context *context, const void *data, u32 length);

extern void func_02008c14(u32 data, void *destp, u32 size);

void DGT_Hash2Reset(unsigned int *ctx) {
    ctx[0] = 0x67452301;
    ctx[1] = 0xefcdab89;
    ctx[2] = 0x98badcfe;
    ctx[3] = 0x10325476;
    ctx[4] = 0xc3d2e1f0;
    ctx[5] = 0;
    ctx[6] = 0;
    ctx[7] = 0;
}

void DGT_Hash2SetSource(DGTHash2Context *context, const void *input, u32 length)
{
    const u8 *data = (const u8 *)input;
    u8 *p = context->data;
    u32 l;
    u32 n;

    if (length == 0) {
        return;
    }
    l = context->Nl + (length << 3);
    if (l < context->Nl) {
        context->Nh++;
    }
    context->Nh += length >> 29;
    context->Nl = l;

    if (context->num != 0) {
        if (context->num + length >= 64) {
            n = 64 - context->num;
            MI_CpuCopy8(data, p + context->num, n);
            length -= n;
            data += n;
            data_020c5e94(context, p, 64);
            context->num = 0;
        } else {
            MI_CpuCopy8(data, p + context->num, length);
            context->num += length;
            return;
        }
    }
    if (length >= 64) {
        int sw = (int)(length & ~0x3f);

        length -= sw;
        if (((u32)data & 3) == 0) {
            data_020c5e94(context, data, sw);
            data += sw;
        } else {
            do {
                MI_CpuCopy8(data, p, 64);
                data += 64;
                data_020c5e94(context, p, 64);
                sw -= 64;
            } while (sw > 0);
        }
    }
    context->num = length;
    if (length != 0) {
        MI_CpuCopy8(data, p, length);
    }
}

void DGT_Hash2GetDigest(DGTHash2Context *context, void *digest)
{
    u8 *md = (u8 *)digest;
    u32 *p = (u32 *)context->data;
    u8 *cp;
    int i;
    int n;
    u32 l;

    n = context->num;
    i = n >> 2;
    if ((n & 3) == 0) {
        p[i] = 0;
    }
    cp = context->data;
    cp[n] = 0x80;
    n++;
    while ((n & 3) != 0) {
        cp[n] = 0;
        n++;
    }
    i++;
    if (context->num >= 0x38) {
        for (; i < 16; i++) {
            p[i] = 0;
        }
        data_020c5e94(context, p, 64);
        i = 0;
    }
    for (; i < 14; i++) {
        p[i] = 0;
    }
    l = context->Nl;
    cp[0x3f] = (u8)l;
    cp[0x3e] = (u8)(l >> 8);
    cp[0x3d] = (u8)(l >> 16);
    cp[0x3c] = (u8)(l >> 24);
    l = context->Nh;
    cp[0x3b] = (u8)l;
    cp[0x3a] = (u8)(l >> 8);
    cp[0x39] = (u8)(l >> 16);
    cp[0x38] = (u8)(l >> 24);
    data_020c5e94(context, p, 64);
    l = context->h0;
    md[0] = (u8)(l >> 24);
    md[1] = (u8)(l >> 16);
    md[2] = (u8)(l >> 8);
    md[3] = (u8)l;
    l = context->h1;
    md[4] = (u8)(l >> 24);
    md[5] = (u8)(l >> 16);
    md[6] = (u8)(l >> 8);
    md[7] = (u8)l;
    l = context->h2;
    md[8] = (u8)(l >> 24);
    md[9] = (u8)(l >> 16);
    md[10] = (u8)(l >> 8);
    md[11] = (u8)l;
    l = context->h3;
    md[12] = (u8)(l >> 24);
    md[13] = (u8)(l >> 16);
    md[14] = (u8)(l >> 8);
    md[15] = (u8)l;
    l = context->h4;
    md[16] = (u8)(l >> 24);
    md[17] = (u8)(l >> 16);
    md[18] = (u8)(l >> 8);
    md[19] = (u8)l;
    context->num = 0;
    func_02008c14(0, &context, sizeof(context));
}
