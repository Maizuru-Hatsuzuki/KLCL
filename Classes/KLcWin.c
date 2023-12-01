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
