/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nnsys/fnd.h"

extern void NNS_FndAppendListObject(struct NNSFndList *list, void *object);

extern void NNS_FndPrependListObject(struct NNSFndList *list, void *object);

void NNS_FndInsertListObject(struct NNSFndList *list, void *where, void *object)
{
    if (where == 0) {
        NNS_FndAppendListObject(list, object);
    } else if (where == list->head_object) {
        NNS_FndPrependListObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        void *previousObject =
            ((struct NNSFndLink *)((char *)where + list->offset))->prev_object;
        struct NNSFndLink *previousLink =
            (struct NNSFndLink *)((char *)previousObject + list->offset);
        link->prev_object = previousObject;
        link->next_object = where;
        previousLink->next_object = object;
        ((struct NNSFndLink *)((char *)where + list->offset))->prev_object = object;
        list->num_objects++;
    }
}
