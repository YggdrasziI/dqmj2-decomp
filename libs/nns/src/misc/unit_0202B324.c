/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void *NNSi_FndInitExpHeap(void *hh, void *end, int opt);

void *func_0202b324(unsigned int start, unsigned int size, int opt)
{
    unsigned int end = size + start;
    unsigned int aligned_start = start + 3;
    end &= ~3u;
    aligned_start &= ~3u;
    if (aligned_start > end) goto fail;
    if ((end - aligned_start) >= 0x30) goto ok;
fail:
    return (void *)0;
ok:
    return NNSi_FndInitExpHeap((void *)aligned_start, (void *)end, opt);
}
