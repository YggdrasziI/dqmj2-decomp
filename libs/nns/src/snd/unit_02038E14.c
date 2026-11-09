/* NitroSystem; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#include "nnsys/snd.h"

#define RESERVED_AREASIZE 32

NNSSndArcLoadResult NNSi_SndArcLoadBank(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);

const NNSSndArcSeqInfo * NNS_SndArcGetSeqInfo(int seqNo);

void * NNS_SndArcGetFileAddress(u32 fileId);

extern NNSSndSeqData * func_02039104(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern NNSSndArcLoadResult NNSi_SndArcLoadBank (int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);

extern NNSSndSeqData * func_02039104 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

void SND_AssignWaveArc(struct SNDBankData * bank, int index, struct SNDWaveArc * waveArc);

NNSSndArcLoadResult NNSi_SndArcLoadWaveArc(int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData);

const NNSSndArcBankInfo * NNS_SndArcGetBankInfo(int bankNo);

const NNSSndArcWaveArcInfo * NNS_SndArcGetWaveArcInfo(int waveArcNo);

extern SNDBankData * func_02039170(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern BOOL LoadSingleWaves(SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);

extern NNSSndArcLoadResult NNSi_SndArcLoadWaveArc (int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData);

extern SNDBankData * func_02039170 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern BOOL LoadSingleWaves (SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);

extern SNDWaveArc * func_020391dc(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern SNDWaveArc * NNS_SndArcLoadWaveArcTable(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern SNDWaveArc * func_020391dc (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

extern SNDWaveArc * NNS_SndArcLoadWaveArcTable (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

void DC_StoreRange(const void * startAddr, u32 nBytes);

void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);

s32 func_02038ca0(u32 fileId, void * buffer, s32 size, s32 offset);

u32 NNS_SndArcGetFileSize(u32 fileId);

NNSSndArcLoadResult NNSi_SndArcLoadSeq (int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData)
{
    const NNSSndArcSeqInfo * seqInfo;
    NNSSndSeqData * seqData = NULL;
    SNDBankData * bank = NULL;
    NNSSndArcLoadResult result;

    seqInfo = NNS_SndArcGetSeqInfo(seqNo);
    if (seqInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO;

    result = NNSi_SndArcLoadBank(seqInfo->param.bankNo, loadFlag, heap, bSetAddr, NULL);
    if (result != NNS_SND_ARC_LOAD_SUCESS) return result;

    if (loadFlag & NNS_SND_ARC_LOAD_SEQ) {
        seqData = func_02039104(seqInfo->fileId, heap, bSetAddr);
        if (seqData == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ;
        }
    } else {
        seqData = (NNSSndSeqData *)NNS_SndArcGetFileAddress(seqInfo->fileId);
    }

    if (pData != NULL) *pData = seqData;

    return NNS_SND_ARC_LOAD_SUCESS;
}

NNSSndArcLoadResult NNSi_SndArcLoadBank (int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData)
{
    const NNSSndArcBankInfo * bankInfo;
    const NNSSndArcWaveArcInfo * waveArcInfo;
    SNDBankData * bank = NULL;
    SNDWaveArc * waveArc;
    NNSSndArcLoadResult result;
    int i;

    bankInfo = NNS_SndArcGetBankInfo(bankNo);
    if (bankInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_BANK) {
        bank = func_02039170(bankInfo->fileId, heap, bSetAddr);
        if (bank == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK;
        }
    } else {
        bank = (SNDBankData *)NNS_SndArcGetFileAddress(bankInfo->fileId);
    }

    for (i = 0; i < NNS_SND_ARC_BANK_TO_WAVEARC_NUM; i++) {
        if (bankInfo->waveArcNo[i] == NNS_SND_ARC_INVALID_WAVEARC_NO) continue;

        waveArcInfo = NNS_SndArcGetWaveArcInfo(bankInfo->waveArcNo[i]);
        if (waveArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;

        result = NNSi_SndArcLoadWaveArc(bankInfo->waveArcNo[i], loadFlag, heap, bSetAddr, &waveArc);
        if (result != NNS_SND_ARC_LOAD_SUCESS) return result;

        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {

            if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
                if (!LoadSingleWaves(waveArc, bank, i, waveArcInfo->fileId, heap)) {
                    return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
                }
            }
        }

        if (bank != NULL && waveArc != NULL) {
            SND_AssignWaveArc(bank, i, waveArc);
        }
    }

    if (pData != NULL) *pData = bank;

    return NNS_SND_ARC_LOAD_SUCESS;
}

NNSSndArcLoadResult NNSi_SndArcLoadWaveArc (int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData)
{
    const NNSSndArcWaveArcInfo * waveArcInfo;
    SNDWaveArc * waveArc = NULL;

    waveArcInfo = NNS_SndArcGetWaveArcInfo(waveArcNo);
    if (waveArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {

            waveArc = NNS_SndArcLoadWaveArcTable(waveArcInfo->fileId, heap, bSetAddr);
        } else {

            waveArc = func_020391dc(waveArcInfo->fileId, heap, bSetAddr);
        }

        if (waveArc == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
        }
    } else {
        waveArc = (SNDWaveArc *)NNS_SndArcGetFileAddress(waveArcInfo->fileId);
    }

    if (pData != NULL) *pData = waveArc;

    return NNS_SND_ARC_LOAD_SUCESS;
}

void * NNSi_SndArcLoadFile (u32 fileId, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2, NNSSndHeapHandle heap)
{
    void * buffer;
    u32 len;

    len = NNS_SndArcGetFileSize(fileId);
    if (len == 0) return NULL;

    if (heap == NNS_SND_HEAP_INVALID_HANDLE) return NULL;

    buffer = NNS_SndHeapAlloc(heap, len + RESERVED_AREASIZE, callback, data1, data2);
    if (buffer == NULL) return NULL;

    if (func_02038ca0(fileId, buffer, (s32)len, 0) != len) {
        return NULL;
    }

    DC_StoreRange(buffer, len);

    return buffer;
}
