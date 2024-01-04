/********************************************************
* Filename		: KLqtRegisterDevice.cpp
* Creator		: lidiankai
* Date time		: 2024.01.04
* Description	: QDialog for register device.
********************************************************/

#include "KLqtRegisterDevice.h"

RegisterDevicesWindows* RegisterDevicesWindows::m_pSelf;

BaseRegisterDevices::BaseRegisterDevices()	
{
	m_pBtnBoxSubmit = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	m_pBtnBoxSubmit->setParent(this);
	
}

BaseRegisterDevices::~BaseRegisterDevices()
{
	delete m_pBtnBoxSubmit;
}

RegisterDevicesWindows::RegisterDevicesWindows() {}

RegisterDevicesWindows::RegisterDevicesWindows(float fWindowHeight, float fWindowWidth)
{
	m_pWindow = NULL;
	m_fWindowHeight = fWindowWidth;
	m_fWindowWidth = fWindowWidth;
}

RegisterDevicesWindows::~RegisterDevicesWindows()
{
	KLQ_RELEASE(m_pWindow);
}

RegisterDevicesWindows* RegisterDevicesWindows::getInstance(float fWindowHeight, float fWindowWidth)
{
	if (NULL == m_pSelf)
	{
		m_pSelf = new RegisterDevicesWindows(fWindowHeight, fWindowWidth);
	}

	return m_pSelf;
}

void RegisterDevicesWindows::klqCreateWindow()
{
	m_pWindow = new BaseRegisterDevices();
	m_pWindow->setWindowModality(Qt::ApplicationModal);
	m_pWindow->resize(m_fWindowWidth / 2, m_fWindowHeight / 2);

	return;
}

BaseRegisterDevices* RegisterDevicesWindows::getWindowHandler()
{
	return m_pWindow;
}