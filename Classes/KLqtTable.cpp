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

KLcBool KLqBaseTable::getTableItem()
{
	KLP_CREATETHREAD_GET_GIL;
	KLcBool klBool = KL_FALSE;
	PPYOBJECT ret = NULL;
	PPYOBJECT pyRet = NULL;
	__int64 llCount = 0;
	__int64 llPos = 0;
	char* arrszpRet[MAX_KTABLEROWFIELDS] = { 0 };
	
	KLP_LAUNCHCF_WITHNOARGS_UMAIN_RET("R4Debug", "CGetDevices", &ret);
	KL_PROCESS_ERROR(ret);
	KLpGetPyTupleSize(ret, &llCount);

	do 
	{
		klBool = KLpAnalyzeSingleRet(ret, llPos, "O", &pyRet);
		KL_PROCESS_ERROR(klBool);
		klBool = KLpAnalyzeRetTupleToPChar(pyRet, arrszpRet);
		KL_PROCESS_ERROR(klBool);
		klBool = setTableDataALine(llPos, arrszpRet);
		KL_PROCESS_ERROR(klBool);

		llPos++;

	} while (llCount > llPos);

	KLP_RELEASETHREAD_GIL;
	klBool = KL_TRUE;
Exit0:
	return klBool;
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
	KLcBool klBool = KL_FALSE;

	return KL_TRUE;
}

KLcBool KLqBaseTable::setTableDataALine(unsigned int unLine, char** carrszpData)
{
	KLcBool klBool = KL_FALSE;

	for (size_t i = 0; i < m_unRow; i++)
	{
		QTableWidgetItem* pItem = new QTableWidgetItem(carrszpData[i]);
		m_pTableWidget->setItem(unLine, i, pItem);
	}

	klBool = KL_TRUE;
Exit0:
	return klBool;
}
