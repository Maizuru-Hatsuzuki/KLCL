/********************************************************
* Filename		: KLcLua.c
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#include "KLcWin.h"
#include "KLog.h"

extern KLW_SHAREMEMDESC g_tKLwShareMemDesc;

LUARETURN GetKLclVersionR(lua_State* L)
{
	lua_pushnumber(L, KLCL_VERSION);
	return 1;
}

const int GetLuaInteger(lua_State* L)
{
	const int cnRet = luaL_checkint(L, 1);
	return cnRet;
}

void SetKLlEnumFSMStatus(lua_State* L)
{
	lua_newtable(L);
	KLC_LUAPUSHENUM(L, F_INIT);
	KLC_LUAPUSHENUM(L, F_UPDATE);
	KLC_LUAPUSHENUM(L, F_RELEASE);
	lua_setglobal(L, "KFSMSTATUS");
}

LUARETURN SetKLclShareMemR(lua_State* L)
{
	KLEM_FSMSTATUS emFSMStatus = (KLEM_FSMSTATUS)GetLuaInteger(L);
	
	switch (emFSMStatus)
	{
	case F_NONE:
		break;
	case F_INIT:
		break;
	case F_UPDATE:
		break;
	case F_RELEASE:
		break;
	default:
		break;
	}

	memcpy_s(*g_tKLwShareMemDesc.ppvMemMapping, sizeof(KLW_PADDINGSHAREMEMDESC), &emFSMStatus, sizeof(KLEM_FSMSTATUS));
	KLLOG(KLOG_INFO, L"Write klcl memory: %d[%p], size of KLWSHAREMEMDESC: %d", emFSMStatus, &emFSMStatus, sizeof(KLW_PADDINGSHAREMEMDESC));

	return 0;
}

LUAEXPORT int luaopen_KLclX64(lua_State* L)
{
	const luaL_reg tRegFuncList[] = 
	{
		{"GetKLclVersion", GetKLclVersionR},
		{"SetKLclShareMem", SetKLclShareMemR},
		{NULL, NULL}
	};

	SetKLlEnumFSMStatus(L);

	luaL_register(L, "KLclX64", tRegFuncList);	
	return 1;
}
