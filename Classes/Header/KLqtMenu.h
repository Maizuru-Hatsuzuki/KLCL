/********************************************************
* Filename		: KLqtMeun.cpp
* Creator		: lidiankai
* Date time		: 2023.12.06
* Description	: qt menu header file. 
* Help url		: https://www.cnblogs.com/kyzc/p/11962903.html
********************************************************/

#ifndef __KLQTMENU_H__
#define __KLQTMENU_H__

#include "KLclRay.h"
#include "KBase.h"


#define WORKERNAME_W_PERFEYE L"WorkerPy3_Perfeye"
#define WORKERNAME_W_PYLOG	 L"WorkerPy3_PyLog"

enum KLEM_PY3GILEVENT
{
	KGIL_PERFEYE
};

class KLqBaseMenu:
	public QWidget
{
public:
	PQMENUBAR getMenuBar();
	static KLqBaseMenu* getInstance();

	void setThreadGIL(enum KLEM_PY3GILEVENT emEvent);

public slots:
	KLcBool kqeOnActionConnectPfEye();
	KLcBool kqeOnActionDisconnectPfEye();

public:
	


private:
	KLqBaseMenu();
	~KLqBaseMenu();
	KLqBaseMenu(const KLqBaseMenu& pSelf);
	const KLqBaseMenu& operator=(const KLqBaseMenu& pSelf);

	KLqBool ReInit();

	static DWORD WINAPI kqThLaunchPfeye(LPVOID _vp);
	

private:
	static KLqBaseMenu* m_pSelf;
	KLW_THREADWORKPOOL_PTR m_pThPoolPyBreath;
	KLC_SCLIST m_pListPyWorker;

	// Menu -> QMenuBar
	PQMENUBAR m_pMenuBar;

	// Menu bar -> QMenu
	PQMENU m_pMenuNew;
	PQMENU m_pMenuCollector;
	PQMENU m_pMenuSetting;
	PQMENU m_pMenuAbout;

	// Menu 1st
	PQMENU m_pMenu1stPerfeye;

	// Menu 2nd action -> QAction
	PQACTION m_pAcPerfeyeConnect;
	PQACTION m_pAcPerfeyeDisconnect;


private:
	// Perfeye variable.
	PyGILState_STATE			m_emGILPfeye;
	KLW_SHAREMEMDESC			m_tCorMemPfeye;
	KLP_PY3ONFRAMEBREATHDESC	m_tPy3BreathPfeye;

};



#endif