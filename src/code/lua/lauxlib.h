// Lua 5.1.1, lauxlib.h: Auxiliary functions for building Lua libraries.
#ifndef LUA_LAUXLIB_H
#define LUA_LAUXLIB_H

#include <stddef.h>
#include <stdio.h>

#include "code/lua/llimits.h"
#include "code/lua/lua.h"

LUAI_EXTERN_C_BEGIN

// the library functions' macros of lua.h that the auxiliary library uses
#define lua_pop(L, n) lua_settop(L, -(n) - 1)
#define lua_newtable(L) lua_createtable(L, 0, 0)
#define lua_isnil(L, n) (lua_type(L, (n)) == LUA_TNIL)
#define lua_istable(L, n) (lua_type(L, (n)) == LUA_TTABLE)
#define lua_isnone(L, n) (lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n) (lua_type(L, (n)) <= 0)
#define lua_pushliteral(L, s) lua_pushlstring(L, "" s, (sizeof(s) / sizeof(char)) - 1)
#define lua_tostring(L, i) lua_tolstring(L, (i), NULL)
#define lua_strlen(L, i) lua_objlen(L, (i))

// extra error code for `luaL_load'
#define LUA_ERRFILE (LUA_ERRERR + 1)

typedef struct luaL_Reg
{
	const char* name;
	lua_CFunction func;
} luaL_Reg;

// pre-defined references
#define LUA_NOREF (-2)
#define LUA_REFNIL (-1)

// Generic Buffer manipulation
#define luaL_typename(L, i) lua_typename(L, lua_type(L, (i)))

#define luaL_checkstring(L, n) (luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L, n, d) (luaL_optlstring(L, (n), (d), NULL))

#define luaL_opt(L, f, n, d) (lua_isnoneornil(L, (n)) ? (d) : f(L, (n)))

typedef struct luaL_Buffer
{
	char* p; // current position in buffer
	int lvl; // number of strings in the stack (level)
	lua_State* L;
	char buffer[LUAL_BUFFERSIZE];
} luaL_Buffer;

#define luaL_addchar(B, c) \
	((void)((B)->p < ((B)->buffer + LUAL_BUFFERSIZE) || luaL_prepbuffer(B)), \
	(*(B)->p++ = (char)(c)))

int luaL_getmetafield(lua_State* L, int obj, const char* e);
int luaL_callmeta(lua_State* L, int obj, const char* e);
int luaL_typerror(lua_State* L, int narg, const char* tname);
int luaL_argerror(lua_State* L, int numarg, const char* extramsg);
const char* luaL_checklstring(lua_State* L, int numArg, size_t* l);
const char* luaL_optlstring(lua_State* L, int numArg, const char* def, size_t* l);
lua_Number luaL_checknumber(lua_State* L, int numArg);
lua_Number luaL_optnumber(lua_State* L, int nArg, lua_Number def);
lua_Integer luaL_checkinteger(lua_State* L, int numArg);
lua_Integer luaL_optinteger(lua_State* L, int nArg, lua_Integer def);
void luaL_checkstack(lua_State* L, int sz, const char* msg);
void luaL_checktype(lua_State* L, int narg, int t);
void luaL_checkany(lua_State* L, int narg);
int luaL_newmetatable(lua_State* L, const char* tname);
void* luaL_checkudata(lua_State* L, int ud, const char* tname);
void luaL_where(lua_State* L, int lvl);
int luaL_error(lua_State* L, const char* fmt, ...);
int luaL_checkoption(lua_State* L, int narg, const char* def, const char* const lst[]);
int luaL_ref(lua_State* L, int t);
void luaL_unref(lua_State* L, int t, int ref);
int luaL_loadfile(lua_State* L, const char* filename);
int luaL_loadbuffer(lua_State* L, const char* buff, size_t sz, const char* name);
int luaL_loadstring(lua_State* L, const char* s);
lua_State* luaL_newstate(void);
const char* luaL_gsub(lua_State* L, const char* s, const char* p, const char* r);
const char* luaL_findtable(lua_State* L, int idx, const char* fname, int szhint);
void luaI_openlib(lua_State* L, const char* libname, const luaL_Reg* l, int nup);
void luaL_buffinit(lua_State* L, luaL_Buffer* B);
char* luaL_prepbuffer(luaL_Buffer* B);
void luaL_addlstring(luaL_Buffer* B, const char* s, size_t l);
void luaL_addstring(luaL_Buffer* B, const char* s);
void luaL_addvalue(luaL_Buffer* B);
void luaL_pushresult(luaL_Buffer* B);

LUAI_EXTERN_C_END

#endif
