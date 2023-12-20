// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "KLcWin.h"
#include "KLog.h"
#include "KBaseMacro.h"

KLW_SHAREMEMDESC g_tKLwShareMemDesc = { NULL, NULL, KLCL_SHAREMEMDESC, sizeof(KLW_PADDINGSHAREMEMDESC) };
UPDATELOGINFO g_tKlSysLog = { 0 };
KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR g_arrpCustomDataExchagePChar[MAX_KCUSTOMDATAARRAY] = { 0 };


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    KLcBool kbRet = KL_FALSE;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_tKlSysLog.kbIsPrintfFlag = KL_TRUE;
        kbRet = KLwmInitCustomExchageArray();
        KL_PROCESS_ERROR(kbRet);
        kbRet = KLwInitShareMem(&g_tKLwShareMemDesc);
        KL_PROCESS_ERROR(kbRet);
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        KLwmUninitCustomExchageArray();
        KLwUninitShareMem(&g_tKLwShareMemDesc);
        break;
    }

    //ASSERT(kbRet);

Exit0:
    return TRUE;
}

