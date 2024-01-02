/********************************************************
* Filename		: KLcWin.c
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#include "KLcWin.h"
#include "KLog.h"

KLcBool KLwmInitCustomExchageArray()
{
	KLcBool kbRet = KL_FALSE;
	KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR ptmp = NULL;

	for (size_t i = 0; i < MAX_KCUSTOMDATAARRAY; i++)
	{
		ptmp = (KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR)malloc(sizeof(KLW_CUSTOMSCRIPTDATAEXCHANGE));
		KL_PROCESS_ERROR(ptmp);
		g_arrpCustomDataExchagePChar[i] = ptmp;
	}

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLwmUninitCustomExchageArray()
{
	KLcBool kbRet = KL_FALSE;

	for (size_t i = 0; i < MAX_KCUSTOMDATAARRAY; i++)
	{
		KL_RELEASE(g_arrpCustomDataExchagePChar[i]);
	}

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KL_DLLEXPORT KLcBool KLwInitShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc)
{
	KLcBool kbRet = KL_FALSE;
	ptShareDesc->phShareMem = (PHANDLE)malloc(sizeof(HANDLE));
	KL_PROCESS_ERROR(ptShareDesc->phShareMem);
	ptShareDesc->ppvMemMapping = (LPVOID)malloc(sizeof(LPVOID));
	KL_PROCESS_ERROR(ptShareDesc->ppvMemMapping);

	*ptShareDesc->phShareMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, ptShareDesc->dwSize, ptShareDesc->wsMemName);
	if (ERROR_ALIAS_EXISTS == GetLastError())
	{
		*ptShareDesc->phShareMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ptShareDesc->wsMemName);
		KL_PROCESS_ERROR(*ptShareDesc->phShareMem);
	}
	else
	{
		KL_PROCESS_ERROR(*ptShareDesc->phShareMem);
	}
	KLLOG(KLOG_INFO, L"Create share memory success! phShareMem: %p. memory desc: %s, size: %llu.", *ptShareDesc->phShareMem, ptShareDesc->wsMemName, ptShareDesc->dwSize);

	*ptShareDesc->ppvMemMapping = MapViewOfFile(*ptShareDesc->phShareMem, FILE_MAP_ALL_ACCESS, 0, 0, ptShareDesc->dwSize);
	KL_PROCESS_ERROR(*ptShareDesc->ppvMemMapping);
	KLLOG(KLOG_INFO, L"Map view success! pvMemMapping: %p.", *ptShareDesc->ppvMemMapping);

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KL_DLLEXPORT KLcBool KLwUninitShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc)
{
	KLcBool kbRet = KL_FALSE;
	BOOL bFnRet = FALSE;

	bFnRet = UnmapViewOfFile(*ptShareDesc->ppvMemMapping);
	KL_PROCESS_ERROR(bFnRet);

	bFnRet = CloseHandle(*ptShareDesc->phShareMem);
	KL_PROCESS_ERROR(bFnRet);

	KL_RELEASE(ptShareDesc->ppvMemMapping);
	KL_RELEASE(ptShareDesc->phShareMem);

	KLLOG(KLOG_INFO, L"Uninit share memory success!");

	kbRet = KL_TRUE;

Exit0:
	return kbRet;
}

KL_DLLEXPORT KLcBool KLwGetShareMem(KLW_SHAREMEMDESC_PTR pSrc, void** ppvRet, DWORD dwSize)
{
	KLcBool klBool = KL_FALSE;
	errno_t nErr = 0;

	nErr = memcpy_s(*ppvRet, dwSize, *pSrc->ppvMemMapping, pSrc->dwSize);
	KL_PROCESS_ERROR(0 == nErr);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLwGetCustomScriptDataExchage(unsigned int unTagPos, KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR* ppRet)
{
	KLcBool klBool = KL_FALSE;


	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLwSetCustomScriptDataExchagePChar(char** arrszpCustomData, unsigned int unLen, unsigned int unTagPos)
{
	KLcBool klBool = KL_FALSE;
	KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR punRet = g_arrpCustomDataExchagePChar[unTagPos];
	KL_PROCESS_ERROR(punRet);
	KL_PROCESS_ERROR(unLen < MAX_KCUSTOMDATA);

	for (size_t i = 0; i < unLen; i++)
	{
		punRet->arrszpCustomData[i] = arrszpCustomData[i];
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

void KLwSetPCharBackslash(char* szpText)
{
	int n = 0;
	int nLen = strlen(szpText);

	while (n < nLen)
	{
		if ('\\' == * szpText)
		{
			*szpText = '/';
		}
		szpText++;
		n++;
	}
}

void KLwGetSimpleHash(const char* szpSrc, unsigned int unLen, unsigned int* punRet)
{
	unsigned int unHash = 20240102;
	for (size_t i = 0; i < unLen; i++)
	{
		unHash ^= ((unHash << 5) + (*szpSrc) + (unHash >> 2));
	}
	*punRet = unHash;
}

void KLwDecToHex(const int cnSrc, int* pnDst)
{
	
}

void KLwRandomNum(const int cnMax, int* pnRet)
{
	*pnRet = rand() % (cnMax + 1);
	return;
}

KL_DLLEXPORT KLcBool KLwSetCustomScriptDataExchageInt()
{
	return KL_TRUE;
}

KL_DLLEXPORT KLcBool KLwSetShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc, enum KLEM_SHAREMEMFLAGS emFlags)
{
	KLcBool klBool = KL_FALSE;
	errno_t nErr = 0;

	nErr = memcpy_s(*ptShareDesc->ppvMemMapping, ptShareDesc->dwSize, &emFlags, sizeof(enum KLEM_SHAREMEMFLAGS));
	KL_PROCESS_ERROR(0 == nErr);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLwResetShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc)
{
	KLcBool klBool = KL_FALSE;
	errno_t nErr = 0;
	enum KLEM_SHAREMEMFLAGS emZero = KMSHARE_ZERO;

	nErr = memcpy_s(*ptShareDesc->ppvMemMapping, ptShareDesc->dwSize, &emZero, sizeof(enum KLEM_SHAREMEMFLAGS));
	KL_PROCESS_ERROR(0 == nErr);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLwGetWindowsProcessInfo(const WCHAR* cwszpProcess, PDWORD pdwPid)
{
	KLcBool klBool = KL_FALSE;
	int nProcessCount = 0;
	HANDLE hAllProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 tTmpProcess = { 0 };
	tTmpProcess.dwSize = sizeof(PROCESSENTRY32);
	
	KL_PROCESS_SUCCESS(INVALID_HANDLE_VALUE == hAllProcess);
	klBool = Process32First(hAllProcess, &tTmpProcess);
	while (klBool)
	{
		klBool = Process32Next(hAllProcess, &tTmpProcess);
		if (0 == wcscmp(tTmpProcess.szExeFile, cwszpProcess))
		{
			*pdwPid = tTmpProcess.th32ProcessID;
			KLLOG(KLOG_INFO, L"Get windows process info success! process: %s, pid: %ul", cwszpProcess, *pdwPid);
			break;
		}
		nProcessCount++;
	}

	klBool = CloseHandle(hAllProcess);
	KL_PROCESS_ERROR(klBool);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

