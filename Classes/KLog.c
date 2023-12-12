#include "KLog.h"
#include <time.h>


KL_DLLEXPORT KLcBool KPrettyPrintfW(enum KLEM_LOGLEVEL emLevel, LPCWSTR cwszpText, ...)
{
	KLcBool kbResult = KL_FALSE;
	WCHAR wszarrText[MAX_ZPRINTF] = { 0 };
	WCHAR* wszpLevel = L"";
	WCHAR wszarrDatetime[32] = KLCL_ARRNULL;
	time_t ullTime = 0;
	errno_t err = 0;

	time(&ullTime);
	err = _wctime_s(wszarrDatetime, 32, &ullTime);
	ASSERT(0 == err);
	// delete "\n"
	wszarrDatetime[24] = L'\0';

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
	wprintf_s(L"%s ", wszarrDatetime);
	KL_VAOUTW(cwszpText, wszarrText);

	wsprintf(g_tKlSysLog.wszarrLog, L"%s %s%s\n", wszarrDatetime, wszpLevel, wszarrText);
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
	char szarrDatetime[32] = KLCL_ARRNULL;
	time_t ullTime = 0;
	errno_t err = 0;

	time(&ullTime);
	err = ctime_s(szarrDatetime, 32, &ullTime);
	ASSERT(0 == err);
	// delete "\n"
	szarrDatetime[24] = '\0';

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
	printf_s("%s ", szarrDatetime);
	KL_VAOUTA(cszpText, szarrText);

	sprintf_s(g_tKlSysLog.szarrLog, MAX_ZPRINTF, "%s %s%s\n", szarrDatetime, szpLevel, szarrText);
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