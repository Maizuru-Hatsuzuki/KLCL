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

#define KLP_RELEASE(p)																	{ if (p) { Py_DecRef(p); (p) = NULL; } }
#define ASSERT_KLPRET(fnRet, klpRet)													{ PyArg_Parse(fnRet, "i", &klpRet); KLpGetLastError(); ASSERT(!(KLEM_ERR_TYPEERR_NONETYPE == g_emLastErrCode)); }

#define KLP_LAUNCHCF_WITHNOARGS_UMAIN(cszpModule, cszpClass)							KLpLaunchClassFn(cszpModule, cszpClass, "UMain", NULL, NULL)
#define KLP_LAUNCHCF_WITHARGS_UMAIN(cszpModule, cszpClass, pArgs, cszpArgsFormat)		KLpLaunchClassFn(cszpModule, cszpClass, "UMain", pArgs, cszpArgsFormat)
#define KLP_LAUNCHCF_WITHNOARGS_ONFRAMEBREATH(cszpModule, cszpClass)					KLpLaunchClassFn(cszpModule, cszpClass, "OnFrameBreath", NULL, NULL)
#define KLP_LAUNCHF_UMAIN(cszpModule)													KLpLaunchFn(cszpModule, "UMain")


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
	KL_DLLEXPORT KLcBool KLpLaunchClassFn(const char* cszpModule, const char* cszpClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat);
	KL_DLLEXPORT KLcBool KLpLaunchFn(const char* cszpModule, const char* cszpFn);
	KL_DLLEXPORT KLcBool KLpGetLastError();
	KL_DLLEXPORT const int KLpGetMatchingErrorCode(const char* cszpMatchingErr);
	KL_DLLEXPORT void KLpGetPyTupleInt(const int cnArgsCount, const int* cnarrData, PPYOBJECT* ppRet);
#ifdef __cplusplus
}
#endif

#endif
