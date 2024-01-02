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

KL_DLLEXPORT KLcBool KLpAnalyzeRet(PPYOBJECT pFnRet, __int64* pllRetCount, ...)
{
	/*
		��ע�������õ�pyobjectָ��󣬴���ȥ�ڽ������ڻ�ȡ���ﲻ������
		��Ϊ��֪��python�ű����ص�Ԫ�������������ʲô������ȥ�����
		ҵ���߼�����������ҵ��Ϳ�ֿܷ������ֻ����ȡ��������ҵ������顣
		���صĽ���� ... ������ָ���
	*/
	KLcBool klBool = KL_FALSE;
	va_list vaRet;
	char* szpRetFormat = NULL;
	__int64 llRetCount = 0;

	llRetCount = PyTuple_Size(pFnRet);
	*pllRetCount = llRetCount;

	szpRetFormat = (char*)malloc(llRetCount * sizeof(char) + 1);
	KL_PROCESS_ERROR(szpRetFormat);
	for (size_t i = 0; i < llRetCount; i++)
	{
		// Default type 'O', get pyobject then use other analyzes fn to get it.
		*(szpRetFormat + i) = 'O';
	}
	*(szpRetFormat + llRetCount) = '\0';

	va_start(vaRet, pllRetCount);
	PyArg_VaParse(pFnRet, szpRetFormat, vaRet);
	va_end(vaRet);

	KLLOG(KLOG_INFO, L"Get pyObject ret success, total %ld.", llRetCount);

	klBool = KL_TRUE;

Exit0:
	KL_RELEASE(szpRetFormat);
	return klBool;
}

KL_DLLEXPORT KLcBool KLpAnalyzeRetToLong(PPYOBJECT* arrpAnalyzeRet, __int64 llRetCount, long* arrlRet)
{
	KLcBool klBool = KL_FALSE;

	for (size_t i = 0; i < llRetCount; i++)
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

	for (size_t i = 0; i < llRetCount; i++)
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
	DWORD dwSize = 0;
	PPYOBJECT ptmpTag = NULL;

	klBool = PyTuple_Check(pRetTuple);
	KL_PROCESS_ERROR(klBool);

	dwSize = PyTuple_Size(pRetTuple);

	for (size_t i = 0; i < dwSize; i++)
	{
		ptmpTag = PyTuple_GetItem(pRetTuple, i);
		arrpRet[i] = PyUnicode_AsUTF8(ptmpTag);
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
