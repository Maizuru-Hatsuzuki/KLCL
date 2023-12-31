/********************************************************
* Filename		: KLcPy.c
* Creator		: lidiankai
* Date time		: 2023.12.04
* Description	: KLCL connect python frame.
********************************************************/


#include "KLcPy.h"
#include "KLog.h"
#include "KBaseMacro.h"
#include <stdlib.h>

g_emLastErrCode = KLEM_ERR_NONE;

KL_DLLEXPORT KLcBool KLpInitPy3()
{
	KLcBool klBool = KL_FALSE;
	PyObject* pSysPath = NULL;
	PyObject* pPath = NULL;
	WCHAR wszarrPyPath[MAX_PATH]		= { 0 };
	WCHAR wszarrPyFullPath[MAX_PATH]	= { 0 };
	char szarrPyScriptSrcPath[MAX_PATH] = { 0 };
	char szarrSysAppend[MAX_PATH + 19]	= { 0 };

	klBool = GetPrivateProfileString(L"KLcPy", L"szPythonPath", NULL, wszarrPyPath, MAX_PATH, L".\\config.ini");
	KL_PROCESS_ERROR(klBool);

	_wfullpath(wszarrPyFullPath, wszarrPyPath, MAX_PATH);
	_fullpath(szarrPyScriptSrcPath, "Src", MAX_PATH);
	KLwSetPCharBackslash(szarrPyScriptSrcPath);

	Py_SetPythonHome(wszarrPyFullPath);
	Py_Initialize();
	klBool = Py_IsInitialized();
	KLP_PROCESS_ERROR(klBool);

	pSysPath = PySys_GetObject("path");
	if (NULL == pSysPath || !PyList_Check(pSysPath))
	{
		goto Exit0;
	}
	pPath = PyUnicode_FromString(szarrPyScriptSrcPath);
	PyList_Insert(pSysPath, 0, pPath);

	PyEval_InitThreads();
	klBool = PyEval_ThreadsInitialized();
	KLP_PROCESS_ERROR(klBool);
	
#ifdef KLP_DEBUG_FLAG
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("for i in sys.path: print(i)");
#endif

Exit0:
	if (NULL != pPath)
	{
		Py_DECREF(pPath);
	}
	return klBool;
}

KL_DLLEXPORT KLcBool KLpUninitPy3()
{
	KLcBool klBool = KL_FALSE;

	klBool = Py_IsInitialized();
	if (KL_TRUE == klBool)
	{
		klBool = Py_FinalizeEx();
		KL_PROCESS_SUCCESS(-1 == klBool);
	}

	KLLOG(KLOG_INFO, L"Uninit klp python3 success!");
	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLcBool KLpGetClassInstance(PPYOBJECT pPyFileObject, const char* cszpClassname, PPYOBJECT* ppClass)
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pModuleDict = NULL;

	// pModuleDict & pClass don't need Py_DECREF, 2 object is borrowed reference, Py_Finalize can release it.
	// https://stackoverflow.com/questions/6757741/py-finalize-crashes-after-error-in-python
	pModuleDict = PyModule_GetDict(pPyFileObject);
	KLP_PROCESS_ERROR(pModuleDict);

	*ppClass = PyDict_GetItemString(pModuleDict, cszpClassname);
	KLP_PROCESS_ERROR(*ppClass);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLpGetLastError()
{
	KLcBool klBool = KL_TRUE;
	PyObject* pExcType = NULL;
	PyObject* pExcValue = NULL;
	PyObject* pExcTraceback = NULL;
	PyObject* pErrstr = NULL;
	const char* szpLastErrMsg = "";

	PyErr_Fetch(&pExcType, &pExcValue, &pExcTraceback);

	if (NULL != pExcValue)
	{
		PyErr_NormalizeException(&pExcType, &pExcValue, &pExcTraceback);
		pErrstr = PyObject_Str(pExcValue);
		szpLastErrMsg = PyUnicode_AsUTF8(pErrstr);

		klBool = KPrettyPrintfA(KLOG_ERROR, "PY ERR -> %s", szpLastErrMsg);
		KL_PROCESS_ERROR(klBool);
		KLpGetMatchingErrorCode(szpLastErrMsg);
		klBool = KL_FALSE;
	}
	else
	{
	}

Exit0:
	KLP_RELEASE(pExcType);
	KLP_RELEASE(pExcValue);
	KLP_RELEASE(pExcTraceback);
	KLP_RELEASE(pErrstr);
	return klBool;
}

KL_DLLEXPORT const int KLpGetMatchingErrorCode(const char* cszpMatchingErr)
{
	int nMatching = -1;
	if (0 == strcmp(KLP_ERRMSG_TYPEERR_NONETYPE, cszpMatchingErr))
	{
		nMatching = 0;
		g_emLastErrCode = KLEM_ERR_TYPEERR_NONETYPE;
	} 
	else
	{
	}
	
	return nMatching;
}

KLcBool KLpExcutePy3ClassFn(PPYOBJECT pClass, const char* cszpFn, PPYOBJECT pArgs, const char* cszpArgsFormat, PPYOBJECT* ppClassRet)
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pClassConstruct = NULL;
	PPYOBJECT pClassIns = NULL;

	pClassConstruct = PyInstanceMethod_New(pClass);
	KLP_PROCESS_ERROR(pClassConstruct);

	pClassIns = PyObject_CallObject(pClassConstruct, NULL);
	KLP_PROCESS_ERROR(pClassIns);

	if (NULL == cszpArgsFormat)
	{
		*ppClassRet = PyObject_CallMethod(pClassIns, cszpFn, NULL);
		KLP_PROCESS_ERROR(*ppClassRet);
	}
	else
	{
		*ppClassRet = PyObject_CallMethod(pClassIns, cszpFn, cszpArgsFormat, pArgs);
		KLP_PROCESS_ERROR(*ppClassRet);
	}
	

	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pClassConstruct);
	KLP_RELEASE(pClassIns);
	return klBool;
}
