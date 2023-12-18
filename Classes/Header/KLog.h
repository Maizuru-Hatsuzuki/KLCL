#ifndef __KLOG_H__
#define __KLOG_H__

#include "KBase.h"
#include "KLcLua.h"
#include <Windows.h>


#define KL_VAOUTW(fmt, fmtRet, ...)		\
do										\
{										\
	va_list vaArgs;						\
	va_start(vaArgs, fmt);				\
	vwprintf(fmt, vaArgs);				\
	vswprintf_s(fmtRet, MAX_ZPRINTF, fmt, vaArgs); \
	va_end(vaArgs);						\
} while (0);


#define KL_VAOUTA(fmt, fmtRet, ...)				\
do										\
{										\
	va_list vaArgs;						\
	va_start(vaArgs, fmt);				\
	vprintf(fmt, vaArgs);				\
	vsprintf_s(fmtRet, MAX_ZPRINTF, fmt, vaArgs); \
	va_end(vaArgs);						\
} while (0);


#ifdef UNICODE
#define KLLOG(level, fmt, ...)		KPrettyPrintfW(KLOG_INFO, fmt, __VA_ARGS__);

#else
#define KLLOG						KPrettyPrintfA

#endif



enum KLEM_LOGLEVEL
{
	KLOG_DEBUG,
	KLOG_INFO,
	KLOG_WARING,
	KLOG_ERROR
};

struct _tUpdateLogInfo
{
	enum KLEM_LOGLEVEL emLevel;
	WCHAR wszarrLog[MAX_ZPRINTF];
	char szarrLog[MAX_ZPRINTF];
	KLcBool kbIsPrintfFlag;
};
typedef struct _tUpdateLogInfo UPDATELOGINFO, *UPDATELOGINFO_PTR;

extern UPDATELOGINFO g_tKlSysLog;

void KBaseInfoPrintfA();
KLcBool KBaseInfoPrintfW();

#ifdef __cplusplus
extern "C" {
#endif	
	KL_DLLEXPORT KLcBool KPrettyPrintfW(enum KLEM_LOGLEVEL emLevel, LPCWSTR cwszpText, ...);
	KL_DLLEXPORT KLcBool KPrettyPrintfA(enum KLEM_LOGLEVEL emLevel, const char* cszpText, ...);
	KL_DLLEXPORT void KLWCharToChar(LPCWSTR pwsSrc, char* szpDst);
	KL_DLLEXPORT void KLResetSysLog();
	KL_DLLEXPORT void KLPushSysLog(WCHAR* wpsRet, char* psRet);
	KL_DLLEXPORT void KLGetSysLogFlag(int* pnRet);
#ifdef __cplusplus
}
#endif

#endif
