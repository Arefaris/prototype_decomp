// CFLAGS: /TC !/arch
// Lua 5.1.1 ltm.c (Tag methods; unit 0x10630A80 - 0x10630B6F). The library is compiled as C.
#include <string.h>

#include "code/lua/lua.h"
#include "code/lua/lobject.h"
#include "code/lua/lstate.h"
#include "code/lua/lstring.h"
#include "code/lua/ltable.h"
#include "code/lua/ltm.h"

const char* const luaT_typenames[] = {
	"nil", "boolean", "userdata", "number",
	"string", "table", "function", "userdata", "thread",
	"proto", "upval"
};

// FUNCTION: ENGINE 0x10630A80
void luaT_init(lua_State* L)
{
	static const char* const luaT_eventname[] = {
		// ORDER TM
		"__index", "__newindex",
		"__gc", "__mode", "__eq",
		"__add", "__sub", "__mul", "__div", "__mod",
		"__pow", "__unm", "__len", "__lt", "__le",
		"__concat", "__call"
	};
	int i;
	for (i = 0; i < TM_N; i++)
	{
		G(L)->tmname[i] = luaS_new(L, luaT_eventname[i]);
		luaS_fix(G(L)->tmname[i]); // never collect these names
	}
}

// function to be used with macro "fasttm": optimized for absence of tag methods
// FUNCTION: ENGINE 0x10630AE0
const TValue* luaT_gettm(Table* events, TMS event, TString* ename)
{
	const TValue* tm = luaH_getstr(events, ename);
	lua_assert(event <= TM_EQ);
	if (ttisnil(tm))
	{
		// no tag method?
		events->flags |= cast_byte(1u << event); // cache this fact
		return NULL;
	}
	else
	{
		return tm;
	}
}

// FUNCTION: ENGINE 0x10630B10
const TValue* luaT_gettmbyobj(lua_State* L, const TValue* o, TMS event)
{
	Table* mt;
	switch (ttype(o))
	{
	case LUA_TTABLE:
		mt = hvalue(o)->metatable;
		break;
	case LUA_TUSERDATA:
		mt = uvalue(o)->metatable;
		break;
	default:
		mt = G(L)->mt[ttype(o)];
		break;
	}
	return (mt ? luaH_getstr(mt, G(L)->tmname[event]) : luaO_nilobject);
}
