// CFLAGS: !/arch /Oy-
// Lua 5.1 lmathlib.c (Standard mathematical library; the engine's build with float numbers, unit 0x10B7B510 - 0x10B7BD60). The functions
// are internal to the unit.
#include <stdlib.h>
#include <math.h>

#include "code/lua/lua.h"
#include "code/lua/lauxlib.h"

#undef PI
#define PI (3.14159265358979323846f)
#define RADIANS_PER_DEGREE (PI / 180.0f)

#define luaL_checkint(L, n) ((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L, n, d) ((int)luaL_optinteger(L, (n), (d)))
#define luaL_argcheck(L, cond, numarg, extramsg) ((void)((cond) || luaL_argerror(L, (numarg), (extramsg))))

namespace engine
{
	// FUNCTION: ENGINE 0x10B7B5F0
	static int math_abs(lua_State* L)
	{
		lua_pushnumber(L, fabs(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B620
	static int math_sin(lua_State* L)
	{
		lua_pushnumber(L, sin(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B650
	static int math_sinh(lua_State* L)
	{
		lua_pushnumber(L, sinh(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B680
	static int math_cos(lua_State* L)
	{
		lua_pushnumber(L, cos(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B6B0
	static int math_cosh(lua_State* L)
	{
		lua_pushnumber(L, cosh(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B6E0
	static int math_tan(lua_State* L)
	{
		lua_pushnumber(L, tan(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B710
	static int math_tanh(lua_State* L)
	{
		lua_pushnumber(L, tanh(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B740
	static int math_asin(lua_State* L)
	{
		lua_pushnumber(L, asin(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B770
	static int math_acos(lua_State* L)
	{
		lua_pushnumber(L, acos(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B7A0
	static int math_atan(lua_State* L)
	{
		lua_pushnumber(L, atan(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B7D0
	static int math_atan2(lua_State* L)
	{
		lua_pushnumber(L, atan2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B810
	static int math_ceil(lua_State* L)
	{
		lua_pushnumber(L, ceil(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B840
	static int math_floor(lua_State* L)
	{
		lua_pushnumber(L, floor(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B870
	static int math_fmod(lua_State* L)
	{
		lua_pushnumber(L, fmod(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B8B0
	static int math_modf(lua_State* L)
	{
		double ip;
		double fp = modf(luaL_checknumber(L, 1), &ip);
		lua_pushnumber(L, ip);
		lua_pushnumber(L, fp);
		return 2;
	}

	// FUNCTION: ENGINE 0x10B7B900
	static int math_sqrt(lua_State* L)
	{
		lua_pushnumber(L, sqrt(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B930
	static int math_pow(lua_State* L)
	{
		lua_pushnumber(L, pow(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B970
	static int math_log(lua_State* L)
	{
		lua_pushnumber(L, log(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B9A0
	static int math_log10(lua_State* L)
	{
		lua_pushnumber(L, log10(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7B9D0
	static int math_exp(lua_State* L)
	{
		lua_pushnumber(L, exp(luaL_checknumber(L, 1)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7BA10
	static int math_deg(lua_State* L)
	{
		lua_pushnumber(L, luaL_checknumber(L, 1) / RADIANS_PER_DEGREE);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7BA40
	static int math_rad(lua_State* L)
	{
		lua_pushnumber(L, luaL_checknumber(L, 1) * RADIANS_PER_DEGREE);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7BA70
	static int math_frexp(lua_State* L)
	{
		int e;
		lua_pushnumber(L, frexp(luaL_checknumber(L, 1), &e));
		lua_pushinteger(L, e);
		return 2;
	}

	// FUNCTION: ENGINE 0x10B7BAC0
	static int math_ldexp(lua_State* L)
	{
		lua_pushnumber(L, ldexp(luaL_checknumber(L, 1), luaL_checkint(L, 2)));
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7BB10
	static int math_min(lua_State* L)
	{
		int n = lua_gettop(L); // number of arguments
		lua_Number dmin = luaL_checknumber(L, 1);
		int i;
		for (i = 2; i <= n; i++)
		{
			lua_Number d = luaL_checknumber(L, i);
			if (d < dmin)
			{
				dmin = d;
			}
		}
		lua_pushnumber(L, dmin);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7BB80
	static int math_max(lua_State* L)
	{
		int n = lua_gettop(L); // number of arguments
		lua_Number dmax = luaL_checknumber(L, 1);
		int i;
		for (i = 2; i <= n; i++)
		{
			lua_Number d = luaL_checknumber(L, i);
			if (d > dmax)
			{
				dmax = d;
			}
		}
		lua_pushnumber(L, dmax);
		return 1;
	}

	// The engine's version draws from the fight random number generator (not reconstructed)
	int math_random(lua_State* L);

	// The seed is not used
	// FUNCTION: ENGINE 0x10B7BD40
	static int math_randomseed(lua_State* L)
	{
		return 0;
	}

	static const luaL_Reg mathlib[] = {
		{"abs", math_abs},
		{"acos", math_acos},
		{"asin", math_asin},
		{"atan2", math_atan2},
		{"atan", math_atan},
		{"ceil", math_ceil},
		{"cosh", math_cosh},
		{"cos", math_cos},
		{"deg", math_deg},
		{"exp", math_exp},
		{"floor", math_floor},
		{"fmod", math_fmod},
		{"frexp", math_frexp},
		{"ldexp", math_ldexp},
		{"log10", math_log10},
		{"log", math_log},
		{"max", math_max},
		{"min", math_min},
		{"modf", math_modf},
		{"pow", math_pow},
		{"rad", math_rad},
		{"random", math_random},
		{"randomseed", math_randomseed},
		{"sinh", math_sinh},
		{"sin", math_sin},
		{"sqrt", math_sqrt},
		{"tanh", math_tanh},
		{"tan", math_tan},
		{NULL, NULL}};

	// FUNCTION: ENGINE 0x10B7BD50
	int luaopen_math(lua_State* L)
	{
		luaL_register(L, "math", mathlib);
		lua_pushnumber(L, (lua_Number)PI);
		lua_setfield(L, -2, "pi");
		lua_pushnumber(L, HUGE_VAL);
		lua_setfield(L, -2, "huge");
		lua_getfield(L, -1, "fmod");
		lua_setfield(L, -2, "mod");
		return 1;
	}
}
