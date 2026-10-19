// Lua 5.1.1, lstring.h: string table (keeps all strings handled by Lua).
#ifndef LUA_LSTRING_H
#define LUA_LSTRING_H

#include "code/lua/lgc.h"
#include "code/lua/lobject.h"
#include "code/lua/lstate.h"

LUAI_EXTERN_C_BEGIN

#define sizestring(s) (sizeof(union TString) + ((s)->len + 1) * sizeof(char))

#define sizeudata(u) (sizeof(union Udata) + (u)->len)

#define luaS_new(L, s) (luaS_newlstr(L, s, strlen(s)))
#define luaS_newliteral(L, s) (luaS_newlstr(L, "" s, (sizeof(s) / sizeof(char)) - 1))

#define luaS_fix(s) l_setbit((s)->tsv.marked, FIXEDBIT)

void luaS_resize(lua_State* L, int newsize);
Udata* luaS_newudata(lua_State* L, size_t s, Table* e);
TString* luaS_newlstr(lua_State* L, const char* str, size_t l);

LUAI_EXTERN_C_END

#endif
