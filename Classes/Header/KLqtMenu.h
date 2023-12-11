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

class KLqBaseMenu:
	public QWidget
{
public:
	PQMENUBAR getMenuBar();
	static KLqBaseMenu* getInstance();

public slots:
	KLcBool KLqeOnActionConnectPfEye();
	KLcBool KLqeOnActionDisconnectPfEye();

signals:
	void KLQS_CLICK();

public:

private:
	KLqBaseMenu();
	~KLqBaseMenu();
	KLqBaseMenu(const KLqBaseMenu& pSelf);
	const KLqBaseMenu& operator=(const KLqBaseMenu& pSelf);

private:
	static KLqBaseMenu* m_pSelf;
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

};



#endif