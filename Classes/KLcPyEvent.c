/********************************************************
* Filename		: KLcPyEvent.c
* Creator		: lidiankai
* Date time		: 2023.12.04
* Description	: KLCL private python event.
********************************************************/


#include "KLcPy.h"
#include "KLog.h"
#include "KBaseMacro.h"

KL_DLLEXPORT void KLpGetPyTupleInt(const int cnArgsCount, const int* cnarrData, PPYOBJECT* ppRet)
{
	PyObject* pArgs = PyTuple_New(cnArgsCount);
	
	for (size_t i = 0; i < cnArgsCount; i++)
	{
		PyTuple_SetItem(pArgs, i, Py_BuildValue("i", cnarrData[i]));
	}
	*ppRet = pArgs;
}

KL_DLLEXPORT KLcBool KLpLaunchClassFn(const char* cszpModule, const char* cszpClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat)
{
	KLcBool klBool = KL_FALSE;
	KLpFnRet klpRet = KLP_FALSE;
	PPYOBJECT pModule = NULL;
	PPYOBJECT pClass = NULL;
	PPYOBJECT pClassRet = NULL;

	pModule = PyImport_ImportModule(cszpModule);
	KLP_PROCESS_ERROR(pModule);

	klBool = KLpGetClassInstance(pModule, cszpClass, &pClass);
	KLP_PROCESS_ERROR(klBool);

	klBool = KLpExcutePy3ClassFn(pClass, cszpFn, pArgs, cszpArgsFormat, &pClassRet);
	KLP_PROCESS_ERROR(klBool);
	ASSERT_KLPRET(pClassRet, klpRet);

	KPrettyPrintfA(KLOG_INFO, "KLpeLaunchClassFn %s::%s in %s, ret: %d", cszpClass, cszpFn, cszpModule, klpRet);
	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pModule);
	KLP_RELEASE(pClassRet);
	
	return klBool;
}

KL_DLLEXPORT KLcBool KLpLaunchFn(const char* cszpModule, const char* cszpFn)
{
	KLcBool klBool = KL_FALSE;
	KLpFnRet klpRet = KLP_FALSE;
	PPYOBJECT pModule = NULL;
	PPYOBJECT pFn = NULL;
	PPYOBJECT pFnRet = NULL;

	pModule = PyImport_ImportModule(cszpModule);
	KLP_PROCESS_ERROR(pModule);

	pFn = PyObject_GetAttrString(pModule, cszpFn);
	KLP_PROCESS_ERROR(pFn);

	pFnRet = PyObject_CallObject(pFn, NULL);
	KLP_PROCESS_ERROR(pFnRet);
	ASSERT_KLPRET(pFnRet, klpRet);

	KPrettyPrintfA(KLOG_INFO, "KLpeLaunchClassFn %s in %s, ret: %d", cszpFn, cszpModule, klpRet);
	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pModule);
	KLP_RELEASE(pFn);
	KLP_RELEASE(pFnRet);
	return klBool;
}
