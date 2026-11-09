/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os_types.h"

#define OSi_STACK_MAGIC_HIGH 0xfddb597du

#define OSi_STACK_MAGIC_LOW  0x7bf9dd5bu

typedef void (*OSThreadFunc)(void *pArg);

typedef struct OSThread {
    u8 _reserved0[4];
    void *pArg;                  
    u8 _reserved08[0x34];
    void *pTerminateHook;        
    u8 _reserved40[0x24];
    u32 field64;                 
    u8 _reserved68[4];
    u32 id;                      
    u32 priority;                
    u32 field74;                 
    u32 field78;                 
    struct OSThread *prev;       
    struct OSThread *next;       
    u32 field84;
    u32 field88;
    u32 field8c;
    u32 *pStackLow;              
    u32 *pStackHigh;             
    u32 field98;
    u32 field9c;
    u32 fielda0;
    u8 _reserveda4[0xc];         
    u32 fieldb0;                 
} OSThread;

extern OSIntrMode OS_DisableInterrupts(void);

extern void OS_RestoreInterrupts(OSIntrMode state);

extern u32 OSi_GetUnusedThreadId(void);

extern void OSi_InsertThreadByPriority(OSThread *pThread);

extern void OS_InitContext(OSThread *pThread, OSThreadFunc pfnEntry, void *pStack);

extern void func_02006cd8(OSThread *pThread, void *pfnDestructor);

extern void func_02008c14(u32 nValue, void *pDest, u32 nBytes);

extern void OS_ExitThread(void);

void OS_CreateThread(OSThread *pThread, OSThreadFunc pfnEntry, void *pArg,
                     void *pStack, u32 nStackSize, u32 nPriority)
{
    u8 *pLow;
    OSIntrMode nLast = OS_DisableInterrupts();
    u32 nId = OSi_GetUnusedThreadId();

    pThread->priority = nPriority;
    pThread->id = nId;
    pThread->field64 = 0;
    pThread->field74 = 0;
    OSi_InsertThreadByPriority(pThread);

    pLow = (u8 *)pStack - nStackSize;
    pThread->pStackHigh = (u32 *)pStack;
    pThread->pStackLow = (u32 *)pLow;
    pThread->field98 = 0;
    pThread->pStackHigh[-1] = OSi_STACK_MAGIC_HIGH;
    pThread->pStackLow[0] = OSi_STACK_MAGIC_LOW;
    pThread->field9c = pThread->fielda0 = 0;
    OS_InitContext(pThread, pfnEntry, (void *)((u8 *)pStack - 4));

    pThread->pArg = pArg;
    pThread->pTerminateHook = (void *)OS_ExitThread;
    func_02008c14(0, pLow + 4, nStackSize - 8);

    pThread->field84 = 0;
    pThread->field88 = 0;
    pThread->field8c = 0;
    func_02006cd8(pThread, NULL);

    pThread->field78 = 0;
    pThread->next = NULL;
    pThread->prev = NULL;
    func_02008c14(0, pThread->_reserveda4, 12);

    pThread->fieldb0 = 0;
    OS_RestoreInterrupts(nLast);
}
