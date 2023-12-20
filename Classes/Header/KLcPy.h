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

#define KLP_RELEASE(p)																		{ if (p) { Py_DecRef(p); (p) = NULL; } }
#define KLP_LAUNCHCF_WITHNOARGS_UMAIN_NORET(cszpModule, cszpClass)							KLpLaunchClassFn(cszpModule, cszpClass, "UMain", NULL, NULL, NULL)
#define KLP_LAUNCHCF_WITHARGS_UMAIN_NORET(cszpModule, cszpClass, pArgs, cszpArgsFormat)		KLpLaunchClassFn(cszpModule, cszpClass, "UMain", pArgs, cszpArgsFormat, NULL)
#define KLP_LAUNCHCF_WITHNOARGS_ONFRAMEBREATH_NORET(cszpModule, cszpClass)					KLpLaunchClassFn(cszpModule, cszpClass, "OnFrameBreath", NULL, NULL, NULL)
#define KLP_LAUNCHF_UMAIN_NORET(cszpModule)													KLpLaunchFn(cszpModule, "UMain", NULL, NULL)
#define KLP_CREATETHREAD_GET_GIL															PyGILState_STATE k = PyGILState_Ensure()


enum KLEM_PYRETTYPE
{
	KPRET_INT,
	KPRET_TUPLE
};

struct _tPy3OnFrameBreathDesc
{
	KLcBool nIsInit;
	LPCWSTR cwsDesc;
	LPKLTHREAD_WORKER_FN fn;
};
typedef struct _tPy3OnFrameBreathDesc KLP_PY3ONFRAMEBREATHDESC, * KLP_PY3ONFRAMEBREATHDESC_PTR;
typedef PyObject* PPYOBJECT;


extern enum KLEM_PYERR g_emLastErrCode;

KLcBool KLpGetClassInstance(PPYOBJECT pPyFileObject, const char* cszpClassname, PPYOBJECT* ppClass);
KLcBool KLpExcutePy3ClassFn(PPYOBJECT pClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat, PPYOBJECT* ppClassRet);

#ifdef __cplusplus
extern "C" {
#endif	
	// KL Python frame.
	KL_DLLEXPORT KLcBool KLpInitPy3();
	KL_DLLEXPORT KLcBool KLpUninitPy3();
	KL_DLLEXPORT KLcBool KLpLaunchClassFn(
		const char* cszpModule, const char* cszpClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat, PPYOBJECT* ppRet
	);
	KL_DLLEXPORT KLcBool KLpLaunchFn(const char* cszpModule, const char* cszpFn, PPYOBJECT pArgs, PPYOBJECT* ppRet);
	KL_DLLEXPORT KLcBool KLpAnalyzeRet(PPYOBJECT pFnRet, __int64* pllRetCount, ...);
	KL_DLLEXPORT KLcBool KLpAnalyzeRetToLong(PPYOBJECT* arrpAnalyzeRet, __int64 llRetCount, long* arrlRet);
	KL_DLLEXPORT KLcBool KLpAnalyzeRetToPChar(PPYOBJECT* arrpAnalyzeRet, __int64 llRetCount, char** arrpRet);
	KL_DLLEXPORT KLcBool KLpGetLastError();
	KL_DLLEXPORT const int KLpGetMatchingErrorCode(const char* cszpMatchingErr);
	KL_DLLEXPORT void KLpGetPyTupleInt(const int cnArgsCount, const int* cnarrData, PPYOBJECT* ppRet);
#ifdef __cplusplus
}
#endif

#endif
