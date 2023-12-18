/********************************************************
* Filename		: KLcThread.h
* Creator		: lidiankai
* Date time		: 2023.12.13
* Description	: klcl thread pool etc.
********************************************************/

#include "KLcWin.h"
#include "KLog.h"
#include "KBaseMacro.h"


KL_DLLEXPORT KLcBool KLwThCreateThreadPool(const int cnMaxWorker, KLW_THREADWORKPOOL_PTR* ppRet)
{
	KLcBool klBool = KL_FALSE;
	KLW_THREADWORKPOOL_PTR pRet = (KLW_THREADWORKPOOL_PTR)malloc(sizeof(KLW_THREADWORKPOOL));
	KL_PROCESS_ERROR(pRet);

	pRet->nMaxWorker = cnMaxWorker;
	pRet->arrpWorkers = (KLW_THREADWORKER_PTR*)malloc(sizeof(KLW_THREADWORKER_PTR) * cnMaxWorker);
	KL_PROCESS_ERROR(pRet->arrpWorkers);
	ZeroMemory(pRet->arrpWorkers, sizeof(KLW_THREADWORKER_PTR) * cnMaxWorker);

	pRet->AddWorker = KLwThAddWorker;	
	pRet->RemoveWorker = KLwThDestroyWorker;
	pRet->nUseThread = 0;

	*ppRet = pRet;

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT void KLwThDestroyThreadPool(KLW_THREADWORKPOOL_PTR pPool)
{
	KL_RELEASE(pPool->arrpWorkers);
	KL_RELEASE(pPool);
}

KL_DLLEXPORT KLcBool KLwThCreateThreadWorker(LPCWSTR cwsWorkerDesc, LPKLTHREAD_WORKER_FN fn, void* vpArgs, KLW_THREADWORKER_PTR* ppRet)
{
	KLcBool klBool = KL_FALSE;
	KLW_THREADWORKER_PTR ptWorker = (KLW_THREADWORKER_PTR)malloc(sizeof(KLW_THREADWORKER));
	KL_PROCESS_ERROR(ptWorker);

	ptWorker->ullHandler = 0;
	ptWorker->bIsWorking = KL_FALSE;
	ptWorker->cwsWorkerDesc = cwsWorkerDesc;
	ptWorker->fn = fn;
	ptWorker->vpArgs = vpArgs;
	*ppRet = ptWorker;

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLcBool KLwThDestroyWorker(KLW_THREADWORKPOOL_PTR pThis, KLW_THREADWORKER_PTR pWorker)
{
	KLcBool klBool = KL_FALSE;

	KL_PROCESS_SUCCESS(pWorker);
	for (size_t i = 0; i < pThis->nMaxWorker; i++)
	{
		if (pWorker && pThis->arrpWorkers[i] == pWorker)
		{
			KLLOG(KLOG_INFO, L"End thread success, hanlder: %lu, thread desc: %s", pWorker->ullHandler, pWorker->cwsWorkerDesc);
			KL_RELEASE(pWorker);
			pThis->nUseThread--;
			pThis->arrpWorkers[i] = NULL;

		}
		klBool = KL_TRUE;
	}

Exit0:
	return klBool;
}

KLcBool KLwThAddWorker(KLW_THREADWORKPOOL_PTR pThis, KLW_THREADWORKER_PTR pWorker)
{
	KLcBool klBool = KL_FALSE;

	for (size_t i = 0; i < pThis->nMaxWorker; i++)
	{
		if (NULL == pThis->arrpWorkers[i])
		{
			pThis->arrpWorkers[i] = pWorker;
			pWorker->ullHandler = _beginthread(pWorker->fn, 0, pWorker->vpArgs);
			KL_PROCESS_SUCCESS(-1L == pWorker->ullHandler);
			pThis->arrpWorkers[i]->bIsWorking = KL_TRUE;
			pThis->nUseThread++;
			
			KLLOG(KLOG_INFO, L"Begin thread success, handler: %lu, thread desc: %s", pWorker->ullHandler, pWorker->cwsWorkerDesc);
			klBool = KL_TRUE;
			break;
		}
	}
	
Exit0:
	return klBool;
}
