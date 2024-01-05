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
	KLcBool reInit(float fWindowHeight, float fWindowWidth);
	static KLqBaseTable* getInstance();
	KLcBool getTableItem();
	QTableWidget* getTableWidget();

public:
	// Qt.
	KLcBool setTableData();
	KLcBool setTableDataALine(unsigned int unLine, char** carrszpData);

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
	QTableWidget* m_pTableWidget;
};




#endif // __KLQTTABLE_H__
