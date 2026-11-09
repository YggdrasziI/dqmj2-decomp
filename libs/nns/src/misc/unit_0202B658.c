/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nnsys/fnd.h"

extern void SetFirstObject(struct NNSFndList *list, void *object);

void NNS_FndPrependListObject(struct NNSFndList *list, void *object)
{
    if (list->head_object == 0) {
        SetFirstObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        link->prev_object = 0;
        link->next_object = list->head_object;
        ((struct NNSFndLink *)((char *)list->head_object + list->offset))->prev_object = object;
        list->head_object = object;
        list->num_objects++;
    }
}
