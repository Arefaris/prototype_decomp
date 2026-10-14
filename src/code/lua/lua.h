// The parts of the Lua 5.1 API the engine uses (the library is linked in: lapi.c 0x1062C0A0 - 0x1062D3xx, lauxlib.c
// 0x106394xx - 0x1063A2xx; the engine's build uses float numbers and 8-byte stack values). Declarations follow the
// Lua 5.1 headers; only the declarations, the library itself is not reconstructed.
#ifndef LUA_LUA_H
#define LUA_LUA_H

#include <stddef.h>

extern "C"
{
	struct lua_State;
	struct lua_Debug;

	typedef float lua_Number;
	typedef int lua_Integer;
	typedef int (*lua_CFunction)(lua_State* L);
	typedef void* (*lua_Alloc)(void* ud, void* ptr, size_t osize, size_t nsize);

	enum
	{
		LUA_REGISTRYINDEX = -10000,
		LUA_ENVIRONINDEX = -10001,
		LUA_GLOBALSINDEX = -10002
	};

	enum
	{
		LUA_TNONE = -1,
		LUA_TNIL = 0,
		LUA_TBOOLEAN = 1,
		LUA_TLIGHTUSERDATA = 2,
		LUA_TNUMBER = 3,
		LUA_TSTRING = 4,
		LUA_TTABLE = 5,
		LUA_TFUNCTION = 6,
		LUA_TUSERDATA = 7,
		LUA_TTHREAD = 8
	};

	enum
	{
		LUA_YIELD = 1,
		LUA_ERRRUN = 2,
		LUA_ERRSYNTAX = 3,
		LUA_ERRMEM = 4,
		LUA_ERRERR = 5
	};

	enum
	{
		LUA_GCSTOP = 0,
		LUA_GCRESTART = 1,
		LUA_GCCOLLECT = 2,
		LUA_GCCOUNT = 3,
		LUA_GCCOUNTB = 4,
		LUA_GCSTEP = 5
	};

	struct lua_Debug
	{
		int event;
		const char* name;
		const char* namewhat;
		const char* what;
		const char* source;
		int currentline;
		int nups;
		int linedefined;
		int lastlinedefined;
		char short_src[200];
		int i_ci;
	};

	lua_State* lua_newstate(lua_Alloc f, void* ud);
	void lua_close(lua_State* L);
	lua_State* lua_newthread(lua_State* L);
	int lua_checkstack(lua_State* L, int sz);
	void lua_xmove(lua_State* from, lua_State* to, int n);
	lua_CFunction lua_atpanic(lua_State* L, lua_CFunction panicf);

	int lua_gettop(lua_State* L);
	void lua_settop(lua_State* L, int idx);
	void lua_pushvalue(lua_State* L, int idx);
	void lua_remove(lua_State* L, int idx);
	void lua_insert(lua_State* L, int idx);
	void lua_replace(lua_State* L, int idx);

	int lua_isnumber(lua_State* L, int idx);
	int lua_isstring(lua_State* L, int idx);
	int lua_iscfunction(lua_State* L, int idx);
	int lua_isuserdata(lua_State* L, int idx);
	int lua_type(lua_State* L, int idx);
	const char* lua_typename(lua_State* L, int tp);
	int lua_rawequal(lua_State* L, int idx1, int idx2);
	lua_Number lua_tonumber(lua_State* L, int idx);
	lua_Integer lua_tointeger(lua_State* L, int idx);
	int lua_toboolean(lua_State* L, int idx);
	const char* lua_tolstring(lua_State* L, int idx, size_t* len);
	size_t lua_objlen(lua_State* L, int idx);
	void* lua_touserdata(lua_State* L, int idx);
	lua_State* lua_tothread(lua_State* L, int idx);
	const void* lua_topointer(lua_State* L, int idx);

	void lua_pushnil(lua_State* L);
	void lua_pushnumber(lua_State* L, lua_Number n);
	void lua_pushinteger(lua_State* L, lua_Integer n);
	void lua_pushlstring(lua_State* L, const char* s, size_t l);
	void lua_pushstring(lua_State* L, const char* s);
	const char* lua_pushvfstring(lua_State* L, const char* fmt, char* argp);
	const char* lua_pushfstring(lua_State* L, const char* fmt, ...);
	void lua_pushcclosure(lua_State* L, lua_CFunction fn, int n);
	void lua_pushboolean(lua_State* L, int b);
	void lua_pushlightuserdata(lua_State* L, void* p);

	void lua_gettable(lua_State* L, int idx);
	void lua_getfield(lua_State* L, int idx, const char* k);
	void lua_rawget(lua_State* L, int idx);
	void lua_rawgeti(lua_State* L, int idx, int n);
	void lua_createtable(lua_State* L, int narr, int nrec);
	int lua_getmetatable(lua_State* L, int objindex);
	void lua_settable(lua_State* L, int idx);
	void lua_setfield(lua_State* L, int idx, const char* k);
	void lua_rawset(lua_State* L, int idx);
	void lua_rawseti(lua_State* L, int idx, int n);
	int lua_setmetatable(lua_State* L, int objindex);

	void lua_call(lua_State* L, int nargs, int nresults);
	int lua_pcall(lua_State* L, int nargs, int nresults, int errfunc);
	int lua_load(lua_State* L, const char* (*reader)(lua_State*, void*, size_t*), void* dt, const char* chunkname);
	int lua_resume(lua_State* L, int narg);
	int lua_gc(lua_State* L, int what, int data);
	int lua_error(lua_State* L);
	int lua_next(lua_State* L, int idx);
	void lua_concat(lua_State* L, int n);

	int lua_getstack(lua_State* L, int level, lua_Debug* ar);
	int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar);

	int luaL_callmeta(lua_State* L, int obj, const char* e);
	int luaL_argerror(lua_State* L, int numarg, const char* extramsg);
	const char* luaL_checklstring(lua_State* L, int numArg, size_t* l);
	lua_Integer luaL_optinteger(lua_State* L, int nArg, lua_Integer def);
	void luaL_checkany(lua_State* L, int narg);
	int luaL_error(lua_State* L, const char* fmt, ...);
	int luaL_ref(lua_State* L, int t);
	void luaL_unref(lua_State* L, int t, int ref);
	int luaL_loadbuffer(lua_State* L, const char* buff, size_t sz, const char* name);
}

#endif
