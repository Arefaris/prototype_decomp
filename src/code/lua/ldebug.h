// Lua 5.1.1, ldebug.h: auxiliary functions from the debug interface.
#ifndef LUA_LDEBUG_H
#define LUA_LDEBUG_H

#include "code/lua/lstate.h"

LUAI_EXTERN_C_BEGIN

#define pcRel(pc, p) (cast(int, (pc) - (p)->code) - 1)

#define getline(f, pc) (((f)->lineinfo) ? (f)->lineinfo[pc] : 0)

#define resethookcount(L) (L->hookcount = L->basehookcount)

void luaG_typeerror(lua_State* L, const TValue* o, const char* opname);
void luaG_concaterror(lua_State* L, StkId p1, StkId p2);
void luaG_aritherror(lua_State* L, const TValue* p1, const TValue* p2);
int luaG_ordererror(lua_State* L, const TValue* p1, const TValue* p2);
void luaG_runerror(lua_State* L, const char* fmt, ...);
void luaG_errormsg(lua_State* L);
int luaG_checkcode(const Proto* pt);

LUAI_EXTERN_C_END

#endif
