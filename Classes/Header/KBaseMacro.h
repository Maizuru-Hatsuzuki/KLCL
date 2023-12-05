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
#define MAX_ADBCMD 1024
#define MAX_ZPRINTF 1024
#define MAX_CMDRET 10240

#define ASSERT(Condition) if (!(Condition)) __debugbreak()
#define KL_RELEASE(p) { if (p) { free(p); (p) = NULL; } }

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



#endif // !__Z1_BASEMACRO_H__
