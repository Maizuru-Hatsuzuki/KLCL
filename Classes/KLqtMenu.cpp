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

	this->connect(m_pAcPerfeyeConnect, &QAction::triggered, this, &KLqBaseMenu::KLqeOnActionConnectPfEye);
	this->connect(m_pAcPerfeyeDisconnect, &QAction::triggered, this, &KLqBaseMenu::KLqeOnActionDisconnectPfEye);
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
	
KLcBool KLqBaseMenu::KLqeOnActionConnectPfEye()
{
	KLcBool klBool = KL_FALSE;
	KLLOG(KLOG_INFO, L"Connecting perfeye.");
	/*klBool = KLP_LAUNCHCF_UMAIN("WizardUltra", "UAConnectPfeye");
	KL_PROCESS_ERROR(klBool);*/
	KLLOG(KLOG_INFO, L"Connect perfeye success.");

	klBool = KL_TRUE;
Exit0:
	return klBool;
}

KLqBool KLqBaseMenu::KLqeOnActionDisconnectPfEye()
{
	KLcBool klBool = KL_FALSE;
	klBool = KLP_LAUNCHCF_UMAIN("WizardUltra", "UADisconnectPfeye");
	KL_PROCESS_ERROR(klBool);

	klBool = KL_TRUE;
Exit0:
	return klBool;
}



