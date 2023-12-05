/********************************************************
* Filename		: KLcPyEvent.c
* Creator		: lidiankai
* Date time		: 2023.12.04
* Description	: KLCL private python event.
********************************************************/

#define KL_DLLEXPORT

#include "KLcPy.h"
#include "KLog.h"
#include "KBaseMacro.h"


KL_DLLEXPORT KLcBool KLpePfEyeLaunch()
{
	KLcBool klBool = KL_FALSE;
	KLpFnRet klpRet = KLP_FALSE;
	PPYOBJECT pModule = NULL;
	PPYOBJECT pClass = NULL;
	PPYOBJECT pClassRet = NULL;

	pModule = PyImport_ImportModule("WizardUltra");
	KLP_PROCESS_ERROR(pModule);

	klBool = KLpGetClassInstance(pModule, "CwuKL25COM", &pClass);
	KLP_PROCESS_ERROR(klBool);

	klBool = KLpExcutePy3ClassFn(pClass, "getValue", &pClassRet);
	KLP_PROCESS_ERROR(klBool);

	PyArg_Parse(pClassRet, "i", &klpRet);
	KLpGetLastError();
	// if python function return is none, crash.
	ASSERT(!(KLEM_ERR_TYPEERR_NONETYPE == g_emLastErrCode));

	KLLOG(KLOG_INFO, L"PfEye launch ret: %d", klBool);
	klBool = KL_TRUE;

Exit0:
	KLP_RELEASE(pModule);
	KLP_RELEASE(pClassRet);
	return klBool;
}