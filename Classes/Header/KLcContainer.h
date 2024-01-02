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

#define KLCMAP_DEFAULTPKV			( &klcDefaultKV )
#define KLCMAP_CHECKNULL(t)			( KT_NULL == (t)->ktValue.emType ? KL_TRUE : KL_FALSE )
#define KLCMAP_GETNEXT(t)			( (t)->uKey.Va.pNext )
#define KLCMAP_GETKEY(t)			( &(t)->uKey )
#define KLCMAP_GETVAL(t)			( &(t)->ktValue )
#define KLCMAP_GETTYPE(t)			( (t)->emType )
#define KLCMAP_LACKOFSPACE			-1
#define KLCMAP_SETSTRINGKEYVALUE(m, k, s, v, b)					\
do																\
{																\
	k.emType = KT_PCHAR;										\
	k.uValue.cszp = s;											\
	b = KLcmCreateMapKeyValue(m, &k, &v);						\
	KL_PROCESS_ERROR(b);										\
} while (0);
#define KLCMAP_GETSTRINGKEYVALUE(m, k, pv)		KLcmGetMapKeyStringValue(m, k, pv)	


enum KLEM_GENERICS
{
	KT_NULL,
	KT_VPTR,
	KT_DOUBLE,
	KT_INT,
	KT_PCHAR,
};

/* Hash map struct */
#define KL_INTERFACE struct _tKlcMap
#define KTHIS KL_INTERFACE* pThis

union _uKTValue
{
	void* vp;
	double d;
	int n;
	char* szp;
	const char* cszp;
};

struct _tKTValue
{
	union _uKTValue uValue;
	enum KLEM_GENERICS emType;
};
typedef struct _tKTValue KTVALUE, * KTVALUE_PTR;

/* KLc map key. */
union _uKlcMapKey
{
	struct
	{
		KTVALUE ktValue;
		struct _tKlcMapNode* pNext;
	} Va;
	KTVALUE TVa;
};

/* KLc map node, include key(union) and value. */
struct _tKlcMapNode
{
	union _uKlcMapKey uKey;
	KTVALUE ktValue;
};
static const struct _tKlcMapNode klcDefaultKV =
{ 
	{{{ NULL, KT_NULL }, NULL }},
	{ NULL, KT_NULL }
};

struct _tKlcMap
{
	struct _tKlcMapNode** parrNode;
	unsigned int unLastFreePos;
	unsigned int unSize;

};
typedef struct _tKlcMapNode		KLCMAPNODE, * KLCMAPNODE_PTR;
typedef struct _tKlcMap			KLCMAP, * KLCMAP_PTR;


KLcBool KLcmGetHashKeyPosition(KLCMAP_PTR pTag, KTVALUE_PTR pKey, unsigned int* punRet);
KLcBool KLcmGetHashKTInt(const int cnSrc, unsigned int* punRet);
KLcBool KLcmGetHashKTDouble(const double cdSrc, unsigned int* punRet);
KLcBool KLcmGetHashKTVoidPointer(void* vp, unsigned int* punRet);
KLcBool KLcmGetHashKTCharPointer(const char* cszpSrc, unsigned int* punRet);
KLcBool KLcmGetIsLegalKv(KTVALUE_PTR pKv, KLcBool* pKbRet);
KLcBool KLcmGetHashKeyFreePosition(KLCMAP_PTR pKv, unsigned int* punRet);
KLcBool KLcmSetNullKV(KLCMAPNODE_PTR pKv);
KLcBool KLcmReinitMapNode(KLCMAP_PTR pTag);

#undef KL_INTERFACE


/* Linked list struct */
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

KLcBool KLclSingCirLinkedListNodeAppend(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData);
KLcBool KLclSingCirLinkedListNodeRemove(KLCSINGCIRLINKEDLIST_PTR pThis, unsigned int unPos);
KLcBool KLclSingCirLinkedListNodeFindPos(KLCSINGCIRLINKEDLIST_PTR pThis, KLCLINKEDLISTDATA_PTR pData, LPCWSTR cwsTag, unsigned int* punRet);
void	KLclSingCirLinkedListNodeInitFn(KLCSINGCIRLINKEDLIST_PTR pThis);

#undef KL_INTERFACE


#ifdef __cplusplus
extern "C" {
#endif
	/* Link list. */
	KL_DLLEXPORT KLcBool KLclCreateSinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR* ppRet);
	KL_DLLEXPORT KLcBool KLclCreateLinkedListData(enum KLEM_GENERICS emType, void* vpData, LPCWSTR cwsWorkerName, KLCLINKEDLISTDATA_PTR* ppRet);
	KL_DLLEXPORT void KLclDestroySinglyCirLinkedList(KLCSINGCIRLINKEDLIST_PTR pList);
	KL_DLLEXPORT void KLclDestroyLinkedListData(KLCLINKEDLISTDATA_PTR pData);

	/* Map. */
	KL_DLLEXPORT KLcBool KLcmCreateMap(KLCMAP_PTR* ppRet);
	KL_DLLEXPORT KLcBool KLcmCreateMapKeyValue(KLCMAP_PTR pTag, KTVALUE_PTR pKey, KTVALUE_PTR* ppRetValue);
	KL_DLLEXPORT KLcBool KLcmGetMapKeyStringValue(KLCMAP_PTR pTag, const char* cszpKey, KTVALUE_PTR* ppRet);
#ifdef __cplusplus
}
#endif

#endif
