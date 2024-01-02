/********************************************************
* Filename		: KBaseMacro.h
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#ifndef __KBASEMACRO_H__
#define __KBASEMACRO_H__

#define KL_FALSE 0
#define KLP_FALSE -1
#define KL_TRUE  1

#define ASSERT(Condition)	if (!(Condition)) __debugbreak()
#define KL_MALLOC(ptrType)	(ptrType*)malloc(sizeof(ptrType))
#define KL_RELEASE(p)		{ if (p) { free(p); (p) = NULL; } }

#define KL_PROCESS_SUCCESS(Condition)		\
do											\
{											\
	if (Condition)							\
	{										\
		printf("[KL_PROCESS_SUCCESS] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		goto Exit0;							\
	}										\
} while (0);

#define KLP_PROCESS_SUCCESS(Condition)		\
do											\
{											\
	if (Condition)							\
	{										\
		printf("[KL_PROCESS_SUCCESS] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		KLpGetLastError();					\
		goto Exit0;							\
	}										\
} while (0);

#define KL_PROCESS_ERROR(Condition)			\
do											\
{											\
	if (!(Condition))						\
	{										\
		printf("[KL_PROCESS_ERROR] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		goto Exit0;							\
	}										\
} while (0);

#define KLP_PROCESS_ERROR(Condition)		\
do											\
{											\
	if (!(Condition))						\
	{										\
		printf("[KL_PROCESS_ERROR] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		KLpGetLastError();					\
		goto Exit0;							\
	}										\
} while (0);



#endif // !__KBASEMACRO_H__
