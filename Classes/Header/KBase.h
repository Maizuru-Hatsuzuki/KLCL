#ifndef __KBASE_H__
#define __KBASE_H__

#define KLDLLEXPORT

#ifdef KLDLLEXPORT
#define KL_DLLEXPORT __declspec(dllexport)
#else
#define KL_DLLEXPORT __declspec(dllimport)
#endif



typedef int KLcBool;
typedef int KLpFnRet;




#endif
