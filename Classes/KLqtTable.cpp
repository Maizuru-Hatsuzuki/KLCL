/********************************************************
* Filename		: KLqtTable.cpp
* Creator		: lidiankai
* Date time		: 2023.12.18
* Description	:
********************************************************/

#include "KLcPy.h"
#include "KLqtTable.h"


KLqBaseTable* KLqBaseTable::m_pSelf;

KLqBaseTable::KLqBaseTable()
{
	m_unRow = MAX_KTABLEROWFIELDS;
	m_unLine = 10;
}

KLqBaseTable::~KLqBaseTable()
{
}

KLqBaseTable* KLqBaseTable::getInstance()
{
	if (NULL == m_pSelf)
	{
		m_pSelf = new KLqBaseTable();
	}

	return m_pSelf;
}

void debugKK()
{
	KLP_CREATETHREAD_GET_GIL;
	PPYOBJECT ret = NULL;
	PPYOBJECT ck = NULL;
	PPYOBJECT yk = NULL;
	PPYOBJECT arrpyRet[2] = { 0 };
	__int64 llCount = 0;
	long arrlRet[2] = { 0 };
	char* arrszpRet[2] = { 0 };
	KLpLaunchClassFn("WizardUltra", "UAPfeye", "getDevicesInfo", NULL, NULL, &ret);
	KL_PROCESS_ERROR(ret);

	KLpAnalyzeRet(ret, &llCount, &arrpyRet[0], &arrpyRet[1]);
	/*KLpAnalyzeRetToLong(arrpyRet, llCount, arrlRet);
	printf("%ld, %ld\n", arrlRet[0], arrlRet[1]);*/

	KLpAnalyzeRetToPChar(arrpyRet, llCount, arrszpRet);
	printf("%s, %s\n", arrszpRet[0], arrszpRet[1]);

Exit0:
	return;
}


KLcBool KLqBaseTable::initTableWidget(float fWindowHeight, float fWindowWidth)
{
	m_pTableWidget			= new QTableWidget(m_unLine, MAX_KTABLEROWFIELDS);
	QHeaderView* pHeader	= m_pTableWidget->horizontalHeader();
	QFont qHeaderFont		= pHeader->font();
	QStringList qsHeader;
	for (size_t i = 0; i < MAX_KTABLEROWFIELDS; i++)
	{
		qsHeader << m_carrszpRowFields[i];
	}

	qHeaderFont.setBold(true);
	pHeader->setFont(qHeaderFont);

	m_pTableWidget->setGeometry(fWindowWidth * KQSCALING_BOTTOMLEFT, fWindowHeight * 0.15, fWindowWidth * (1 - KQSCALING_BOTTOMLEFT * 2), fWindowHeight * 0.45);
	m_pTableWidget->setShowGrid(true);
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTableWidget->setHorizontalHeaderLabels(qsHeader);
	m_pTableWidget->verticalHeader()->setDefaultSectionSize(10);
	m_pTableWidget->setStyleSheet("QTableWidget { font-size: 12px; }");
	m_pTableWidget->setColumnWidth(1, 200);
	m_pTableWidget->setColumnWidth(3, 300);
	m_pTableWidget->setColumnWidth(4, 200);

	setTableData();
	return KL_TRUE;
}

KLcBool KLqBaseTable::setTableData()
{
	QTableWidgetItem* pItem = new QTableWidgetItem("127.0.0.1");
	m_pTableWidget->setItem(0, 0, pItem);

	return KL_TRUE;
}

KLcBool KLqBaseTable::setTableDataALine(unsigned int unLine, const char** carrszpData)
{
	KLcBool klBool = KL_FALSE;

	for (size_t i = 0; i < m_unRow; i++)
	{
		QTableWidgetItem* pItem = new QTableWidgetItem(carrszpData[i]);
		m_pTableWidget->setItem(0, 0, pItem);
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}