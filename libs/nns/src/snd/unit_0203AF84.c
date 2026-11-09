/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nitro/pxi.h"

#include "nnsys/snd.h"

void * NNS_SndArcGetFileAddress(u32 fileId);

extern BOOL OpenFileStream(NNSSndStrmPlayer * player, u32 fileId);

extern void func_0203b078(NNSSndStrmPlayer * player);

extern s32 ReadFileStream(NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

extern void func_0203b0c0(NNSSndStrmPlayer * player);

extern BOOL OpenMemoryStream(NNSSndStrmPlayer * player, u32 fileId);

extern void func_0203b0f8(NNSSndStrmPlayer * player);

extern s32 ReadMemoryStream(NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

extern void func_0203b118(NNSSndStrmPlayer * player);

extern BOOL OpenFileStream (NNSSndStrmPlayer * player, u32 fileId);

extern void func_0203b078 (NNSSndStrmPlayer * player);

extern s32 ReadFileStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

extern void func_0203b0c0 (NNSSndStrmPlayer * player);

extern BOOL OpenMemoryStream (NNSSndStrmPlayer * player, u32 fileId);

extern void func_0203b0f8 (NNSSndStrmPlayer * player);

extern s32 ReadMemoryStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

extern void func_0203b118 (NNSSndStrmPlayer * player);

extern NNSSndStrmThread * sPrepareThread;

extern BOOL data_0204ad8c;

extern u8 * sDecodeBuffer;

void SetupStreamFunction (NNSSndStrmPlayer * player, u32 fileId)
{
    if (NNS_SndArcGetFileAddress(fileId) == NULL) {
        player->openStreamFunc = OpenFileStream;
        player->closeStreamFunc = func_0203b078;
        player->readStreamFunc = ReadFileStream;
        player->cancelStreamFunc = func_0203b0c0;
    } else {
        player->openStreamFunc = OpenMemoryStream;
        player->closeStreamFunc = func_0203b0f8;
        player->readStreamFunc = ReadMemoryStream;
        player->cancelStreamFunc = func_0203b118;
    }

}
