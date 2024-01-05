/********************************************************
* Filename		: KLqtRegisterDevice.h
* Creator		: lidiankai
* Date time		: 2024.01.04
* Description	: QDialog for register device.
********************************************************/

#ifndef __KLQTREGISTERDEVICE_H__
#define __KLQTREGISTERDEVICE_H__

#include "KLclRay.h"
#include "KLclRayEx.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QFileDialog>


typedef QDialogButtonBox* PQDIALOGBUTTONBOX;

class BaseRegisterDevices:
	public QDialog
{
public:
	BaseRegisterDevices();
	~BaseRegisterDevices();

	PQDIALOGBUTTONBOX getBtnBoxSubmitHandler();
	

public:


protected:
	PQDIALOGBUTTONBOX m_pBtnBoxSubmit;

private:

};


class RegisterDevicesWindows
{
public:
	static RegisterDevicesWindows* getInstance(float fWindowHeight = 720.f, float fWindowWidth = 1200.f);
	BaseRegisterDevices* getWindowHandler();
	void initWindowDialog();
	void uninitWindowDialog();

private:
	RegisterDevicesWindows();
	RegisterDevicesWindows(float fWindowHeight, float fWindowWidth);
	~RegisterDevicesWindows();
	RegisterDevicesWindows(const RegisterDevicesWindows& pSelf);
	const RegisterDevicesWindows& operator=(const RegisterDevicesWindows& pSelf);

	void klqCreateGetInfoIntput();

private:
	static RegisterDevicesWindows* m_pSelf;

	float m_fWindowHeight = 0;
	float m_fWindowWidth = 0;

private:
	// Qt.
	BaseRegisterDevices* m_pWindow;
	QVBoxLayout* m_pLayoutBase;
	QHBoxLayout* m_pLayoutBottom;
	QWidget* m_pWidgetBottom;
	QGridLayout* m_pLayoutDevice;
	QGridLayout* m_pLayoutPath;
	QGroupBox* m_pGroupDevice;
	QGroupBox* m_pGroupPath;
	QLabel* m_pLabelDeviceIp;
	QLabel* m_pLabelDeviceDescription;
	QLabel* m_pLabelJX3HDPath;
	QLabel* m_pLabelJX3YQPath;
	QLineEdit* m_pEditDeviceIP;
	QLineEdit* m_pEditDeviceDescrition;
	QLineEdit* m_pEditJX3HDPath;
	QLineEdit* m_pEditJX3YQPath;
	QPushButton* m_pBtnGetJX3HDPath;
	QPushButton* m_pBtnGetJX3YQPath;
};



#endif
