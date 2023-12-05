/********************************************************
* Filename		: KLcPy.c
* Creator		: lidiankai
* Date time		: 2023.12.04
* Description	: KLCL connect python frame.
********************************************************/

#define KL_DLLEXPORT

#include "KLcPy.h"
#include "KLcWin.h"
#include "KLog.h"
#include "KBaseMacro.h"


g_emLastErrCode = KLEM_ERR_NONE;

KL_DLLEXPORT KLcBool KLpInitPy3()
{
	KLcBool klBool = KL_FALSE;
	WCHAR wszarrPyPath[MAX_PATH] = { 0 };

	klBool = GetPrivateProfileString(L"KLcPy", L"szPythonPath", NULL, wszarrPyPath, MAX_PATH, L".\\config.ini");
	KLP_PROCESS_ERROR(klBool);

	Py_SetPythonHome(wszarrPyPath);
	Py_Initialize();
	klBool = Py_IsInitialized();
	KLP_PROCESS_ERROR(klBool);

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

Exit0:
	return klBool;
}

KL_DLLEXPORT KLcBool KLpUninitPy3(KLPPY3OBJECTLINKCONTAINERDATA_PTR pPy3ObjectData)
{
	KLcBool klBool = KL_FALSE;

	klBool = Py_IsInitialized();
	if (KL_TRUE == klBool)
	{
		Py_Finalize();
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLcBool KLpGetClassInstance(PPYOBJECT pPyFileObject, char* cszpClassname, PPYOBJECT* ppClass)
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
	char* szpLastErrMsg = "";

	PyErr_Fetch(&pExcType, &pExcValue, &pExcTraceback);

	if (NULL != pExcValue)
	{
		PyErr_NormalizeException(&pExcType, &pExcValue, &pExcTraceback);
		pErrstr = PyObject_Str(pExcValue);
		szpLastErrMsg = PyUnicode_AsUTF8(pErrstr);

		KPrettyPrintfA(KLOG_ERROR, "PY ERR -> %s", szpLastErrMsg);
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

KLcBool KLpExcutePy3ClassFn(PPYOBJECT pClass, const char* cszpFn, PPYOBJECT* ppClassRet)
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pClassConstruct = NULL;
	PPYOBJECT pClassIns = NULL;

	pClassConstruct = PyInstanceMethod_New(pClass);
	KLP_PROCESS_ERROR(pClassConstruct);

	pClassIns = PyObject_CallObject(pClassConstruct, NULL);
	KLP_PROCESS_ERROR(pClassIns);

	*ppClassRet = PyObject_CallMethod(pClassIns, cszpFn, NULL);
	KLP_PROCESS_ERROR(*ppClassRet);

	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pClassConstruct);
	KLP_RELEASE(pClassIns);
	return klBool;
}
