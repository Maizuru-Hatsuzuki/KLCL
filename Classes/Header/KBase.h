#ifndef __KBASE_H__
#define __KBASE_H__

#ifdef KL_DLLEXPORT
#define KL_DLLEXPORT __declspec(dllexport)
#else
#define KL_DLLEXPORT __declspec(dllimport)
#endif

#define KL_MALLOC(ptrType) (ptrType*)malloc(sizeof(ptrType))

typedef int KLcBool;
typedef int KLpFnRet;




#endif
