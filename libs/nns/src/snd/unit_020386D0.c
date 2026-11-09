/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

s32 func_0200c180(FSFile * p_file, void * dst, s32 len);

BOOL FS_SeekFile(FSFile * p_file, s32 offset, FSSeekFileMode origin);

void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

extern void InfoDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);

extern void FatDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);

extern void SymbolDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);

extern void InfoDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);

extern void FatDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);

extern void SymbolDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);

BOOL NNS_SndArcSetup (NNSSndArc * arc, NNSSndHeapHandle heap, BOOL symbolLoadFlag)
{
    BOOL result;
    s32 readSize;

    result = FS_SeekFile(&arc->file, 0, FS_SEEK_SET);
    if (!result) return FALSE;

    readSize = func_0200c180(
        &arc->file,
        &arc->header,
        sizeof(arc->header)
        );
    if (readSize != sizeof(arc->header)) return FALSE;

    if (heap != NNS_SND_HEAP_INVALID_HANDLE) {

        arc->info = (NNSSndArcInfo *)NNS_SndHeapAlloc(heap, arc->header.infoSize, InfoDisposeCallback, (u32)arc, 0);
        if (arc->info == NULL) return FALSE;
        result = FS_SeekFile(&arc->file, (s32)(arc->header.infoOffset), FS_SEEK_SET);
        if (!result) return FALSE;
        readSize = func_0200c180(&arc->file, arc->info, (s32)(arc->header.infoSize));
        if (readSize != arc->header.infoSize) return FALSE;

        arc->fat = (NNSSndArcFat *)NNS_SndHeapAlloc(heap, arc->header.fatSize, FatDisposeCallback, (u32)arc, 0);
        if (arc->fat == NULL) return FALSE;
        result = FS_SeekFile(&arc->file, (s32)(arc->header.fatOffset), FS_SEEK_SET);
        if (!result) return FALSE;
        readSize = func_0200c180(&arc->file, arc->fat, (s32)(arc->header.fatSize));
        if (readSize != arc->header.fatSize) return FALSE;

        if (symbolLoadFlag && arc->header.symbolDataSize > 0) {
            arc->symbol = (NNSSndArcSymbol *)NNS_SndHeapAlloc(heap, arc->header.symbolDataSize, SymbolDisposeCallback, (u32)arc, 0);
            if (arc->symbol == NULL) return FALSE;
            result = FS_SeekFile(&arc->file, (s32)(arc->header.symbolDataOffset), FS_SEEK_SET);
            if (!result) return FALSE;

            readSize = func_0200c180(&arc->file, arc->symbol, (s32)(arc->header.symbolDataSize));
            if (readSize != arc->header.symbolDataSize) return FALSE;
        }
    }

    return TRUE;
}
