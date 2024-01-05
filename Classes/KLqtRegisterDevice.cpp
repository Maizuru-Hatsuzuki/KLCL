/********************************************************
(Filename		: KLqtRegisterDevice.cpp
(Creator		: lidiankai
(Date time		: 2024.01.04
(Description	: QDialog for register device.
********************************************************/

#include "KLqtRegisterDevice.h"


RegisterDevicesWindows* RegisterDevicesWindows::m_pSelf;

BaseRegisterDevices::BaseRegisterDevices()	
{
	m_pBtnBoxSubmit = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	m_pBtnBoxSubmit->setParent(this);
	
}

PQDIALOGBUTTONBOX BaseRegisterDevices::getBtnBoxSubmitHandler()
{
	return m_pBtnBoxSubmit;
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
	uninitWindowDialog();
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

void RegisterDevicesWindows::initWindowDialog()
{
	m_pWindow			= new BaseRegisterDevices;
	m_pLayoutBase		= new QVBoxLayout;
	m_pLayoutBottom		= new QHBoxLayout;
	m_pLayoutDevice		= new QGridLayout;
	m_pLayoutPath		= new QGridLayout;
	m_pWidgetBottom		= new QWidget;

	klqCreateGetInfoIntput();

	m_pLayoutBottom->addWidget(m_pWindow->getBtnBoxSubmitHandler(), 1, Qt::AlignCenter | Qt::AlignBottom);
	m_pLayoutBase->addLayout(m_pLayoutBottom);

	m_pWindow->setWindowTitle("Register device [Windows]");
	m_pWindow->setWindowModality(Qt::ApplicationModal);
	m_pWindow->resize(m_fWindowWidth / 2, m_fWindowHeight / 2);
	m_pWindow->setFixedSize(m_pWindow->size());
	m_pWindow->setLayout(m_pLayoutBase);

	return;
}

void RegisterDevicesWindows::uninitWindowDialog()
{
	KLQ_RELEASE(m_pWindow);
	KLQ_RELEASE(m_pLayoutBase);
	KLQ_RELEASE(m_pLayoutBottom);
	KLQ_RELEASE(m_pWidgetBottom);
	KLQ_RELEASE(m_pLayoutDevice);
	KLQ_RELEASE(m_pLayoutPath);
	KLQ_RELEASE(m_pGroupDevice);
	KLQ_RELEASE(m_pGroupPath);
	KLQ_RELEASE(m_pLabelDeviceIp);
	KLQ_RELEASE(m_pLabelDeviceDescription);
	KLQ_RELEASE(m_pLabelJX3HDPath);
	KLQ_RELEASE(m_pLabelJX3YQPath);
	KLQ_RELEASE(m_pEditDeviceIP);
	KLQ_RELEASE(m_pEditDeviceDescrition);
	KLQ_RELEASE(m_pEditJX3HDPath);
	KLQ_RELEASE(m_pEditJX3YQPath);
	KLQ_RELEASE(m_pBtnGetJX3HDPath);
	KLQ_RELEASE(m_pBtnGetJX3YQPath);
}

void RegisterDevicesWindows::klqCreateGetInfoIntput()
{
	m_pGroupDevice					= new QGroupBox("Device");
	m_pGroupPath					= new QGroupBox("Path");
	m_pLabelDeviceIp				= new QLabel("Device ip");
	m_pLabelDeviceDescription		= new QLabel("Device description");
	m_pLabelJX3HDPath				= new QLabel("JX3 hd path");
	m_pLabelJX3YQPath				= new QLabel("JX3 yq path");

	m_pEditDeviceIP					= new QLineEdit();
	m_pEditDeviceDescrition			= new QLineEdit();
	m_pEditJX3HDPath				= new QLineEdit();
	m_pEditJX3YQPath				= new QLineEdit();

	m_pBtnGetJX3HDPath				= new QPushButton("Open");
	m_pBtnGetJX3YQPath				= new QPushButton("Open");

	m_pLayoutDevice->addWidget(m_pLabelDeviceIp, 0, 0);
	m_pLayoutDevice->addWidget(m_pEditDeviceIP, 0, 1);
	m_pLayoutDevice->addWidget(m_pLabelDeviceDescription, 1, 0);
	m_pLayoutDevice->addWidget(m_pEditDeviceDescrition, 1, 1);
	m_pLayoutDevice->setHorizontalSpacing(50);
	m_pGroupDevice->setLayout(m_pLayoutDevice);

	m_pLayoutPath->addWidget(m_pLabelJX3HDPath, 0, 0);
	m_pLayoutPath->addWidget(m_pEditJX3HDPath, 0, 1);
	m_pLayoutPath->addWidget(m_pBtnGetJX3HDPath, 0, 2);
	m_pLayoutPath->addWidget(m_pLabelJX3YQPath, 1, 0);
	m_pLayoutPath->addWidget(m_pEditJX3YQPath, 1, 1);
	m_pLayoutPath->addWidget(m_pBtnGetJX3YQPath, 1, 2);
	m_pLayoutPath->setHorizontalSpacing(50);
	m_pGroupPath->setLayout(m_pLayoutPath);

	m_pLayoutBase->addWidget(m_pGroupDevice);
	m_pLayoutBase->addWidget(m_pGroupPath);

	m_pWindow->connect(m_pBtnGetJX3HDPath, &QPushButton::clicked, [=] {
		QString sPath = QFileDialog::getExistingDirectory(m_pWindow, "Open path", "/", QFileDialog::ShowDirsOnly);
		m_pEditJX3HDPath->setText(sPath);
		});
	return;
}

BaseRegisterDevices* RegisterDevicesWindows::getWindowHandler()
{
	return m_pWindow;
}