/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

void Node_SeedTransform(int *node, const int *source, int unused, int flags) {
    if ((flags & 4) != 0) {
        node[0] |= 1;
    } else {
        node[1] = source[0];
        node[2] = source[1];
        node[3] = source[2];
    }

    node[0] |= 0x18;
}
