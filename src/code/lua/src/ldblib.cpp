// CFLAGS: !/arch /Oy-
// Lua 5.1 ldblib.c (Interface from Lua to its debug API; the engine's build, unit 0x10B7A0C0 - 0x10B7AD60). The functions are internal to
// the unit.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code/lua/lua.h"
#include "code/lua/lauxlib.h"

#define LUA_QL(x) "'" x "'"
#define LUA_QS LUA_QL("%s")
#define lua_isthread(L, n) (lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isfunction(L, n) (lua_type(L, (n)) == LUA_TFUNCTION)
#define luaL_checkint(L, n) ((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L, n, d) ((int)luaL_optinteger(L, (n), (d)))
#define luaL_argcheck(L, cond, numarg, extramsg) ((void)((cond) || luaL_argerror(L, (numarg), (extramsg))))

namespace engine
{
	// FUNCTION: ENGINE 0x10B7A0C0
	static int db_getregistry(lua_State* L)
	{
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A0E0
	static int db_getmetatable(lua_State* L)
	{
		luaL_checkany(L, 1);
		if (!lua_getmetatable(L, 1))
		{
			lua_pushnil(L); // no metatable
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A110
	static int db_setmetatable(lua_State* L)
	{
		int t = lua_type(L, 2);
		luaL_argcheck(L, t == LUA_TNIL || t == LUA_TTABLE, 2, "nil or table expected");
		lua_settop(L, 2);
		lua_pushboolean(L, lua_setmetatable(L, 1));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A160
	static int db_getfenv(lua_State* L)
	{
		lua_getfenv(L, 1);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A180
	static int db_setfenv(lua_State* L)
	{
		luaL_checktype(L, 2, LUA_TTABLE);
		lua_settop(L, 2);
		if (lua_setfenv(L, 1) == 0)
		{
			luaL_error(L, LUA_QL("setfenv") " cannot change environment of given object");
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A1C0
	static void settabss(lua_State* L, const char* i, const char* v)
	{
		lua_pushstring(L, v);
		lua_setfield(L, -2, i);
	}

	// FUNCTION: ENGINE 0x10B7A1E0
	static void settabsi(lua_State* L, const char* i, int v)
	{
		lua_pushinteger(L, v);
		lua_setfield(L, -2, i);
	}

	// FUNCTION: ENGINE 0x10B7A200
	static lua_State* getthread(lua_State* L, int* arg)
	{
		if (lua_isthread(L, 1))
		{
			*arg = 1;
			return lua_tothread(L, 1);
		}
		else
		{
			*arg = 0;
			return L;
		}
	}

	// FUNCTION: ENGINE 0x10B7A230
	static void treatstackoption(lua_State* L, lua_State* L1, const char* fname)
	{
		if (L == L1)
		{
			lua_pushvalue(L, -2);
			lua_remove(L, -3);
		}
		else
		{
			lua_xmove(L1, L, 1);
		}
		lua_setfield(L, -2, fname);
	}

	// FUNCTION: ENGINE 0x10B7A280
	static int db_getinfo(lua_State* L)
	{
		lua_Debug ar;
		int arg;
		lua_State* L1 = getthread(L, &arg);
		const char* options = luaL_optstring(L, arg + 2, "flnSu");
		if (lua_isnumber(L, arg + 1))
		{
			if (!lua_getstack(L1, (int)lua_tointeger(L, arg + 1), &ar))
			{
				lua_pushnil(L); // level out of range
				return 1;
			}
		}
		else if (lua_isfunction(L, arg + 1))
		{
			lua_pushfstring(L, ">%s", options);
			options = lua_tostring(L, -1);
			lua_pushvalue(L, arg + 1);
			lua_xmove(L, L1, 1);
		}
		else
		{
			return luaL_argerror(L, arg + 1, "function or level expected");
		}
		if (!lua_getinfo(L1, options, &ar))
		{
			return luaL_argerror(L, arg + 2, "invalid option");
		}
		lua_createtable(L, 0, 2);
		if (strchr(options, 'S'))
		{
			settabss(L, "source", ar.source);
			settabss(L, "short_src", ar.short_src);
			settabsi(L, "linedefined", ar.linedefined);
			settabsi(L, "lastlinedefined", ar.lastlinedefined);
			settabss(L, "what", ar.what);
		}
		if (strchr(options, 'l'))
		{
			settabsi(L, "currentline", ar.currentline);
		}
		if (strchr(options, 'u'))
		{
			settabsi(L, "nups", ar.nups);
		}
		if (strchr(options, 'n'))
		{
			settabss(L, "name", ar.name);
			settabss(L, "namewhat", ar.namewhat);
		}
		if (strchr(options, 'L'))
		{
			treatstackoption(L, L1, "activelines");
		}
		if (strchr(options, 'f'))
		{
			treatstackoption(L, L1, "func");
		}
		return 1; // return table
	}

	// FUNCTION: ENGINE 0x10B7A4B0
	static int db_getlocal(lua_State* L)
	{
		int arg;
		lua_State* L1 = getthread(L, &arg);
		lua_Debug ar;
		const char* name;
		if (!lua_getstack(L1, luaL_checkint(L, arg + 1), &ar))
		{
			// out of range?
			return luaL_argerror(L, arg + 1, "level out of range");
		}
		name = lua_getlocal(L1, &ar, luaL_checkint(L, arg + 2));
		if (name)
		{
			lua_xmove(L1, L, 1);
			lua_pushstring(L, name);
			lua_pushvalue(L, -2);
			return 2;
		}
		else
		{
			lua_pushnil(L);
			return 1;
		}
	}

	// FUNCTION: ENGINE 0x10B7A570
	static int db_setlocal(lua_State* L)
	{
		int arg;
		lua_State* L1 = getthread(L, &arg);
		lua_Debug ar;
		if (!lua_getstack(L1, luaL_checkint(L, arg + 1), &ar))
		{
			// out of range?
			return luaL_argerror(L, arg + 1, "level out of range");
		}
		luaL_checkany(L, arg + 3);
		lua_settop(L, arg + 3);
		lua_xmove(L, L1, 1);
		lua_pushstring(L, lua_setlocal(L1, &ar, luaL_checkint(L, arg + 2)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A620
	static int auxupvalue(lua_State* L, int get)
	{
		const char* name;
		int n = luaL_checkint(L, 2);
		luaL_checktype(L, 1, LUA_TFUNCTION);
		if (lua_iscfunction(L, 1))
		{
			return 0; // cannot touch C upvalues from Lua
		}
		name = get ? lua_getupvalue(L, 1, n) : lua_setupvalue(L, 1, n);
		if (name == NULL)
		{
			return 0;
		}
		lua_pushstring(L, name);
		lua_insert(L, -(get + 1));
		return get + 1;
	}

	// FUNCTION: ENGINE 0x10B7A680
	static int db_getupvalue(lua_State* L)
	{
		return auxupvalue(L, 1);
	}

	// FUNCTION: ENGINE 0x10B7A6A0
	static int db_setupvalue(lua_State* L)
	{
		luaL_checkany(L, 3);
		return auxupvalue(L, 0);
	}

	// The key of the hook table in the registry (only its address matters)
	extern const char KEY_HOOK = 'h';

	// FUNCTION: ENGINE 0x10B7A6C0
	// NONMATCHING: only the hook functions of the debug library use it, and those are not reconstructed
#ifdef NONMATCHING
	static void hookf(lua_State* L, lua_Debug* ar)
	{
		static const char* const hooknames[] = {"call", "return", "line", "count", "tail return"};
		lua_pushlightuserdata(L, (void*)&KEY_HOOK);
		lua_rawget(L, LUA_REGISTRYINDEX);
		lua_pushlightuserdata(L, L);
		lua_rawget(L, -2);
		if (lua_isfunction(L, -1))
		{
			lua_pushstring(L, hooknames[(int)ar->event]);
			if (ar->currentline >= 0)
			{
				lua_pushinteger(L, ar->currentline);
			}
			else
			{
				lua_pushnil(L);
			}
			lua_call(L, 2, 0);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10B7A750
	// NONMATCHING: only the hook functions of the debug library use it, and those are not reconstructed
#ifdef NONMATCHING
	static int makemask(const char* smask, int count)
	{
		int mask = 0;
		if (strchr(smask, 'c'))
		{
			mask |= LUA_MASKCALL;
		}
		if (strchr(smask, 'r'))
		{
			mask |= LUA_MASKRET;
		}
		if (strchr(smask, 'l'))
		{
			mask |= LUA_MASKLINE;
		}
		if (count > 0)
		{
			mask |= LUA_MASKCOUNT;
		}
		return mask;
	}
#endif

	// FUNCTION: ENGINE 0x10B7A7A0
	// NONMATCHING: only the hook functions of the debug library use it, and those are not reconstructed
#ifdef NONMATCHING
	static char* unmakemask(int mask, char* smask)
	{
		int i = 0;
		if (mask & LUA_MASKCALL)
		{
			smask[i++] = 'c';
		}
		if (mask & LUA_MASKRET)
		{
			smask[i++] = 'r';
		}
		if (mask & LUA_MASKLINE)
		{
			smask[i++] = 'l';
		}
		smask[i] = '\0';
		return smask;
	}
#endif

	// FUNCTION: ENGINE 0x10B7A7E0
	// NONMATCHING: only the hook functions of the debug library use it, and those are not reconstructed
#ifdef NONMATCHING
	static void gethooktable(lua_State* L)
	{
		lua_pushlightuserdata(L, (void*)&KEY_HOOK);
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			lua_createtable(L, 0, 1);
			lua_pushlightuserdata(L, (void*)&KEY_HOOK);
			lua_pushvalue(L, -2);
			lua_rawset(L, LUA_REGISTRYINDEX);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10B7A840
	// NONMATCHING: the engine keeps the stack frame and registers differently (the thread of getthread lives in ebx); ours 95 %
#ifdef NONMATCHING
	static int db_sethook(lua_State* L)
	{
		int arg, mask, count;
		lua_Hook func;
		lua_State* L1 = getthread(L, &arg);
		if (lua_isnoneornil(L, arg + 1))
		{
			lua_settop(L, arg + 1);
			func = NULL;
			mask = 0;
			count = 0; // turn off hooks
		}
		else
		{
			const char* smask = luaL_checkstring(L, arg + 2);
			luaL_checktype(L, arg + 1, LUA_TFUNCTION);
			count = luaL_optint(L, arg + 3, 0);
			func = hookf;
			mask = makemask(smask, count);
		}
		gethooktable(L);
		lua_pushlightuserdata(L, L1);
		lua_pushvalue(L, arg + 1);
		lua_rawset(L, -3); // set new hook
		lua_pop(L, 1); // remove hook table
		lua_sethook(L1, func, mask, count); // set hooks
		return 0;
	}
#else
	int db_sethook(lua_State* L);
#endif

	// FUNCTION: ENGINE 0x10B7A910
	// NONMATCHING: the same register assignment as db_sethook; ours is 11 bytes shorter
#ifdef NONMATCHING
	static int db_gethook(lua_State* L)
	{
		int arg;
		lua_State* L1 = getthread(L, &arg);
		char buff[5];
		int mask = lua_gethookmask(L1);
		lua_Hook hook = lua_gethook(L1);
		if (hook != NULL && hook != hookf)
		{
			// external hook?
			lua_pushliteral(L, "external hook");
		}
		else
		{
			gethooktable(L);
			lua_pushlightuserdata(L, L1);
			lua_rawget(L, -2); // get hook
			lua_remove(L, -2); // remove hook table
		}
		lua_pushstring(L, unmakemask(mask, buff));
		lua_pushinteger(L, lua_gethookcount(L1));
		return 3;
	}
#else
	int db_gethook(lua_State* L);
#endif

	// FUNCTION: ENGINE 0x10B7A9B0
	// NONMATCHING: the loop of the prompt is laid out differently (292 bytes against 281)
#ifdef NONMATCHING
	static int db_debug(lua_State* L)
	{
		for (;;)
		{
			char buffer[250];
			fputs("lua_debug> ", stderr);
			if (fgets(buffer, sizeof(buffer), stdin) == 0 || strcmp(buffer, "cont\n") == 0)
			{
				return 0;
			}
			if (luaL_loadbuffer(L, buffer, strlen(buffer), "=(debug command)") || lua_pcall(L, 0, 0, 0))
			{
				fputs(lua_tostring(L, -1), stderr);
				fputs("\n", stderr);
			}
			lua_settop(L, 0); // remove eventual returns
		}
	}
#else
	int db_debug(lua_State* L);
#endif

#define LEVELS1 12 // size of the first part of the stack
#define LEVELS2 10 // size of the second part of the stack

	// FUNCTION: ENGINE 0x10B7AAE0
	static int db_errorfb(lua_State* L)
	{
		int level;
		int firstpart = 1; // still before eventual `...'
		int arg;
		lua_State* L1 = getthread(L, &arg);
		lua_Debug ar;
		if (lua_isnumber(L, arg + 2))
		{
			level = (int)lua_tointeger(L, arg + 2);
			lua_pop(L, 1);
		}
		else
		{
			level = (L == L1) ? 1 : 0; // level 0 may be this own function
		}
		if (lua_gettop(L) == arg)
		{
			lua_pushliteral(L, "");
		}
		else if (!lua_isstring(L, arg + 1))
		{
			return 1; // message is not a string
		}
		else
		{
			lua_pushliteral(L, "\n");
		}
		lua_pushliteral(L, "stack traceback:");
		while (lua_getstack(L1, level++, &ar))
		{
			if (level > LEVELS1 && firstpart)
			{
				// no more than `LEVELS2' more levels?
				if (!lua_getstack(L1, level + LEVELS2, &ar))
				{
					level--; // keep going
				}
				else
				{
					lua_pushliteral(L, "\n\t..."); // too many levels
					while (lua_getstack(L1, level + LEVELS2, &ar))
					{
						level++; // find last levels
					}
				}
				firstpart = 0;
				continue;
			}
			lua_pushliteral(L, "\n\t");
			lua_getinfo(L1, "Snl", &ar);
			lua_pushfstring(L, "%s:", ar.short_src);
			if (ar.currentline > 0)
			{
				lua_pushfstring(L, "%d:", ar.currentline);
			}
			if (*ar.namewhat != '\0')
			{
				// is there a name?
				lua_pushfstring(L, " in function " LUA_QS, ar.name);
			}
			else
			{
				if (*ar.what == 'm')
				{
					// main?
					lua_pushfstring(L, " in main chunk");
				}
				else if (*ar.what == 'C' || *ar.what == 't')
				{
					lua_pushliteral(L, " ?"); // C function or tail call
				}
				else
				{
					lua_pushfstring(L, " in function <%s:%d>", ar.short_src, ar.linedefined);
				}
			}
			lua_concat(L, lua_gettop(L) - arg);
		}
		lua_concat(L, lua_gettop(L) - arg);
		return 1;
	}

	static const luaL_Reg dblib[] = {
		{"debug", db_debug},
		{"getfenv", db_getfenv},
		{"gethook", db_gethook},
		{"getinfo", db_getinfo},
		{"getlocal", db_getlocal},
		{"getregistry", db_getregistry},
		{"getmetatable", db_getmetatable},
		{"getupvalue", db_getupvalue},
		{"setfenv", db_setfenv},
		{"sethook", db_sethook},
		{"setlocal", db_setlocal},
		{"setmetatable", db_setmetatable},
		{"setupvalue", db_setupvalue},
		{"traceback", db_errorfb},
		{NULL, NULL}};

	// FUNCTION: ENGINE 0x10B7AD40
	int luaopen_debug(lua_State* L)
	{
		luaL_register(L, "ldebug", dblib);
		return 1;
	}
}

