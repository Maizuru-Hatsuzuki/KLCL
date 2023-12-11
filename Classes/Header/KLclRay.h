#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include <Qlist>
#include <windows.h>
#include "KBaseMacro.h"
#include "KLclRayEx.h"
#include "ui_KLclRay.h"

#define KLQ_NEW(qType, s)     new qType(s)
#define KLQ_RELEASE(p)        { if (p) { delete p; (p) = NULL; } }

typedef int         KLqBool;
typedef QTextEdit*  PQTEXTEDIT;
typedef QMenuBar*   PQMENUBAR;
typedef QMenu*      PQMENU;
typedef QAction*    PQACTION;

struct _tKLqDevicesInfo
{
	
};

class KLclRay : public QMainWindow
{
    Q_OBJECT

public:
	void ReInit();
	static KLclRay* getInstance();
	static DWORD WINAPI klqUpdateSysLog(LPVOID _this);
    void klqUpdateText(PQTEXTEDIT pTextEdit, const char* cszpText);
    void klqCreateTextEdit(PQTEXTEDIT* ppQTextEdit);

private:
	KLclRay(QWidget* parent = nullptr);
	~KLclRay();
    KLclRay(const KLclRay& pSelf);
    const KLclRay& operator=(const KLclRay& pSelf);

    Ui::KLclRayClass ui;


private:
	float m_fWindowHeight = 0;
	float m_fWindowWidth = 0;

	HANDLE m_hThUpdateSysLog = NULL;
	PQTEXTEDIT m_pQTKLLog = NULL;
	QHBoxLayout* m_pQHLayoutBase = NULL;
	QHBoxLayout* m_pQHLayoutBottom = NULL;

	static KLclRay* m_pSelf;




};
