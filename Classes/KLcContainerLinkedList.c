/********************************************************
* Filename		: KLcContainerLinkedList.c
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#include "KLcContainer.h"
#include "KBaseMacro.h"


KLcBool KLcSingCirLinkedListNodeAppend(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData)
{
	KLcBool klBool = KL_FALSE;
	KLCSINGCIRLINKEDLIST_PTR ptAddNode = (KLCSINGCIRLINKEDLIST_PTR)malloc(sizeof(KLCSINGCIRLINKEDLIST));
	KL_PROCESS_ERROR(ptAddNode);
	ZeroMemory(ptAddNode, sizeof(KLCSINGCIRLINKEDLIST));

	ptAddNode->pData = pData;
	ptAddNode->ptHeadNode = pThis->ptHeadNode;
	ptAddNode->ptTailNode = ptAddNode;
	ptAddNode->ptNext = pThis->ptTailNode->ptNext;
	pThis->ptTailNode->ptNext = ptAddNode;
	pThis->ptTailNode = ptAddNode;
	pThis->unCount++;

	KLcSingCirLinkedListNodeInitFn(ptAddNode);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLcBool KLcSingCirLinkedListNodeRemove(KLCSINGCIRLINKEDLIST_PTR pThis, unsigned int unPos)
{
	KLcBool klBool = KL_FALSE;
	KLCSINGCIRLINKEDLIST_PTR ptmpTagNode = NULL;
	KLCSINGCIRLINKEDLIST_PTR ptmpTagPreNode = NULL;
	unsigned int unTag = 0;

	KL_PROCESS_SUCCESS(unPos > pThis->unCount || 0 == unPos);

	// Get target(unPos) - 1 prep node.
	for (
		ptmpTagPreNode = pThis;
		ptmpTagPreNode->ptNext != pThis && unTag != unPos - 1;
		ptmpTagPreNode = ptmpTagNode->ptNext, unPos++
		);

	if (ptmpTagPreNode->ptNext == pThis->ptTailNode)
	{
		// if unPos node is last node.
		ptmpTagNode = ptmpTagPreNode->ptNext;
		ptmpTagPreNode->ptNext = pThis;
		ptmpTagPreNode->ptTailNode = ptmpTagPreNode;

		KLcDestroyLinkedListData(ptmpTagNode->pData);
		KL_RELEASE(ptmpTagNode);
		pThis->unCount--;
	}
	else
	{
		// if unPos node is central node.
		ptmpTagNode = ptmpTagPreNode->ptNext;
		ptmpTagPreNode->ptNext = ptmpTagNode->ptNext;

		KLcDestroyLinkedListData(ptmpTagNode->pData);
		KL_RELEASE(ptmpTagNode);
		pThis->unCount--;
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLcBool KLcSingCirLinkedListNodeFindPos(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData, LPCWSTR cwsTag, unsigned int* punRet)
{
	KLcBool klBool = KL_FALSE;
	KLCSINGCIRLINKEDLIST_PTR ptmpTagNode = pThis;
	*punRet = 0;

	KL_PROCESS_ERROR(pThis);

	// If ptmpTagNode == pThis(header node), then break while.
	while (ptmpTagNode->ptNext != pThis)
	{
		(*punRet)++;
		ptmpTagNode = ptmpTagNode->ptNext;

		if (NULL != pData && ptmpTagNode->pData == pData)
		{
			// Use pData search.
			break;
		}
		else if (0 == wcscmp(cwsTag, ptmpTagNode->pData->cwsWorkerName))
		{
			// Use cwsTag search.
			break;
		}
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

void KLcSingCirLinkedListNodeInitFn(KLCSINGCIRLINKEDLIST_PTR pThis)
{
	pThis->Append = KLcSingCirLinkedListNodeAppend;
	pThis->Remove = KLcSingCirLinkedListNodeRemove;
	pThis->FindPos = KLcSingCirLinkedListNodeFindPos;
	return;
}

KL_DLLEXPORT KLcBool KLcCreateSinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR* ppRet)
{
	KLcBool klBool = KL_FALSE;
	KLCSINGCIRLINKEDLIST_PTR pRet = (KLCSINGCIRLINKEDLIST_PTR)malloc(sizeof(KLCSINGCIRLINKEDLIST));
	KL_PROCESS_ERROR(pRet);

	pRet->unCount				= 0;
	pRet->ptHeadNode			= pRet;
	pRet->ptTailNode			= pRet;
	pRet->ptTailNode->ptNext	= pRet->ptHeadNode;
	pRet->ptNext				= pRet;
	pRet->pData					= NULL;
	KLcSingCirLinkedListNodeInitFn(pRet);

	*ppRet = pRet;

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLcCreateLinkedListData(enum KLEM_GENERICS emType, void* vpData, LPCWSTR cwsWorkerName, KLCLINKEDLISTDATA_PTR* ppRet)
{
	KLcBool klBool = KL_FALSE;
	KLCLINKEDLISTDATA_PTR pRet = (KLCLINKEDLISTDATA_PTR)malloc(sizeof(KLCLINKEDLISTDATA));
	KL_PROCESS_ERROR(pRet);

	pRet->emType = emType;
	pRet->vpData = vpData;
	pRet->cwsWorkerName = cwsWorkerName;
	*ppRet = pRet;

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT void KLcDestroySinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR pList)
{
	// First node, while from here.
	KLCSINGCIRLINKEDLIST_PTR ptmpList = pList->ptNext;
	// Delete tmp node.
	KLCSINGCIRLINKEDLIST_PTR ptmpTagNode = NULL;

	// If pList->ptNext has value and not finish a round, go ahead.
	while (NULL != ptmpList->ptNext && ptmpList != pList->ptHeadNode)
	{
		ptmpTagNode = ptmpList;
		ptmpList = ptmpTagNode->ptNext;
		KLcDestroyLinkedListData(ptmpList->pData);
		KL_RELEASE(ptmpTagNode);
		pList->unCount--;
	}
	// Delete pList header node.
	KL_RELEASE(pList);

	return;
}

KL_DLLEXPORT void KLcDestroyLinkedListData(KLCLINKEDLISTDATA_PTR pData)
{
	KL_RELEASE(pData->vpData);
	KL_RELEASE(pData);
	return;
}
