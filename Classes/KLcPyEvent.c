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

KL_DLLEXPORT void KLpGetPyTupleSize(PPYOBJECT pFnRet, __int64* pllRet)
{
	*pllRet = PyTuple_Size(pFnRet);
	return;
}

KL_DLLEXPORT KLcBool KLpAnalyzeSingleRet(PPYOBJECT pFnRet, __int64 llTagPos, const char* szpRetFormat, PPYOBJECT* ppRet)
{
	/*
		备注：这里拿到pyobject指针后，传出去在解析，在获取这里不做解析
		因为不知道python脚本返回的元组里面的类型是什么，传出去后根据
		业务逻辑在做解析，业务和框架分开，框架只做获取，解析是业务的事情。
		返回的结果在 ... 里，传入的指针里。
	*/
	KLcBool klBool = KL_FALSE;
	PPYOBJECT ptmpFnRet = NULL;

	*ppRet = PyTuple_GetItem(pFnRet, llTagPos);
	KL_PROCESS_ERROR(*ppRet);

	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(ptmpFnRet);
	return klBool;
}

KL_DLLEXPORT KLcBool KLpAnalyzeRetToLong(PPYOBJECT* arrpAnalyzeRet, __int64 llRetCount, long* arrlRet)
{
	KLcBool klBool = KL_FALSE;

	for (__int64 i = 0; i < llRetCount; i++)
	{
		arrlRet[i] = PyLong_AsLong(arrpAnalyzeRet[i]);
	}

	klBool = KL_TRUE;

Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLpAnalyzeRetToPChar(PPYOBJECT* arrpAnalyzeRet, __int64 llRetCount, char** arrpRet)
{
	KLcBool klBool = KL_FALSE;

	for (__int64 i = 0; i < llRetCount; i++)
	{
		arrpRet[i] = PyUnicode_AsUTF8(arrpAnalyzeRet[i]);
	}

	klBool = KL_TRUE;

Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLpAnalyzeRetTupleToPChar(PPYOBJECT pRetTuple, char** arrpRet)
{
	KLcBool klBool = KL_FALSE;
	Py_ssize_t llSize = 0;
	PPYOBJECT ptmpTag = NULL;

	klBool = PyTuple_Check(pRetTuple);
	KL_PROCESS_ERROR(klBool);

	llSize = PyTuple_Size(pRetTuple);

	for (__int64 i = 0; i < llSize; i++)
	{
		ptmpTag = PyTuple_GetItem(pRetTuple, i);
		arrpRet[i] = PyUnicode_AsUTF8(ptmpTag);
		KLpGetLastError();
	}

	klBool = KL_TRUE;
	
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLpLaunchClassFn(
	const char* cszpModule, const char* cszpClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat, PPYOBJECT* ppRet
)
{
	KLcBool klBool		= KL_FALSE;
	int nRetInt			= -1;
	PPYOBJECT pModule	= NULL;
	PPYOBJECT pClass	= NULL;
	PPYOBJECT pClassRet = NULL;
	PPYOBJECT* arrpRet	= NULL;
	
	pModule = PyImport_ImportModule(cszpModule);
	KLP_PROCESS_ERROR(pModule);

	klBool = KLpGetClassInstance(pModule, cszpClass, &pClass);
	KLP_PROCESS_ERROR(klBool);

	klBool = KLpExcutePy3ClassFn(pClass, cszpFn, pArgs, cszpArgsFormat, &pClassRet);
	KLP_PROCESS_ERROR(klBool);

	if (NULL != ppRet)
	{
		// Need copy fn result.
		*ppRet = pClassRet;
	}
	else
	{
	}
	
	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pModule);
	KLP_RELEASE(pClassRet);
	
	return klBool;
}

KL_DLLEXPORT KLcBool KLpLaunchFn(
	const char* cszpModule, const char* cszpFn, PPYOBJECT pArgs, PPYOBJECT* ppRet
)
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

	pFnRet = PyObject_CallObject(pFn, pArgs);
	KLP_PROCESS_ERROR(pFnRet);

	if (NULL != ppRet)
	{
		// Need copy fn result.
		*ppRet = pFnRet;
	}
	else
	{
	}
	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pModule);
	KLP_RELEASE(pFn);
	KLP_RELEASE(pFnRet);
	return klBool;
}
