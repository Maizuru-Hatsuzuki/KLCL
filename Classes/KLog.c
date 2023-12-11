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

KL_DLLEXPORT KLcBool KPrettyPrintfW(enum KLEM_LOGLEVEL emLevel, LPCWSTR cwszpText, ...)
{
	KLcBool kbResult = KL_FALSE;
	WCHAR wszarrText[MAX_ZPRINTF] = { 0 };
	WCHAR* wszpLevel = L"";
	WCHAR wszarrDate[32] = KLCL_ARRNULL;
	WCHAR wszarrTime[32] = KLCL_ARRNULL;
	DWORD dwFuncRes = -1;

	dwFuncRes = MultiByteToWideChar(CP_UTF8, 0, __DATE__, -1, wszarrDate, 32);
	KL_PROCESS_ERROR(dwFuncRes);
	dwFuncRes = MultiByteToWideChar(CP_UTF8, 0, __TIME__, -1, wszarrTime, 32);
	KL_PROCESS_ERROR(dwFuncRes);

	switch (emLevel)
	{
	case KLOG_DEBUG:
		wszpLevel = L"[KLCL][DEBUG] ";
		wprintf_s(wszpLevel);
		break;
	case KLOG_INFO:
		wszpLevel = L"[KLCL][INFO] ";
		wprintf_s(wszpLevel);
		break;
	case KLOG_WARING:
		wszpLevel = L"[KLCL][WARING] ";
		wprintf_s(wszpLevel);
		break;
	case KLOG_ERROR:
		wszpLevel = L"[KLCL][ERROR] ";
		wprintf_s(wszpLevel);
		break;
	default:
		break;
	}

	// print date time.
	kbResult = KLBASELOG();
	KL_PROCESS_ERROR(kbResult);
	KL_VAOUTW(cwszpText, wszarrText);

	wsprintf(g_tKlSysLog.wszarrLog, L"%s %s %s%s\n", wszarrDate, wszarrTime, wszpLevel, wszarrText);
	g_tKlSysLog.kbIsPrintfFlag = KL_FALSE;

	wprintf_s(L"\n");

	kbResult = 0;

Exit0:
	return kbResult;

}

KL_DLLEXPORT KLcBool KPrettyPrintfA(enum KLEM_LOGLEVEL emLevel, const char* cszpText, ...)
{
	KLcBool kbResult = KL_FALSE;
	char szarrText[MAX_ZPRINTF] = { 0 };
	char* szpLevel = "";

	switch (emLevel)
	{
	case KLOG_DEBUG:
		szpLevel = "[KLCL][DEBUG] ";
		printf(szpLevel);
		break;
	case KLOG_INFO:
		szpLevel = "[KLCL][INFO] ";
		printf(szpLevel);
		break;
	case KLOG_WARING:
		szpLevel = "[KLCL][WARING] ";
		printf(szpLevel);
		break;
	case KLOG_ERROR:
		szpLevel = "[KLCL][ERROR] ";
		printf(szpLevel);
		break;
	default:
		break;
	}

	// print date time.
	kbResult = KLBASELOG();
	KL_PROCESS_ERROR(kbResult);
	KL_VAOUTA(cszpText, szarrText);

	sprintf_s(g_tKlSysLog.szarrLog, strlen(szarrText) + 1, "%s, %s %s%s\n", __DATE__, __TIME__,szpLevel, szarrText);
	g_tKlSysLog.kbIsPrintfFlag = KL_FALSE;

	printf_s("\n");

	kbResult = 0;

Exit0:
	return kbResult;

}

KL_DLLEXPORT void KLWCharToChar(LPCWSTR pwsSrc, char* szpDst)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwsSrc, wcslen(pwsSrc), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, pwsSrc, wcslen(pwsSrc), szpDst, nLen, NULL, NULL);
	return;
}

KL_DLLEXPORT void KLResetSysLog()
{
	ZeroMemory(&g_tKlSysLog, sizeof(UPDATELOGINFO));
	g_tKlSysLog.kbIsPrintfFlag = KL_TRUE;
	return;
}

KL_DLLEXPORT void KLPushSysLog(WCHAR* wpsRet, char* psRet)
{
	if (NULL != wpsRet)
	{
		wcscpy_s(wpsRet, wcslen(g_tKlSysLog.wszarrLog) + 1, g_tKlSysLog.wszarrLog);
	}
	else if (NULL != psRet)
	{
		strcpy_s(psRet, strlen(g_tKlSysLog.szarrLog) + 1, g_tKlSysLog.szarrLog);
	}
	
	return;
}

KL_DLLEXPORT void KLGetSysLogFlag(int* pnRet)
{
	*pnRet = g_tKlSysLog.kbIsPrintfFlag;
	return;
}