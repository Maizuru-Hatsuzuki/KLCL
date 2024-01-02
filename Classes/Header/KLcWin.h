/********************************************************
* Filename		: KLcWin.h
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#ifndef __KLCWIN_H__
#define __KLCWIN_H__

#include "KBase.h"
#include "KLcLua.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <process.h>


#define KCAST(t, exp)		((t)(exp))

enum KLEM_SHAREMEMFLAGS
{
	KMSHARE_ZERO,
	KMSHARE_INIT,
	KMSHARE_RUN,
	KMSHARE_RELEASE,
	KMSHARE_EXIT,
	KMSHARE_UNKNOW
};

#define KL_INTERFACE struct _tKLwThreadWorkerPool
#define KTHIS KL_INTERFACE* pThis

typedef DWORD (WINAPI *KLTHREAD_WORKER_FN)(
	void* lpThreadParameter
	);
typedef KLTHREAD_WORKER_FN LPKLTHREAD_WORKER_FN;

struct _tKLwThreadWorker
{
	KLcBool bIsWorking;
	LPCWSTR cwsWorkerDesc;
	LPKLTHREAD_WORKER_FN fn;
	void* vpArgs;
	uintptr_t ullHandler;
};
typedef struct _tKLwThreadWorker KLW_THREADWORKER, * KLW_THREADWORKER_PTR;

struct _tKLwThreadWorkerPool
{
	int nMaxWorker;
	int nUseThread;
	LPCWSTR cwsThreadPoolDesc;
	KLW_THREADWORKER_PTR* arrpWorkers;
	KBOOLFN(AddWorker)(KTHIS, KLW_THREADWORKER_PTR pWorker);
	KBOOLFN(RemoveWorker)(KTHIS, KLW_THREADWORKER_PTR pWorker);
};
typedef struct _tKLwThreadWorkerPool KLW_THREADWORKPOOL, * KLW_THREADWORKPOOL_PTR;

#undef KL_INTERFACE

struct _tKLwShareMemDesc
{
	PHANDLE phShareMem;
	LPVOID* ppvMemMapping;
	LPCWSTR wsMemName;
	DWORD dwSize;
};

struct _tKLwPaddingShareMemDesc
{
	KLEM_FSMSTATUS emFsmStatus;
};

union _unKLwCustomScriptDataExchange
{
	struct
	{
		char* arrszpCustomData[MAX_KCUSTOMDATA];
	};

	struct
	{
		int arrnCustomData[MAX_KCUSTOMDATA];
	};
};

typedef struct _tKLwShareMemDesc				KLW_SHAREMEMDESC,				* KLW_SHAREMEMDESC_PTR;
typedef struct _tKLwPaddingShareMemDesc			KLW_PADDINGSHAREMEMDESC,		* KLW_PADDINGSHAREMEMDESC_PTR;
typedef union  _unKLwCustomScriptDataExchange	KLW_CUSTOMSCRIPTDATAEXCHANGE,	* KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR;


extern KLW_SHAREMEMDESC g_tKLwShareMemDesc;
extern KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR g_arrpCustomDataExchagePChar[MAX_KCUSTOMDATAARRAY];

KLcBool KLwThAddWorker(KLW_THREADWORKPOOL_PTR pThis, KLW_THREADWORKER_PTR pWorker);
KLcBool KLwThDestroyWorker(KLW_THREADWORKPOOL_PTR pThis, KLW_THREADWORKER_PTR pWorker);
KLcBool KLwmInitCustomExchageArray();
KLcBool KLwmUninitCustomExchageArray();

void KLwSetPCharBackslash(char* szpText);
void KLwGetSimpleHash(const char* szpSrc, unsigned int unLen, unsigned int* punRet);
void KLwDecToHex(const int cnSrc, int* pnDst);
void KLwRandomNum(const int cnMax, int* pnRet);

#ifdef __cplusplus
extern "C" {
#endif	
	KL_DLLEXPORT KLcBool KLwInitShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc);
	KL_DLLEXPORT KLcBool KLwUninitShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc);
	KL_DLLEXPORT KLcBool KLwGetShareMem(KLW_SHAREMEMDESC_PTR pSrc, void** ppvRet, DWORD dwSize);
	KL_DLLEXPORT KLcBool KLwGetWindowsProcessInfo(const WCHAR* cwszpProcess, PDWORD pdwPid);
	KL_DLLEXPORT KLcBool KLwGetCustomScriptDataExchage(unsigned int unTagPos, KLW_CUSTOMSCRIPTDATAEXCHANGE_PTR* ppRet);
	KL_DLLEXPORT KLcBool KLwSetCustomScriptDataExchagePChar(char** arrszpCustomData, unsigned int unLen, unsigned int unTagPos);
	KL_DLLEXPORT KLcBool KLwSetCustomScriptDataExchageInt();
	KL_DLLEXPORT KLcBool KLwSetShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc, enum KLEM_SHAREMEMFLAGS emFlags);
	KL_DLLEXPORT KLcBool KLwResetShareMem(KLW_SHAREMEMDESC_PTR ptShareDesc);
	KL_DLLEXPORT KLcBool KLwThCreateThreadPool(const int cnMaxWorker, KLW_THREADWORKPOOL_PTR* ppRet);
	KL_DLLEXPORT KLcBool KLwThCreateThreadWorker(LPCWSTR cwsWorkerDesc, LPKLTHREAD_WORKER_FN fn, void* vpArgs, KLW_THREADWORKER_PTR* ppRet);
	KL_DLLEXPORT void KLwThDestroyThreadPool(KLW_THREADWORKPOOL_PTR pPool);
#ifdef __cplusplus
}
#endif

#endif
