#include "KBaseMacro.h"
#include "KLcPy.h"


KLcBool KLpdCreatePy3ObjectArray(KLPPY3OBJECTARRAY_PTR* ppArray)
{
	KLcBool kbBool = KL_FALSE;
	KLPPY3OBJECTARRAY_PTR pRet = KL_MALLOC(KLPPY3OBJECTARRAY);
	KL_PROCESS_ERROR(pRet);

	pRet->unCount = 0;
	pRet->ptHeadNode = pRet;
	pRet->ptTailNode = pRet;
	pRet->ptTailNode->ptNext = pRet->ptHeadNode;
	pRet->ptNext = NULL;
	pRet->pData = NULL;

	KLpdCreatePy3ObjectArrayFn(pRet);

	*ppArray = pRet;
	kbBool = KL_TRUE;
	
Exit0:
	return kbBool;
}

void KLpdCreatePy3ObjectArrayFn(KLPPY3OBJECTARRAY_PTR pArray)
{
	pArray->Append = KLpdAppendPy3ObjectArrayNode;
	pArray->Remove = KLpdRemovePy3ObjectArrayNode;
}

KLcBool KLpdDeletePy3ObjectArray(KLPPY3OBJECTARRAY_PTR pArray)
{
	KLcBool kbBool = KL_FALSE;
	KLPPY3OBJECTARRAY_PTR ptmpArray = pArray->ptNext;
	KLPPY3OBJECTARRAY_PTR ptmpTagNode = NULL;

	KL_PROCESS_SUCCESS((0 == pArray->unCount));

	while (NULL != ptmpArray->ptNext && ptmpArray != pArray->ptHeadNode)
	{
		ptmpTagNode = ptmpArray;
		ptmpArray = ptmpTagNode->ptNext;
		KLpdRealsePy3ObjectNodeData(ptmpTagNode->pData);
		
		KL_RELEASE(ptmpTagNode);
	}

	KLP_RELEASE(pArray);

	kbBool = KL_TRUE;
Exit0:
	return kbBool;
}

KLcBool KLpdAppendPy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, KLPPY3OBJECTLINKCONTAINERDATA_PTR pData)
{
	KLcBool kbBool = KL_FALSE;
	KLPPY3OBJECTARRAY_PTR pNode = KL_MALLOC(KLPPY3OBJECTARRAY);
	KL_PROCESS_ERROR(pNode);

	pNode->pData = pData;
	pNode->ptHeadNode = pArray->ptHeadNode;
	pNode->ptTailNode = pNode;
	pNode->ptNext = pNode->ptTailNode->ptNext;
	pArray->ptTailNode->ptNext = pNode;
	pArray->ptTailNode = pNode;
	pArray->unCount++;

	KLpdCreatePy3ObjectArrayFn(pNode);

	kbBool = KL_TRUE;
Exit0:
	return kbBool;
}

KLcBool KLpdRemovePy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, unsigned int unPos)
{
	KLcBool kbBool = KL_FALSE;
	unsigned int unTag = 0;
	KLPPY3OBJECTARRAY_PTR ptmpTagNode = NULL;
	KLPPY3OBJECTARRAY_PTR ptmpTagPreNode = NULL;

	KL_PROCESS_ERROR(unPos > pArray->unCount || 0 != unPos);

	// get target - 1 node.
	for (ptmpTagPreNode = pArray;
		ptmpTagPreNode->ptNext != pArray && unTag != unPos - 1;
		ptmpTagPreNode = ptmpTagPreNode->ptNext, unTag++);
	
	if (ptmpTagPreNode->ptNext == pArray->ptTailNode)
	{
		// delete tail node.
		ptmpTagNode = ptmpTagPreNode->ptNext;
		ptmpTagPreNode->ptNext = pArray;
		ptmpTagPreNode->ptTailNode = ptmpTagPreNode;

		KLpdRealsePy3ObjectNodeData(ptmpTagNode->pData);
		KL_RELEASE(ptmpTagNode);
	} 
	else
	{
		// delete central node.
		ptmpTagNode = ptmpTagPreNode->ptNext;
		ptmpTagPreNode->ptNext = ptmpTagNode->ptNext;

		KLpdRealsePy3ObjectNodeData(ptmpTagNode->pData);
		KL_RELEASE(ptmpTagNode);
	}

	unTag--;
	kbBool = KL_TRUE;
Exit0:
	return kbBool;
}

void KLpdRealsePy3ObjectNodeData(KLPPY3OBJECTLINKCONTAINERDATA_PTR pData)
{
	KLP_RELEASE(pData->pPyClass);
	KLP_RELEASE(pData->pPyClassConstruct);
	KLP_RELEASE(pData->pPyClassIns);
	KLP_RELEASE(pData->pPyClassRet);
}