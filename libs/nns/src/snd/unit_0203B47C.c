/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void SND_SetChannelVolume(u32 chBitMask, int volume, SNDChannelDataShift shift);

u16 SND_CalcChannelVolume(int dB);

extern NNSSndStrmChannel data_020de9d0[ 16 ];

void NNS_SndStrmSetVolume (NNSSndStrm * stream, int volume)
{
    u16 chVolume;
    int vol;
    int chNo;
    int i;

    stream->volume = volume;

    for (i = 0; i < stream->numChannels; i++) {
        chNo = stream->channelNo[ i ];
        vol = stream->volume + data_020de9d0[ chNo ].volume;
        chVolume = SND_CalcChannelVolume(vol);

        SND_SetChannelVolume(
            (u32)(1 << chNo),
            chVolume & 0xff,
            (SNDChannelDataShift)(chVolume >> 8)
            );
    }
}
