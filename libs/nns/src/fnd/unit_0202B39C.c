/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/mi.h"

#include "nitro/os.h"

#include "nnsys/fnd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern void func_0202b274 (NNSiFndHeapHead * pHeapHd);

extern void func_0202b2c0 (NNSiFndHeapHead * pHeapHd);

void NNS_FndFreeToFrmHeap (NNSFndHeapHandle heap, int mode)
{

    if (mode & NNS_FND_FRMHEAP_FREE_HEAD) {
        func_0202b274(heap);
    }

    if (mode & NNS_FND_FRMHEAP_FREE_TAIL) {
        func_0202b2c0(heap);
    }
}
