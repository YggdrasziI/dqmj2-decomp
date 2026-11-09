/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

typedef struct InsertMBlock_node {
    char pad[8];
    struct InsertMBlock_node *prev;
    struct InsertMBlock_node *next;
} InsertMBlock_node;

typedef struct {
    InsertMBlock_node *head;
    InsertMBlock_node *tail;
} InsertMBlock_list;

InsertMBlock_node *InsertMBlock(InsertMBlock_list *list, InsertMBlock_node *node, InsertMBlock_node *prev)
{
    InsertMBlock_node *next;

    node->prev = prev;
    if (prev != 0) {
        next = prev->next;
        prev->next = node;
    } else {
        next = list->head;
        list->head = node;
    }
    node->next = next;
    if (next != 0) {
        next->prev = node;
    } else {
        list->tail = node;
    }
    return node;
}
