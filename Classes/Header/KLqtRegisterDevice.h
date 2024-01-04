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


typedef QDialogButtonBox* PQDIALOGBUTTONBOX;

class BaseRegisterDevices:
	public QDialog
{
public:
	BaseRegisterDevices();
	~BaseRegisterDevices();


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
	void klqCreateWindow();
	
private:
	RegisterDevicesWindows();
	RegisterDevicesWindows(float fWindowHeight, float fWindowWidth);
	~RegisterDevicesWindows();
	RegisterDevicesWindows(const RegisterDevicesWindows& pSelf);
	const RegisterDevicesWindows& operator=(const RegisterDevicesWindows& pSelf);

private:
	static RegisterDevicesWindows* m_pSelf;
	BaseRegisterDevices* m_pWindow;

	float m_fWindowHeight = 0;
	float m_fWindowWidth = 0;
};



#endif
