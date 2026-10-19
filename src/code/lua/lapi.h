// Lua 5.1.1, lapi.h: Auxiliary functions from Lua API.
#ifndef LUA_LAPI_H
#define LUA_LAPI_H

#include "code/lua/lobject.h"

LUAI_EXTERN_C_BEGIN

void luaA_pushobject(lua_State* L, const TValue* o);

LUAI_EXTERN_C_END

#endif
