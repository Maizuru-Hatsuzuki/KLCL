/********************************************************
* Filename		: KLcPy.h
* Creator		: lidiankai
* Date time		: 2023.12.04
* Description	: KLCL connect python frame.
********************************************************/

#ifndef __KLCPY_H__
#define __KLCPY_H__

#include "Python.h"
#include "KBase.h"
#include "KLcPyErrCode.h"
#include "KLcWin.h"

#define KLP_RELEASE(p) { if (p) { Py_DecRef(p); (p) = NULL; } }
#define KBOOLFN(fn) KLcBool (*fn)

typedef PyObject* PPYOBJECT;

#define INTERFACE struct _tKlpPy3ObjectArray
#define THIS INTERFACE* pThis

enum KLEM_PYERR g_emLastErrCode;

struct _tKlpPy3ObjectLinkContainerData
{
	const char cszarrClassname[32];
	PPYOBJECT pPyClass;
	PPYOBJECT pPyClassConstruct;
	PPYOBJECT pPyClassIns;
	PPYOBJECT pPyClassRet;
};
typedef struct _tKlpPy3ObjectLinkContainerData KLPPY3OBJECTLINKCONTAINERDATA, * KLPPY3OBJECTLINKCONTAINERDATA_PTR;

struct _tKlpPy3ObjectArray
{
	unsigned int unCount;
	KLPPY3OBJECTLINKCONTAINERDATA_PTR pData;
	struct _tKlpPy3ObjectArray* ptHeadNode;
	struct _tKlpPy3ObjectArray* ptTailNode;
	struct _tKlpPy3ObjectArray* ptNext;
	KBOOLFN(Append)(THIS, KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
	KBOOLFN(Remove)(THIS, unsigned int unPos);
};
typedef struct _tKlpPy3ObjectArray KLPPY3OBJECTARRAY, * KLPPY3OBJECTARRAY_PTR;

struct _tKlpPy3Desc
{
	PPYOBJECT pMoudle;
	PPYOBJECT pMouduleDict;
	KLPPY3OBJECTARRAY_PTR ptPy3ClassArray;
};

#undef INTERFACE

// KL Python data struct.
KLcBool KLpdCreatePy3ObjectArray(KLPPY3OBJECTARRAY_PTR* ppArray);
KLcBool KLpdDeletePy3ObjectArray(KLPPY3OBJECTARRAY_PTR pArray);
KLcBool KLpdAppendPy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
KLcBool KLpdRemovePy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, unsigned int unPos);
void KLpdCreatePy3ObjectArrayFn(KLPPY3OBJECTARRAY_PTR pArray);
void KLpdRealsePy3ObjectNodeData(KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
KLcBool KLpGetClassInstance(PPYOBJECT pPyFileObject, char* cszpClassname, PPYOBJECT* ppClass);
KLcBool KLpExcutePy3ClassFn(PPYOBJECT pClass, const char* cszpFn, PPYOBJECT* ppClassRet);

#ifdef __cplusplus
extern "C" {
#endif	
	// KL Python frame.
	KL_DLLEXPORT KLcBool KLpInitPy3();
	KL_DLLEXPORT KLcBool KLpUninitPy3();
	KL_DLLEXPORT KLcBool KLpGetLastError();
	KL_DLLEXPORT const int KLpGetMatchingErrorCode(const char* cszpMatchingErr);

	// KL Python (all private) event.
	KL_DLLEXPORT KLcBool KLpePfEyeLaunch();
#ifdef __cplusplus
}
#endif

#endif
