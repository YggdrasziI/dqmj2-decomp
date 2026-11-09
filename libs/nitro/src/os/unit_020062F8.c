/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void *OSi_RemoveMutexLinkFromQueue(void **queue) {
    char *head = (char *)queue[0];
    if (head != 0) {
        char *next = *(char **)(head + 0x10);
        queue[0] = next;
        if (next != 0) {
            *(void **)(next + 0x14) = 0;
        } else {
            queue[1] = 0;
        }
    }
    return head;
}
