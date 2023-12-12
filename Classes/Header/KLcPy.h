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
#define ASSERT_KLPRET(fnRet, klpRet) { PyArg_Parse(fnRet, "i", &klpRet); KLpGetLastError(); ASSERT(!(KLEM_ERR_TYPEERR_NONETYPE == g_emLastErrCode)); }

#define KLP_LAUNCHCF_WITHNOARGS_UMAIN(cszpModule, cszpClass)							KLpLaunchClassFn(cszpModule, cszpClass, "UMain", NULL, NULL)
#define KLP_LAUNCHCF_WITHARGS_UMAIN(cszpModule, cszpClass, pArgs, cszpArgsFormat)		KLpLaunchClassFn(cszpModule, cszpClass, "UMain", pArgs, cszpArgsFormat)
#define KLP_LAUNCHF_UMAIN(cszpModule)													KLpLaunchFn(cszpModule, "UMain")

typedef PyObject* PPYOBJECT;

#define KL_INTERFACE struct _tKlpPy3ObjectArray
#define KTHIS KL_INTERFACE* pThis

extern enum KLEM_PYERR g_emLastErrCode;

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
	KBOOLFN(Append)(KTHIS, KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
	KBOOLFN(Remove)(KTHIS, unsigned int unPos);
};
typedef struct _tKlpPy3ObjectArray KLPPY3OBJECTARRAY, * KLPPY3OBJECTARRAY_PTR;

struct _tKlpPy3Desc
{
	PPYOBJECT pMoudle;
	PPYOBJECT pMouduleDict;
	KLPPY3OBJECTARRAY_PTR ptPy3ClassArray;
};

#undef KL_INTERFACE

// KL Python data struct.
KLcBool KLpdCreatePy3ObjectArray(KLPPY3OBJECTARRAY_PTR* ppArray);
KLcBool KLpdDeletePy3ObjectArray(KLPPY3OBJECTARRAY_PTR pArray);
KLcBool KLpdAppendPy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
KLcBool KLpdRemovePy3ObjectArrayNode(KLPPY3OBJECTARRAY_PTR pArray, unsigned int unPos);
void KLpdCreatePy3ObjectArrayFn(KLPPY3OBJECTARRAY_PTR pArray);
void KLpdRealsePy3ObjectNodeData(KLPPY3OBJECTLINKCONTAINERDATA_PTR pData);
KLcBool KLpGetClassInstance(PPYOBJECT pPyFileObject, const char* cszpClassname, PPYOBJECT* ppClass);
KLcBool KLpExcutePy3ClassFn(PPYOBJECT pClass, const char* cszpFn, PPYOBJECT* pArgs, const char* cszpArgsFormat, PPYOBJECT* ppClassRet);

#ifdef __cplusplus
extern "C" {
#endif	
	// KL Python frame.
	KL_DLLEXPORT KLcBool KLpInitPy3();
	KL_DLLEXPORT KLcBool KLpUninitPy3();
	KL_DLLEXPORT KLcBool KLpLaunchClassFn(const char* cszpModule, const char* cszpClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat);
	KL_DLLEXPORT KLcBool KLpLaunchFn(const char* cszpModule, const char* cszpFn);
	KL_DLLEXPORT KLcBool KLpGetLastError();
	KL_DLLEXPORT const int KLpGetMatchingErrorCode(const char* cszpMatchingErr);
	KL_DLLEXPORT KLcBool KLpGetPyTupleInt(const int cnArgsCount, const int* cnarrData, PPYOBJECT* ppRet);
#ifdef __cplusplus
}
#endif

#endif
