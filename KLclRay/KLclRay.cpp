#include "KLcPy.h"
#include "KLclRay.h"
#include "KLqtMenu.h"
#include "KLqtTable.h"
#include "KLqtRegisterDevice.h"
#include "KLog.h"


KLclRay* KLclRay::m_pSelf;


KLclRay::KLclRay(QWidget *parent)
    : QMainWindow(parent)
{
	KLcBool klRet = KL_FALSE;

    ui.setupUi(this);
    klRet = reInit();
	ASSERT(klRet);
}

KLclRay::~KLclRay()
{
    KLcBool klRet = KL_FALSE;

    KLQ_RELEASE(m_pQHLayoutBase);
    KLQ_RELEASE(m_pQHLayoutBottom);
    KLQ_RELEASE(m_pSelf);

	klRet = KLpUninitPy3();
	ASSERT(klRet);
	KLwUninitShareMem(&m_tCorMemPyLog);
}

KLcBool KLclRay::reInit()
{
	KLcBool klRet = KL_FALSE;
    DWORD dwTidUpdateSysLog = 0;
	
	m_tCorMemPyLog.wsMemName = WORKERNAME_W_PYLOG;
	m_tCorMemPyLog.dwSize = sizeof(enum KLEM_SHAREMEMFLAGS);

	reInitQt();
	
	klRet = KLpInitPy3();
	KL_PROCESS_ERROR(klRet);
    KLLOG(KLOG_INFO, L"Init klp python success.");
	klqUpdateSysLog();

	klRet = KLwInitShareMem(&m_tCorMemPyLog);
	KL_PROCESS_ERROR(klRet);

	// Pip python package.
	KLP_LAUNCHF_UMAIN_NORET("R2Vigilante");

	// Print python log thread.
	_beginthread((_beginthread_proc_type)KLclRay::KLqHeartbeat, 0, (void*)this);

	klRet = KL_TRUE;
Exit0:
	return klRet;
}

void KLclRay::reInitQt()
{
	m_fWindowHeight		= this->geometry().height();
	m_fWindowWidth		= this->geometry().width();
	m_pQHLayoutBase		= new QHBoxLayout;
	m_pQHLayoutBottom	= new QHBoxLayout;

	this->setLayout(m_pQHLayoutBase);
	this->setMenuBar(KLqBaseMenu::getInstance()->getMenuBar());

	// Menu.
	KLqBaseTable::getInstance()->reInit(m_fWindowHeight, m_fWindowWidth);
	KLqBaseTable::getInstance()->getTableWidget()->setParent(this);
	m_pQHLayoutBase->addWidget(KLqBaseTable::getInstance()->getTableWidget());

	// Register device dialog.
	RegisterDevicesWindows::getInstance(m_fWindowHeight, m_fWindowWidth)->initWindowDialog();

	// Log info edit.
	klqCreateTextEdit(&m_pQTKLLog);
	ASSERT(m_pQTKLLog);
	m_pQHLayoutBase->addWidget(m_pQTKLLog);
}

KLclRay* KLclRay::getInstance()
{
    if (NULL == m_pSelf)
    {
        m_pSelf = new KLclRay();
    }
    return m_pSelf;
}

void KLclRay::KLqHeartbeat(void* _vp)
{
	KLcBool klRet = KL_FALSE;
	KLclRay* pThis = (KLclRay*)_vp;

	// Init thread, so don't need _PyThreadState_UncheckedGet.
	PyEval_ReleaseThread(PyThreadState_Get());

	while (true)
	{
		klRet = pThis->klqUpdateSysLogForPy();
		ASSERT(klRet);

		Sleep(10);
	}

	return;
}

KLcBool KLclRay::klqUpdateSysLogForPy()
{
	KLcBool klRet					= KL_FALSE;
	WCHAR wszarrLog[MAX_ZPRINTF]	= { 0 };
	CHAR szarrLog[MAX_ZPRINTF]		= { 0 };
	int nFlag						= KL_TRUE;
	void* vpFlags					= malloc(sizeof(enum KLEM_SHAREMEMFLAGS));

	klRet = KLwGetShareMem(&m_tCorMemPyLog, &vpFlags, sizeof(enum KLEM_SHAREMEMFLAGS));
	KL_PROCESS_ERROR(klRet);

	switch (*(KLEM_SHAREMEMFLAGS*)vpFlags)
	{
	case KMSHARE_INIT:
		klqUpdateSysLog();
		klRet = KLwResetShareMem(&m_tCorMemPyLog);
		KL_PROCESS_ERROR(klRet);
		break;

	case KMSHARE_EXIT:
		goto Exit0;

	default:
		break;
	}

Exit0:
	KL_RELEASE(vpFlags);
	return klRet;
}

void KLclRay::klqUpdateSysLog()
{
	WCHAR wszarrLog[MAX_ZPRINTF] = { 0 };
	char szarrLog[MAX_ZPRINTF] = { 0 };
	int nFlag = KL_TRUE;

    KLGetSysLogFlag(&nFlag);
	if (KL_FALSE == nFlag)
	{
		KLPushSysLog(wszarrLog, szarrLog);
		if (0 != wcscmp(L"", wszarrLog))
		{
		    // Text in szarrLog.
			KLWCharToChar(wszarrLog, szarrLog);
		}
        klqUpdateText(m_pQTKLLog, szarrLog);
		ZeroMemory(szarrLog, MAX_ZPRINTF);
		ZeroMemory(wszarrLog, MAX_ZPRINTF);
		KLResetSysLog();
	}
}

void KLclRay::klqCreateTextEdit(PQTEXTEDIT* ppQTextEdit)
{
    *ppQTextEdit = new QTextEdit(this);

    (*ppQTextEdit)->setAlignment(Qt::AlignLeft);
    (*ppQTextEdit)->setGeometry(m_fWindowWidth * KQSCALING_BOTTOMLEFT, m_fWindowHeight * 0.65, m_fWindowWidth * (1 - KQSCALING_BOTTOMLEFT * 2), m_fWindowHeight * 0.3);
    (*ppQTextEdit)->setStyleSheet("QLabel{background-color:rgb(255, 255, 255)}");
    (*ppQTextEdit)->setReadOnly(true);

	return;
}

void KLclRay::klqUpdateText(PQTEXTEDIT pTextEdit, const char* cszpText)
{
    QTextCursor pCursor = pTextEdit->textCursor();

    pCursor.movePosition(QTextCursor::End);
    pTextEdit->setTextCursor(pCursor);
    pTextEdit->insertPlainText(tr(cszpText));
    QCoreApplication::processEvents();
    
    return;
}


