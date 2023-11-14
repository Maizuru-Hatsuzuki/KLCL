#ifndef __KLOG_H__
#define __KLOG_H__

#include "KLcLua.h"
#include <Windows.h>


#define VAOUTW(fmt, ...)				\
do										\
{										\
	va_list vaArgs;						\
	va_start(vaArgs, fmt);				\
	vwprintf(fmt, vaArgs);				\
	va_end(vaArgs);						\
} while (0);


#define VAOUTA(fmt, ...)				\
do										\
{										\
	va_list vaArgs;						\
	va_start(vaArgs, fmt);				\
	vprintf(fmt, vaArgs);				\
	va_end(vaArgs);						\
} while (0);


#ifdef UNICODE
#define KLLOG		KPrettyPrintfW
#define KLBASELOG	KBaseInfoPrintfW

#else
#define KLLOG		KPrettyPrintfA
#define KLBASELOG	KBaseInfoPrintfA

#endif


enum KLEM_LOGLEVEL
{
	KLOG_DEBUG,
	KLOG_INFO,
	KLOG_WARING,
	KLOG_ERROR
};


void KBaseInfoPrintfA();
KLcBool KBaseInfoPrintfW();
KLcBool KPrettyPrintfW(enum KLEM_LOGLEVEL emLevel, LPCWSTR cwszpText, ...);
KLcBool KPrettyPrintfA(enum KLEM_LOGLEVEL emLevel, const char* cszpText, ...);

#endif
