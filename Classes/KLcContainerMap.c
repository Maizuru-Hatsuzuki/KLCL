/********************************************************
* Filename		: KLcContainerMap.h
* Creator		: lidiankai
* Date time		: 2023.12.25
* Description	: map container, learn for lua table.
********************************************************/


#include "KLcContainer.h"


KL_DLLEXPORT KLcBool KLcmCreateMap(KLCMAP_PTR* ppRet)
{
	KLcBool kbRet = KL_FALSE;
	KLCMAP_PTR pRet = (KLCMAP_PTR)malloc(sizeof(KLCMAP));
	KL_PROCESS_ERROR(pRet);
	
	pRet->parrNode = (KLCMAPNODE_PTR*)malloc(sizeof(KLCMAPNODE) * 64);
	KL_PROCESS_ERROR(pRet->parrNode);
	for (size_t i = 0; i < 64; i++)
	{
		pRet->parrNode[i] = KCAST(KLCMAPNODE_PTR, KLCMAP_DEFAULTPKV);
	}

	pRet->unSize = 64;
	pRet->unLastFreePos = 64;

	kbRet = KLcmReinitMapNode(pRet);
	KL_PROCESS_ERROR(kbRet);

	*ppRet = pRet;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KL_DLLEXPORT KLcBool KLcmCreateMapKeyValue(KLCMAP_PTR pTag, KTVALUE_PTR pKey, KTVALUE_PTR* ppRetValue)
{
	/* Annotation info: https://www.cnblogs.com/hatsuzuki/p/17931246.html */
	KLcBool kbRet					= KL_FALSE;
	KLcBool kbIsKvLegal				= KL_FALSE;
	unsigned int nInsertPos			= 0;
	unsigned int nFreePos			= -1;
	unsigned int nCollisionPos		= 0;
	KLCMAPNODE_PTR ptMainNode		= NULL;
	KLCMAPNODE_PTR ptCollisionNode	= NULL;

	kbRet = KLcmGetIsLegalKv(pKey, &kbIsKvLegal);
	KL_PROCESS_ERROR(kbRet && kbIsKvLegal);

	kbRet = KLcmGetHashKeyPosition(pTag, pKey, &nInsertPos);
	KL_PROCESS_ERROR(kbRet);
	ptMainNode = pTag->parrNode[nInsertPos];
	ptMainNode->ktValue.emType = KT_NULL;

	if (KL_TRUE != KLCMAP_CHECKNULL(ptMainNode))
	{
		kbRet = KLcmGetHashKeyFreePosition(pTag, &nFreePos);
		KL_PROCESS_ERROR(kbRet);

		if (KLCMAP_LACKOFSPACE != nFreePos)
		{
			kbRet = KLcmGetHashKeyPosition(pTag, &ptMainNode->uKey.Va.ktValue, &nCollisionPos);
			KL_PROCESS_ERROR(kbRet);
			ptCollisionNode = pTag->parrNode[nCollisionPos];

			if (nInsertPos != nCollisionPos)
			{
				while (KLCMAP_GETNEXT(ptCollisionNode) != ptMainNode)
				{
					ptCollisionNode = KLCMAP_GETNEXT(ptCollisionNode);
				}

				KLCMAP_GETKEY(ptMainNode)->Va.pNext = pTag->parrNode[nFreePos];
				*(pTag->parrNode[nFreePos]) = *ptMainNode;
				KLCMAP_GETKEY(ptMainNode)->Va.pNext = NULL;
				kbRet = KLcmSetNullKV(ptMainNode);
				KL_PROCESS_ERROR(kbRet);
			}
			else
			{
				KLCMAP_GETNEXT(pTag->parrNode[nFreePos]) = KLCMAP_GETNEXT(ptMainNode);
				KLCMAP_GETNEXT(ptMainNode) = pTag->parrNode[nFreePos];
				ptMainNode = pTag->parrNode[nFreePos];
			}
		}
		else
		{
		}
	}
	else
	{ }

	KLCMAP_GETKEY(ptMainNode)->Va.ktValue = *pKey;
	*ppRetValue = &ptMainNode->ktValue;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKeyPosition(KLCMAP_PTR pTag, KTVALUE_PTR pKey, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;

	switch (KLCMAP_GETTYPE(pKey))
	{
	case KT_VPTR:
		kbRet = KLcmGetHashKTVoidPointer(pKey->uValue.vp, punRet);
		KL_PROCESS_ERROR(kbRet);
		break;

	case KT_DOUBLE:
		kbRet = KLcmGetHashKTDouble(pKey->uValue.d, punRet);
		KL_PROCESS_ERROR(kbRet);
		break;

	case KT_INT:
		kbRet = KLcmGetHashKTInt(pKey->uValue.n, punRet);
		KL_PROCESS_ERROR(kbRet);
		break;

	case KT_PCHAR:
		kbRet = KLcmGetHashKTCharPointer(pKey->uValue.szp, punRet);
		KL_PROCESS_ERROR(kbRet);
		break;

	default:
		*punRet = 0;
		break;
	}

	*punRet = *punRet % (pTag->unSize);

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKTInt(const int cnSrc, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;
	*punRet = (unsigned int)cnSrc;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKTDouble(const double cdSrc, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;
	*punRet = (unsigned int)cdSrc;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKTVoidPointer(void* vp, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;
	*punRet = (unsigned int)(unsigned long)vp;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKTCharPointer(const char* cszpSrc, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;
	KLwGetSimpleHash(cszpSrc, strlen(cszpSrc) + 1, punRet);

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetIsLegalKv(KTVALUE_PTR pKv, KLcBool* pKbRet)
{
	KLcBool kbRet = KL_FALSE;
	*pKbRet = KL_TRUE;
	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmGetHashKeyFreePosition(KLCMAP_PTR pKv, unsigned int* punRet)
{
	KLcBool kbRet = KL_FALSE;
	while (0 <= pKv->unLastFreePos)
	{
		if (KT_NULL == pKv->parrNode[pKv->unLastFreePos--]->uKey.Va.ktValue.emType)
		{
			*punRet = pKv->unLastFreePos;
			break;
		}
		pKv->unLastFreePos--;
	}

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KL_DLLEXPORT KLcBool KLcmGetMapKeyStringValue(KLCMAP_PTR pTag, const char* cszpKey, KTVALUE_PTR* ppRet)
{
	KLcBool kbRet = KL_FALSE;
	KLCMAPNODE_PTR ptNode = NULL;
	unsigned int unPos = -1;
	
	KLcmGetHashKTCharPointer(cszpKey, &unPos);
	unPos = unPos % pTag->unSize;

	if (-1 != unPos)
	{
		ptNode = pTag->parrNode[unPos];
		while (NULL != ptNode)
		{
			if (NULL != KLCMAP_GETVAL(ptNode)
				&& KT_PCHAR == KLCMAP_GETKEY(ptNode)->Va.ktValue.emType
				&& 0 == strcmp(cszpKey, KLCMAP_GETKEY(ptNode)->Va.ktValue.uValue.cszp))
			{
				*ppRet = KLCMAP_GETVAL(ptNode);
				break;
			}
			else
			{
				ptNode = KLCMAP_GETNEXT(ptNode);
			}
		}
	}
	else
	{
		goto Exit0;
	}

	kbRet = KL_TRUE;

Exit0:
	return kbRet;
}

KLcBool KLcmSetNullKV(KLCMAPNODE_PTR pKv)
{
	KLcBool kbRet = KL_FALSE;

	KLCMAP_GETKEY(pKv)->Va.ktValue.emType = KT_NULL;
	KLCMAP_GETVAL(pKv)->emType = KT_NULL;

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}

KLcBool KLcmReinitMapNode(KLCMAP_PTR pTag)
{
	KLcBool kbRet = KL_FALSE;
	KLCMAPNODE_PTR ptmpNode = NULL;

	for (size_t i = 0; i < pTag->unSize; i++)
	{
		pTag->parrNode[i] = (KLCMAPNODE_PTR)malloc(sizeof(KLCMAPNODE));
		KL_PROCESS_ERROR(pTag->parrNode[i]);

		ptmpNode = pTag->parrNode[i];
		ptmpNode->uKey.Va.pNext = NULL;
		kbRet = KLcmSetNullKV(ptmpNode);
		KL_PROCESS_ERROR(kbRet);
	}

	kbRet = KL_TRUE;
Exit0:
	return kbRet;
}
