/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void DC_InvalidateRange(void *p, unsigned int len);

extern int *data_020cdbc0;

int SNDi_GetFinishedCommandTag(void) {
    DC_InvalidateRange(data_020cdbc0, 4);
    return *data_020cdbc0;
}
