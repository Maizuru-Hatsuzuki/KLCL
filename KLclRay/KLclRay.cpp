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
    ui.setupUi(this);
    ReInit();
}

KLclRay::~KLclRay()
{
    KLcBool klBool = KL_FALSE;

    KLQ_RELEASE(m_pQHLayoutBase);
    KLQ_RELEASE(m_pQHLayoutBottom);
    KLQ_RELEASE(m_pSelf);

	klBool = KLpUninitPy3();
	ASSERT(klBool);
	KLwUninitShareMem(&m_tCorMemPyLog);
}

void KLclRay::ReInit()
{
	KLcBool klBool = KL_FALSE;
    DWORD dwTidUpdateSysLog = 0;
	m_fWindowHeight = this->geometry().height();
	m_fWindowWidth = this->geometry().width();
	m_pQHLayoutBase = new QHBoxLayout;
	m_pQHLayoutBottom = new QHBoxLayout;
	setLayout(m_pQHLayoutBase);

	this->setMenuBar(KLqBaseMenu::getInstance()->getMenuBar());
	
	KLqBaseTable::getInstance()->initTableWidget(m_fWindowHeight, m_fWindowWidth);
	KLqBaseTable::getInstance()->m_pTableWidget->setParent(this);

	RegisterDevicesWindows::getInstance(m_fWindowHeight, m_fWindowWidth)->klqCreateWindow();

	m_pQHLayoutBase->addWidget(KLqBaseTable::getInstance()->m_pTableWidget);

	klqCreateTextEdit(&m_pQTKLLog);
	ASSERT(m_pQTKLLog);
	m_pQHLayoutBase->addWidget(m_pQTKLLog);
	
	klBool = KLpInitPy3();
	ASSERT(klBool);
    KLLOG(KLOG_INFO, L"Init klp python success.");
	klqUpdateSysLog();

	m_tCorMemPyLog.wsMemName = WORKERNAME_W_PYLOG;
	m_tCorMemPyLog.dwSize = sizeof(enum KLEM_SHAREMEMFLAGS);
	klBool = KLwInitShareMem(&m_tCorMemPyLog);
	ASSERT(klBool);

	KLP_LAUNCHF_UMAIN_NORET("R2Vigilante");

	// Print python log thread.
	_beginthread((_beginthread_proc_type)KLclRay::KLqHeartbeat, 0, (void*)this);

Exit0:
	return;
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
	KLcBool klBool = KL_FALSE;
	KLclRay* pThis = (KLclRay*)_vp;

	// Init thread, so don't need _PyThreadState_UncheckedGet.
	PyEval_ReleaseThread(PyThreadState_Get());

	while (true)
	{
		klBool = pThis->klqUpdateSysLogForPy();
		ASSERT(klBool);

		Sleep(10);
	}

	return;
}

KLcBool KLclRay::klqUpdateSysLogForPy()
{
	KLcBool klBool					= KL_FALSE;
	WCHAR wszarrLog[MAX_ZPRINTF]	= { 0 };
	CHAR szarrLog[MAX_ZPRINTF]		= { 0 };
	int nFlag						= KL_TRUE;
	void* vpFlags					= malloc(sizeof(enum KLEM_SHAREMEMFLAGS));

	klBool = KLwGetShareMem(&m_tCorMemPyLog, &vpFlags, sizeof(enum KLEM_SHAREMEMFLAGS));
	KL_PROCESS_ERROR(klBool);

	switch (*(KLEM_SHAREMEMFLAGS*)vpFlags)
	{
	case KMSHARE_INIT:
		klqUpdateSysLog();
		klBool = KLwResetShareMem(&m_tCorMemPyLog);
		KL_PROCESS_ERROR(klBool);
		break;

	case KMSHARE_EXIT:
		goto Exit0;

	default:
		break;
	}

Exit0:
	KL_RELEASE(vpFlags);
	return klBool;
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


