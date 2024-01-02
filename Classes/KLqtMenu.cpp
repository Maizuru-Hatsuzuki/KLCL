/********************************************************
* Filename		: KLqtMeun.cpp
* Creator		: lidiankai
* Date time		: 2023.12.06
* Description	: qt menu logic.
********************************************************/


#include "KLcPy.h"
#include "KLqtMenu.h"
#include "KBaseMacro.h"
#include "KLog.h"
#include "KLcContainer.h"
#include <process.h>


KLqBaseMenu* KLqBaseMenu::m_pSelf;

KLqBaseMenu::KLqBaseMenu()
{
	KLcBool klBool		= KL_FALSE;
	m_pMenuBar			= new QMenuBar();
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


	klBool = reInit();
	ASSERT(klBool);
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

	KLclDestroySinglyCirLinkedList(m_pListPyWorker);
	KLwUninitShareMem(&m_tCorMemPfeye);
}

KLqBool KLqBaseMenu::reInit()
{
	KLcBool klBool = KL_FALSE;
	m_tCorMemPfeye.wsMemName = WORKERNAME_W_PERFEYE;
	m_tCorMemPfeye.dwSize = sizeof(enum KLEM_SHAREMEMFLAGS);
	m_tPy3BreathPfeye = { KL_FALSE, WORKERNAME_W_PERFEYE, (LPKLTHREAD_WORKER_FN)KLqBaseMenu::kqThLaunchPfeye };

	klBool = KLclCreateSinglyCirLinkedList(&m_pListPyWorker);
	KL_PROCESS_ERROR(klBool);

	klBool = KLwThCreateThreadPool(MAX_KP_THREAD, &m_pThPoolPyBreath);
	ASSERT(klBool);

	klBool = KLwInitShareMem(&m_tCorMemPfeye);
	KL_PROCESS_ERROR(klBool);


	klBool = KL_TRUE;
Exit0:

	return klBool;
}

KLcBool KLqBaseMenu::initMenuWidget()
{
	return KL_TRUE;
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

void KLqBaseMenu::setThreadGIL(enum KLEM_PY3GILEVENT emEvent)
{
	switch (emEvent)
	{
	case KGIL_PERFEYE:
		m_emGILPfeye = PyGILState_Ensure();
		break;
	default:
		break;
	}

	return;
}

DWORD WINAPI KLqBaseMenu::kqThLaunchPfeye(LPVOID _vp)
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pArgs = (PPYOBJECT)_vp;
	KLqBaseMenu::getInstance()->setThreadGIL(KGIL_PERFEYE);

	// Python while will block here.
	klBool = KLP_LAUNCHCF_WITHNOARGS_ONFRAMEBREATH_NORET("WizardUltra", "UAPfeye");
	if (KL_TRUE == klBool)
	{
		KLQ_LOG(KLOG_INFO, L"End perfeye breath fn success.");
	}
	else
	{
		KLQ_LOG(KLOG_INFO, L"End perfeye breath fn failed.");
	}
	return klBool;
}
	
KLcBool KLqBaseMenu::kqeOnActionConnectPfEye()
{
	KLcBool klBool							= KL_FALSE;
	DWORD dwTidPfeye						= 0;
	PPYOBJECT pArgs							= NULL;
	KLW_THREADWORKER_PTR ptWorker			= NULL;
	KLCLINKEDLISTDATA_PTR ptWorkerRecord	= NULL;
	PyThreadState* pPyThreadState			= NULL;

	if (KL_FALSE == m_tPy3BreathPfeye.nIsInit)
	{
		pPyThreadState = _PyThreadState_UncheckedGet();
		klBool = KLwThCreateThreadWorker(L"[PY3 OnFrameBreathe] Perfeye", m_tPy3BreathPfeye.fn, NULL, &ptWorker);
		KL_PROCESS_ERROR(klBool);
		klBool = KLclCreateLinkedListData(KT_VPTR, (void*)ptWorker, m_tPy3BreathPfeye.cwsDesc, &ptWorkerRecord);
		KL_PROCESS_ERROR(klBool);
		klBool = m_pListPyWorker->Append(m_pListPyWorker, ptWorkerRecord);
		KL_PROCESS_ERROR(klBool);
		
		KLQ_LOG(KLOG_INFO, L"Connecting perfeye breath fn.");
		if (NULL != pPyThreadState)
		{
			PyEval_ReleaseThread(pPyThreadState);
		}
		klBool = m_pThPoolPyBreath->AddWorker(m_pThPoolPyBreath, ptWorker);
		KL_PROCESS_ERROR(klBool);

		klBool = KLwSetShareMem(&m_tCorMemPfeye, KMSHARE_INIT);
		KL_PROCESS_ERROR(klBool);

		m_tPy3BreathPfeye.nIsInit = KL_TRUE;
	}
	else
	{
		KLQ_LOG(KLOG_WARING, L"Perfeye breath fn is running.");
	}

	klBool = KL_TRUE;
Exit0:
	
	return klBool;
}

KLqBool KLqBaseMenu::kqeOnActionDisconnectPfEye()
{
	KLcBool klBool = KL_FALSE;
	PPYOBJECT pArgs = NULL;
	const int cnarrArgs[1] = { 0 };
	unsigned int unPfeyeWorkerPos = 0;

	if (KL_TRUE == m_tPy3BreathPfeye.nIsInit)
	{
		klBool = KLwSetShareMem(&m_tCorMemPfeye, KMSHARE_RELEASE);
		KL_PROCESS_ERROR(klBool);

		klBool = m_pListPyWorker->FindPos(m_pListPyWorker, NULL, WORKERNAME_W_PERFEYE, &unPfeyeWorkerPos);
		KL_PROCESS_ERROR(klBool);

		klBool = m_pListPyWorker->Remove(m_pListPyWorker, unPfeyeWorkerPos);
		KL_PROCESS_ERROR(klBool);

		KLqBaseMenu::getInstance()->setThreadGIL(KGIL_PERFEYE);
		PyGILState_Release(m_emGILPfeye);

		m_tPy3BreathPfeye.nIsInit = KL_FALSE;
	}
	else
	{
		KLQ_LOG(KLOG_WARING, L"Perfeye breath fn is not running.");
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}



