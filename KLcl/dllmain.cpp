// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "KLcWin.h"
#include "KLog.h"
#include "KBaseMacro.h"

extern KLWSHAREMEMDESC g_tKLwShareMemDesc = { NULL, NULL, KLCL_SHAREMEMDESC };
UPDATELOGINFO g_tKlSysLog;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_tKlSysLog.kbIsPrintfFlag = KL_TRUE;
        KLwInitShareMem(&g_tKLwShareMemDesc);
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        KLwUninitShareMem(&g_tKLwShareMemDesc);
        break;
    }

    return TRUE;
}

