/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nnsys/fnd.h"

void NNS_FndRemoveListObject(struct NNSFndList *list, void *object)
{
    struct NNSFndLink *link =
        (struct NNSFndLink *)((char *)object + list->offset);
    if (link->prev_object == 0) {
        list->head_object = link->next_object;
    } else {
        ((struct NNSFndLink *)((char *)link->prev_object + list->offset))->next_object =
            link->next_object;
    }
    if (link->next_object == 0) {
        list->tail_object = link->prev_object;
    } else {
        ((struct NNSFndLink *)((char *)link->next_object + list->offset))->prev_object =
            link->prev_object;
    }
    link->prev_object = 0;
    link->next_object = 0;
    list->num_objects--;
}
