#include "KLog.h"


void KBaseInfoPrintfA()
{
	printf_s("%s, %s ", __DATE__, __TIME__);
}


KLcBool KBaseInfoPrintfW()
{
	KLcBool kbResult = KL_FALSE;
	DWORD dwFuncRes = -1;
	WCHAR wszarrDate[32] = KLCL_ARRNULL;
	WCHAR wszarrTime[32] = KLCL_ARRNULL;

	dwFuncRes = MultiByteToWideChar(CP_UTF8, 0, __DATE__, -1, wszarrDate, 32);
	KL_PROCESS_ERROR(dwFuncRes);

	dwFuncRes = MultiByteToWideChar(CP_UTF8, 0, __TIME__, -1, wszarrTime, 32);
	KL_PROCESS_ERROR(dwFuncRes);

	dwFuncRes = wprintf_s(L"%s, %s ", wszarrDate, wszarrTime);
	kbResult = KL_TRUE;

Exit0:
	return kbResult;

}

KLcBool KPrettyPrintfW(enum KLEM_LOGLEVEL emLevel, LPCWSTR cwszpText, ...)
{
	KLcBool kbResult = KL_FALSE;

	switch (emLevel)
	{
	case KLOG_DEBUG:
		wprintf_s(L"[KLCL][DEBUG] ");
		break;
	case KLOG_INFO:
		wprintf_s(L"[KLCL][INFO] ");
		break;
	case KLOG_WARING:
		wprintf_s(L"[KLCL][WARING] ");
		break;
	case KLOG_ERROR:
		wprintf_s(L"[KLCL][ERROR] ");
		break;
	default:
		break;
	}

	// print date time.
	kbResult = KLBASELOG();
	KL_PROCESS_ERROR(kbResult);
	VAOUTW(cwszpText);

	wprintf_s(L"\n");
	kbResult = 0;

Exit0:
	return kbResult;

}

KLcBool KPrettyPrintfA(enum KLEM_LOGLEVEL emLevel, const char* cszpText, ...)
{
	KLcBool kbResult = KL_FALSE;

	switch (emLevel)
	{
	case KLOG_DEBUG:
		printf("[KLCL][DEBUG] ");
		break;
	case KLOG_INFO:
		printf("[KLCL][INFO] ");
		break;
	case KLOG_WARING:
		printf("[KLCL][WARING] ");
		break;
	case KLOG_ERROR:
		printf("[KLCL][ERROR] ");
		break;
	default:
		break;
	}

	// print date time.
	kbResult = KLBASELOG();
	KL_PROCESS_ERROR(kbResult);
	VAOUTA(cszpText);
	printf_s("\n");

	kbResult = 0;

Exit0:
	return kbResult;

}
