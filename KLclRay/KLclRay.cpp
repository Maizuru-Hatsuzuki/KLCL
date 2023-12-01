#include "KLclRay.h"



KLclRay::KLclRay(QWidget *parent)
    : QMainWindow(parent)
{
    
    

    ui.setupUi(this);
	m_fWindowHeight = this->geometry().height();
	m_fWindowWidth = this->geometry().width();

	m_pQHLayoutBase = new QHBoxLayout;
	m_pQHLayoutBottom = new QHBoxLayout;
}

KLclRay::~KLclRay()
{
    delete m_pQHLayoutBase;
    delete m_pQHLayoutBottom;
}

void KLclRay::klqCreateTextEdit(PQTEXTEDIT* ppQTextEdit)
{
    *ppQTextEdit = new QTextEdit(this);

    (*ppQTextEdit)->setAlignment(Qt::AlignLeft);
    (*ppQTextEdit)->setGeometry(m_fWindowWidth * KQSCALING_BOTTOMLEFT, m_fWindowHeight * 0.65, m_fWindowWidth * (1 - KQSCALING_BOTTOMLEFT * 2), m_fWindowHeight * 0.3);
    (*ppQTextEdit)->setStyleSheet("QLabel{background-color:rgb(255, 255, 255)}");
    (*ppQTextEdit)->setReadOnly(true);
    (*ppQTextEdit)->setText("Init success;");
}

void KLclRay::klqUpdateText(PQTEXTEDIT pTextEdit, const char* cszpText)
{
    QTextCursor pCursor = pTextEdit->textCursor();

    pCursor.movePosition(QTextCursor::End);
    pTextEdit->setTextCursor(pCursor);
    pTextEdit->insertPlainText(cszpText);

    return;
}

void KLclRay::klqShow()
{
    PQTEXTEDIT pQTKLLog = NULL;
    klqCreateTextEdit(&pQTKLLog);

	ASSERT(pQTKLLog);

	m_pQHLayoutBase->addWidget(pQTKLLog);
	setLayout(m_pQHLayoutBase);

    pQTKLLog->show();

Exit0:
    return;
}