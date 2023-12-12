/********************************************************
* Filename		: KLqtMeun.cpp
* Creator		: lidiankai
* Date time		: 2023.12.06
* Description	: qt menu logic.
********************************************************/

#include <thread>
#include "KLcPy.h"
#include "KLqtMenu.h"
#include "KBaseMacro.h"
#include "KLog.h"



KLqBaseMenu* KLqBaseMenu::m_pSelf;

KLqBaseMenu::KLqBaseMenu()
{

	m_pMenuBar = new QMenuBar();
	// Menu bar.
	m_pMenuNew			= KLQ_NEW(QMenu, "New");
	m_pMenuCollector	= KLQ_NEW(QMenu, "ATsumeru");
	m_pMenuSetting		= KLQ_NEW(QMenu, "Settei");
	m_pMenuAbout		= KLQ_NEW(QMenu, "About");
	// Menu action.
	m_pMenu1stPerfeye		= KLQ_NEW(QMenu, "Perfeye");
	m_pAcPerfeyeConnect		= KLQ_NEW(QAction, "Connect");
	m_pAcPerfeyeDisconnect	= KLQ_NEW(QAction, "Disconnect");
	
	m_pMenuCollector->addMenu(m_pMenu1stPerfeye);
	m_pMenu1stPerfeye->addAction(m_pAcPerfeyeConnect);
	m_pMenu1stPerfeye->addAction(m_pAcPerfeyeDisconnect);
	m_pMenuCollector->addSeparator();

	m_pMenuBar->addMenu(m_pMenuNew);
	m_pMenuBar->addMenu(m_pMenuCollector);
	m_pMenuBar->addMenu(m_pMenuSetting);
	m_pMenuBar->addMenu(m_pMenuAbout);

	this->connect(m_pAcPerfeyeConnect, &QAction::triggered, this, &KLqBaseMenu::kqeOnActionConnectPfEye);
	this->connect(m_pAcPerfeyeDisconnect, &QAction::triggered, this, &KLqBaseMenu::kqeOnActionDisconnectPfEye);
}

KLqBaseMenu::~KLqBaseMenu()
{
	KLQ_RELEASE(m_pAcPerfeyeDisconnect);
	KLQ_RELEASE(m_pAcPerfeyeConnect);
	KLQ_RELEASE(m_pMenu1stPerfeye);
	KLQ_RELEASE(m_pMenuNew);
	KLQ_RELEASE(m_pMenuCollector);
	KLQ_RELEASE(m_pMenuSetting);
	KLQ_RELEASE(m_pMenuNew);
	KLQ_RELEASE(m_pMenuBar);
	KLQ_RELEASE(m_pSelf);
}

KLqBaseMenu* KLqBaseMenu::getInstance()
{
	if (NULL == m_pSelf)
	{
		m_pSelf = new KLqBaseMenu();
	}

	return m_pSelf;
}

PQMENUBAR KLqBaseMenu::getMenuBar()
{
	return m_pMenuBar;
}

DWORD WINAPI KLqBaseMenu::kqThLaunchPfeye(LPVOID vp, LPVOID _vp)
{
	KLcBool klBool = KL_FALSE;
	PyGILState_STATE gState;
	PPYOBJECT pArgs = (PPYOBJECT)_vp;

	gState = PyGILState_Ensure();
	klBool = KLP_LAUNCHCF_WITHARGS_UMAIN("WizardUltra", "UAConnectPfeye", pArgs, "O");
	ASSERT(klBool);
	PyGILState_Release(gState);
	return klBool;
}
	
KLcBool KLqBaseMenu::kqeOnActionConnectPfEye()
{
	KLcBool klBool = KL_FALSE;
	DWORD dwTidPfeye = 0;
	std::thread thPfEye;
	PyThreadState* pPyThState = NULL;
	PPYOBJECT pArgs = NULL;
	const int cnarrArgs[1] = { 1 };

	KLpGetPyTupleInt(1, cnarrArgs, &pArgs);
	KL_PROCESS_ERROR(pArgs);
	
	KLQ_LOG(KLOG_INFO, L"Connecting perfeye.");

	PyEval_InitThreads();
	Py_BEGIN_ALLOW_THREADS
		thPfEye = std::thread(KLqBaseMenu::kqThLaunchPfeye, this, pArgs);
		thPfEye.join();
		Sleep(2000);

	if (NULL == m_hThPfEye)
	{
		KLQ_LOG(KLOG_INFO, L"Connect perfeye failed.");
	}
	else
	{
		KLQ_LOG(KLOG_INFO, L"Connect perfeye success.");
		klBool = KL_TRUE;
	}
	Py_END_ALLOW_THREADS

Exit0:
	return klBool;
}

KLqBool KLqBaseMenu::kqeOnActionDisconnectPfEye()
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pArgs = NULL;
	const int cnarrArgs[1] = { 0 };

	KLpGetPyTupleInt(1, cnarrArgs, &pArgs);
	KL_PROCESS_ERROR(pArgs);

	klBool = KLP_LAUNCHCF_WITHARGS_UMAIN("WizardUltra", "UAConnectPfeye", pArgs, "O");
	KL_PROCESS_ERROR(klBool);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}



