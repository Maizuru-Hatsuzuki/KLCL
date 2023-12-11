/********************************************************
* Filename		: KLcWin.c
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#include "KLcWin.h"
#include "KLog.h"


KLcBool KLwInitShareMem(KLWSHAREMEMDESC_PTR ptShareDesc)
{
	KLcBool kbRet = KL_FALSE;
	ptShareDesc->phShareMem = (PHANDLE)malloc(sizeof(HANDLE));
	KL_PROCESS_ERROR(ptShareDesc->phShareMem);
	ptShareDesc->ppvMemMapping = (LPVOID)malloc(sizeof(LPVOID));
	KL_PROCESS_ERROR(ptShareDesc->ppvMemMapping);

	*ptShareDesc->phShareMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(KLWPADDINGSHAREMEMDESC), ptShareDesc->wsMemName);
	if (ERROR_ALIAS_EXISTS == GetLastError())
	{
		*ptShareDesc->phShareMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ptShareDesc->wsMemName);
		KL_PROCESS_ERROR(*ptShareDesc->phShareMem);
	}
	else
	{
		KL_PROCESS_ERROR(*ptShareDesc->phShareMem);
	}
	KLLOG(KLOG_INFO, L"Create share memory success! phShareMem: %p.", *ptShareDesc->phShareMem);

	*ptShareDesc->ppvMemMapping = MapViewOfFile(*ptShareDesc->phShareMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(KLWPADDINGSHAREMEMDESC));
	KL_PROCESS_ERROR(*ptShareDesc->ppvMemMapping);
	KLLOG(KLOG_INFO, L"Map view success! pvMemMapping: %p.", *ptShareDesc->ppvMemMapping);

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLwUninitShareMem(KLWSHAREMEMDESC_PTR ptShareDesc)
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
