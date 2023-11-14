/********************************************************
* Filename		: KLcWin.h
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#ifndef __KLCWIN_H__
#define __KLCWIN_H__

#include "KLcLua.h"
#include "KLcWin.h"
#include <Windows.h>


struct _tKLwShareMemDesc
{
	PHANDLE phShareMem;
	LPVOID *ppvMemMapping;
	LPCWSTR wsMemName;
};

struct _tKLwPaddingShareMemDesc
{
	KLEM_FSMSTATUS emFsmStatus;
};

typedef struct _tKLwShareMemDesc		KLWSHAREMEMDESC, * KLWSHAREMEMDESC_PTR;
typedef struct _tKLwPaddingShareMemDesc	KLWPADDINGSHAREMEMDESC, * KLWPADDINGSHAREMEMDESC_PTR;

KLcBool KLwInitShareMem(KLWSHAREMEMDESC_PTR ptShareDesc);
KLcBool KLwUninitShareMem(KLWSHAREMEMDESC_PTR ptShareDesc);

#endif
