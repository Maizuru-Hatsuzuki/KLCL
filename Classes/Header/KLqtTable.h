/********************************************************
* Filename		: KLqtTable.h
* Creator		: lidiankai
* Date time		: 2023.12.18
* Description	:
********************************************************/


#ifndef __KLQTTABLE_H__
#define __KLQTTABLE_H__

#include "KLclRay.h"
#include <QTableWidget>
#include <QHeaderView>


class KLqBaseTable:
	public QWidget
{

public:
	KLcBool initTableWidget(float fWindowHeight, float fWindowWidth);
	static KLqBaseTable* getInstance();
	KLcBool getTableItem();

public:
	// Qt.
	KLcBool setTableData();
	KLcBool setTableDataALine(unsigned int unLine, const char** carrszpData);

public:
	QTableWidget* m_pTableWidget;

private:
	KLqBaseTable();
	~KLqBaseTable();
	KLqBaseTable(const KLqBaseTable& pSelf);
	const KLqBaseTable& operator=(const KLqBaseTable& pSelf);

private:
	const char* m_carrszpRowFields[MAX_KTABLEROWFIELDS] = { 
		"IP", "Description", "Device type", "Mission", "JX3 Version", "Status" 
	};
	unsigned int m_unLine;
	unsigned int m_unRow;

	static KLqBaseTable* m_pSelf;

private:
	// Qt.
	
};




#endif // __KLQTTABLE_H__
