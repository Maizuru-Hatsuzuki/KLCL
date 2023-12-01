/********************************************************
* Filename		: KLcLua.h
* Creator		: lidiankai
* Date time		: 2023.11.14
* Description	:
********************************************************/

#ifndef __KLCLUA_H__
#define __KLCLUA_H__

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "KBaseMacro.h"
#include "KLcFSM.h"

#define LUAEXPORT __declspec(dllexport)

#define KLCL_VERSION 1.1
#define KLCL_SHAREMEMDESC L"KLCL"
#define KLCL_ARRNULL { 0 }

#define KLC_LUAPUSHENUM(L, val)		\
do									\
{									\
	lua_pushliteral(L, #val);		\
	lua_pushnumber(L, val);			\
	lua_settable(L, -3);			\
} while (0)

typedef int LUARETURN;


LUARETURN GetKLclVersionR(lua_State* L);
void SetKLlEnumFSMStatus(lua_State * L);
LUARETURN SetKLclShareMemR(lua_State * L);

LUAEXPORT int luaopen_KLclX64(lua_State* L);

#endif
