#pragma once


#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include <Qlist>
#include <thread>
#include "KBaseMacro.h"
#include "KLclRayEx.h"
#include "ui_KLclRay.h"


#define KLQ_NEW(qType, s)		new qType(s)
#define KLQ_RELEASE(p)			{ if (p) { delete p; (p) = NULL; } }
#define KLQ_UPDATELOG			KLclRay::getInstance()->klqUpdateSysLog
#define KLQ_LOG(level, fmt, ...)	{ KLLOG(level, fmt, __VA_ARGS__); KLQ_UPDATELOG(); }

#define MAX_KP_THREAD 10
#define MAX_KTABLEROWFIELDS 6

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
	static KLclRay* getInstance();
	static void KLqHeartbeat(void* _vp);
	KLcBool klqUpdateSysLogForPy();
	void klqUpdateSysLog();
    void klqUpdateText(PQTEXTEDIT pTextEdit, const char* cszpText);
    void klqCreateTextEdit(PQTEXTEDIT* ppQTextEdit);

public:
	KLW_SHAREMEMDESC m_tCorMemPyLog;
	Ui::KLclRayClass ui;

private:
	KLclRay(QWidget* parent = nullptr);
	~KLclRay();
    KLclRay(const KLclRay& pSelf);
    const KLclRay& operator=(const KLclRay& pSelf);

	void ReInit();


private:
	// Qt.
	float m_fWindowHeight = 0;
	float m_fWindowWidth = 0;

	PQTEXTEDIT m_pQTKLLog = NULL;
	QHBoxLayout* m_pQHLayoutBase = NULL;
	QHBoxLayout* m_pQHLayoutBottom = NULL;

private:
	static KLclRay* m_pSelf;
	

};
