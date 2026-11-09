/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#define SND_COMMAND_NOBLOCK 0

#define SND_COMMAND_BLOCK 1

#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

#define SND_CHANNEL_DATASHIFT_NONE 0

#define SND_CHANNEL_DATASHIFT_1BIT 1

#define SND_CHANNEL_DATASHIFT_2BIT 2

#define SND_CHANNEL_DATASHIFT_4BIT 3

#define SND_VOLUME_DB_MIN (-723)

#define SND_VOLUME_DB_MAX 0

#define SND_VOLUME_SHIFT_2_MIN (-240)

#define SND_VOLUME_SHIFT_1_MIN (-120)

#define SND_VOLUME_SHIFT_0_MIN (-60)

#define VolumeTable data_020c1784

typedef struct SNDCommand {
    struct SNDCommand *next;      
    u32 id;                       
    u32 arg[4];                   
} SNDCommand;

enum {
    SND_COMMAND_START_SEQ = 0,
    SND_COMMAND_STOP_SEQ = 1,
    SND_COMMAND_PREPARE_SEQ = 2,
    SND_COMMAND_START_PREPARED_SEQ = 3,
    SND_COMMAND_PAUSE_SEQ = 4,
    SND_COMMAND_CHANNEL_PAN = 0x15,
    SND_COMMAND_LOCK_CHANNEL = 0x1a,
    SND_COMMAND_UNLOCK_CHANNEL = 0x1b
};

typedef int SNDChannelDataShift;

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);

extern const u8 data_020c1784[];

u16 SND_CalcChannelVolume(int dB)
{
    SNDChannelDataShift shift;
    u8 volume;

    if (dB < SND_VOLUME_DB_MIN) {
        dB = SND_VOLUME_DB_MIN;
    } else if (dB > SND_VOLUME_DB_MAX) {
        dB = SND_VOLUME_DB_MAX;
    }

    volume = VolumeTable[dB - SND_VOLUME_DB_MIN];

    if (dB < SND_VOLUME_SHIFT_2_MIN) {
        shift = SND_CHANNEL_DATASHIFT_4BIT;
    } else if (dB < SND_VOLUME_SHIFT_1_MIN) {
        shift = SND_CHANNEL_DATASHIFT_2BIT;
    } else if (dB < SND_VOLUME_SHIFT_0_MIN) {
        shift = SND_CHANNEL_DATASHIFT_1BIT;
    } else {
        shift = SND_CHANNEL_DATASHIFT_NONE;
    }

    return (u16)(shift << 8 | volume);
}
