/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

extern void OSi_ExceptionHandler(void);

extern char data_020cbf44[];

void OSi_InstallExceptionVector(void)
{
    unsigned int v = *(volatile unsigned int *)0x027FFD9Cu;
    if (v >= 0x02600000u && v < 0x02800000u) {
        *(unsigned int *)data_020cbf44 = v;
    } else {
        *(unsigned int *)data_020cbf44 = 0;
    }
    if (*(unsigned int *)data_020cbf44 == 0) {
        *(volatile void **)0x027FFD9Cu = (void *)OSi_ExceptionHandler;
        {
            volatile char *base = (volatile char *)0x027E3000u;
            *(volatile void **)(base + 0xFDC) = (void *)OSi_ExceptionHandler;
        }
    }
    *(unsigned int *)(data_020cbf44 + 8) = 0;
}
