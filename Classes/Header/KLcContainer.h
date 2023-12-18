/********************************************************
* Filename		: KLcContainer.h
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#ifndef __KLCONTAINER_H__
#define __KLCONTAINER_H__

#include "KBase.h"
#include "KLcWin.h"

enum KLEM_GENERICS
{
	KT_INT,
	KT_VPTR,
	KT_USERPTR,
};

#define KL_INTERFACE struct _tKlcSinglyCircularLinkedListNode
#define KTHIS KL_INTERFACE* pThis

struct _tKlcContainerLinkedListData
{
	void* vpData;
	enum KLEM_GENERICS emType;
	LPCWSTR cwsWorkerName;
};
typedef struct _tKlcContainerLinkedListData KLCLINKEDLISTDATA, * KLCLINKEDLISTDATA_PTR;

struct _tKlcSinglyCircularLinkedListNode
{
	unsigned int unCount;
	KLCLINKEDLISTDATA_PTR pData;
	struct _tKlcSinglyCircularLinkedListNode* ptHeadNode;
	struct _tKlcSinglyCircularLinkedListNode* ptTailNode;
	struct _tKlcSinglyCircularLinkedListNode* ptNext;
	KBOOLFN(Append)(KTHIS, KLCLINKEDLISTDATA_PTR pData);
	KBOOLFN(Remove)(KTHIS, unsigned int unPos);
	KBOOLFN(FindPos)(KTHIS, KLCLINKEDLISTDATA_PTR pData, LPCWSTR cwsTag, unsigned int* punRet);
};
typedef struct _tKlcSinglyCircularLinkedListNode KLCSINGCIRLINKEDLIST, * KLCSINGCIRLINKEDLIST_PTR;
typedef KLCSINGCIRLINKEDLIST_PTR KLC_SCLIST;

#undef KL_INTERFACE

KLcBool KLcSingCirLinkedListNodeAppend(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData);
KLcBool KLcSingCirLinkedListNodeRemove(KLCSINGCIRLINKEDLIST_PTR pThis, unsigned int unPos);
KLcBool KLcSingCirLinkedListNodeFindPos(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData, LPCWSTR cwsTag, unsigned int* punRet);
void KLcSingCirLinkedListNodeInitFn(KLCSINGCIRLINKEDLIST_PTR pThis);

#ifdef __cplusplus
extern "C" {
#endif	
	KL_DLLEXPORT KLcBool KLcCreateSinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR* ppRet);
	KL_DLLEXPORT KLcBool KLcCreateLinkedListData(enum KLEM_GENERICS emType, void* vpData, LPCWSTR cwsWorkerName, KLCLINKEDLISTDATA_PTR* ppRet);
	KL_DLLEXPORT void KLcDestroySinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR pList);
	KL_DLLEXPORT void KLcDestroyLinkedListData(KLCLINKEDLISTDATA_PTR pData);
#ifdef __cplusplus
}
#endif

#endif
