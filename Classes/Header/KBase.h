#ifndef __KBASE_H__
#define __KBASE_H__

#define KLDLLEXPORT

#include <time.h>

#ifdef KLDLLEXPORT
#define KL_DLLEXPORT __declspec(dllexport)
#else
#define KL_DLLEXPORT __declspec(dllimport)
#endif

#define MAX_KCUSTOMDATA				10
#define MAX_KCUSTOMDATAARRAY		5
#define MAX_ADBCMD					1024
#define MAX_ZPRINTF					1024
#define MAX_CMDRET					10240
#define MAX_KLCMAP					512

typedef int KLcBool;
typedef int KLpFnRet;
#define KBOOLFN(fn)	KLcBool (*fn)

#endif
