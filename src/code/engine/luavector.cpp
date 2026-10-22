// The Lua binding of math::Vector and core::Name (this unit 0x1083F820 - 0x10841060; no assert path, file name is a
// guess): a vector is a userdata of three floats with the metatable registered under "Vector" in the registry, and the
// metatable's functions (arithmetic, indexing, length, tostring, dot and cross product, lerp ...) are the Lua C
// functions of this unit. A name is a userdata of the metatable "UID" (UID(text), CreateUID(text), UIDFromHash(hash,
// text); the methods DebugGetString and Equals and the metamethods __gc, __tostring and __eq).
#include "code/engine/luascriptmanager.h"
#include "code/lua/lauxlib.h"
#include "code/lua/lua.h"
#include "code/math/vector.h"
#include <math.h>
#include "code/core/hash.h"
#include "code/core/name.h"
#include "code/core/strings.h"
#include <new>
#include <string.h>

namespace engine
{
	// 0x10800860 (luascriptmanager.cpp)
	void* LuaToTypedUserdata(lua_State* L, int index, const char* typeName);

	// FUNCTION: ENGINE 0x1083F820
	// The absolute stack index of a relative one (inlined into the helpers below; the kept copy takes the state in ecx
	// and the index in esi)
	static inline int AbsoluteIndex(lua_State* L, int index)
	{
		if (index > LUA_REGISTRYINDEX && index <= 0)
		{
			return lua_gettop(L) + index + 1;
		}
		return index;
	}

	// FUNCTION: ENGINE 0x1083F840
	// A new vector, zero, with the metatable of the registry's "Vector"
	static math::Vector* NewVector(lua_State* L)
	{
		math::Vector* vector = (math::Vector*)lua_newuserdata(L, sizeof(math::Vector));
		vector->z = 0.0f;
		vector->y = 0.0f;
		vector->x = 0.0f;
		lua_pushlstring(L, "Vector", 6);
		lua_rawget(L, LUA_REGISTRYINDEX);
		lua_setmetatable(L, -2);
		return vector;
	}

	// FUNCTION: ENGINE 0x1083F890
	static math::Vector* ToVectorUserdata(lua_State* L, int index)
	{
		return (math::Vector*)LuaToTypedUserdata(L, index, "Vector");
	}

	// FUNCTION: ENGINE 0x1083F8A0
	static bool IsVector(lua_State* L, int index)
	{
		return ToVectorUserdata(L, index) != 0;
	}

	// FUNCTION: ENGINE 0x1083F8B0
	// EQUIVALENT: the engine takes the state on the stack (and loads it into ebx), ours takes it in ebx, 30.9 %
	// The vector at index copied to out (a type error when there is none)
	static math::Vector* ReadVector(lua_State* L, int index, math::Vector* out)
	{
		index = AbsoluteIndex(L, index);
		const math::Vector* vector = ToVectorUserdata(L, index);
		if (vector != 0)
		{
			out->x = vector->x;
			out->y = vector->y;
			out->z = vector->z;
			return out;
		}
		luaL_typerror(L, index, "Vector");
		return out;
	}

	// FUNCTION: ENGINE 0x1083F910
	// EQUIVALENT: the engine takes the index on the stack, ours in eax, 34.8 %
	// Replaces the vector at index by a table of its three components
	static void ReplaceWithTable(lua_State* L, int index)
	{
		index = AbsoluteIndex(L, index);
		const math::Vector* vector = ToVectorUserdata(L, index);
		lua_createtable(L, 0, 0);
		lua_pushnumber(L, vector->x);
		lua_rawseti(L, -2, 1);
		lua_pushnumber(L, vector->y);
		lua_rawseti(L, -2, 2);
		lua_pushnumber(L, vector->z);
		lua_rawseti(L, -2, 3);
		lua_replace(L, index);
	}

	// FUNCTION: ENGINE 0x1083F9A0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 49.7 %
	static int LuaAdd(lua_State* L)
	{
		if (!IsVector(L, 1) || !IsVector(L, 2))
		{
			lua_pushlstring(L, "at least one operand is not a vector", 36);
			lua_error(L);
		}
		math::Vector* result = NewVector(L);
		math::Vector storage;
		math::Vector* a = ReadVector(L, 1, &storage);
		result->x = a->x;
		result->y = a->y;
		result->z = a->z;
		ReadVector(L, 2, &storage);
		result->x = result->x + storage.x;
		result->y = result->y + storage.y;
		result->z = result->z + storage.z;
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FA60
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 49.7 %
	static int LuaSub(lua_State* L)
	{
		if (!IsVector(L, 1) || !IsVector(L, 2))
		{
			lua_pushlstring(L, "at least one operand is not a vector", 36);
			lua_error(L);
		}
		math::Vector* result = NewVector(L);
		math::Vector storage;
		math::Vector* a = ReadVector(L, 1, &storage);
		result->x = a->x;
		result->y = a->y;
		result->z = a->z;
		ReadVector(L, 2, &storage);
		result->x = result->x - storage.x;
		result->y = result->y - storage.y;
		result->z = result->z - storage.z;
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FB20
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 76.5 %
	static int LuaPow(lua_State* L)
	{
		if (!IsVector(L, 1))
		{
			lua_pushstring(L, "left operand must be a vector");
			lua_error(L);
		}
		if (!lua_isnumber(L, 2))
		{
			lua_pushstring(L, "right operand must be a number");
			lua_error(L);
		}
		math::Vector* result = NewVector(L);
		math::Vector first;
		math::Vector* a = ReadVector(L, 1, &first);
		result->x = a->x;
		result->y = a->y;
		result->z = a->z;
		float exponent = lua_tonumber(L, 2);
		float* components = &result->x;
		for (int i = 0; i < 3; i++)
		{
			components[i] = (float)pow((double)components[i], (double)exponent);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FBE0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ); the engine stores the copy of y after the first subtraction, ours before, 32.6 %
	static int LuaUnm(lua_State* L)
	{
		if (!IsVector(L, 1))
		{
			lua_pushlstring(L, "operand is not a vector", 23);
			lua_error(L);
		}
		math::Vector* result = NewVector(L);
		math::Vector source;
		math::Vector* a = ReadVector(L, 1, &source);
		result->x = a->x;
		result->y = a->y;
		result->z = a->z;
		math::Vector negated(-0.0f - result->x, -0.0f - result->y, -0.0f - result->z);
		result->x = negated.x;
		result->y = negated.y;
		result->z = negated.z;
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FC70
	// The vector at index, a Lua error when there is none
	static math::Vector* CheckVector(lua_State* L, int index)
	{
		math::Vector* vector = ToVectorUserdata(L, index);
		if (vector == 0)
		{
			lua_pushlstring(L, "type mismatch; expected a vector", 32);
			lua_error(L);
		}
		return vector;
	}

	// FUNCTION: ENGINE 0x1083FCA0
	static int LuaIndex(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		lua_getmetatable(L, 1);
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		if (lua_type(L, -1) != LUA_TFUNCTION)
		{
			if (lua_isnumber(L, -1))
			{
				int component = (int)lua_tonumber(L, -1);
				lua_pushnumber(L, (&vector->x)[component]);
			}
			else
			{
				lua_pushstring(L, "invalid index");
				lua_error(L);
				return 0;
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FD30
	static int LuaNewIndex(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		luaL_checktype(L, 3, LUA_TNUMBER);
		lua_getmetatable(L, 1);
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		if (lua_isnumber(L, -1))
		{
			int component = (int)lua_tonumber(L, -1);
			(&vector->x)[component] = lua_tonumber(L, 3);
			return 0;
		}
		lua_pushlstring(L, "invalid subscript in assignment", 31);
		lua_error(L);
		return 0;
	}

	// FUNCTION: ENGINE 0x1083FDC0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 38.1 %
	static int LuaNewVectorFunction(lua_State* L)
	{
		int count = lua_gettop(L);
		if (count == 1)
		{
			math::Vector* result = NewVector(L);
			math::Vector source;
			math::Vector* a = ReadVector(L, 1, &source);
			result->x = a->x;
			result->y = a->y;
			result->z = a->z;
			return 1;
		}
		if (count == 3)
		{
			luaL_checktype(L, 1, LUA_TNUMBER);
			luaL_checktype(L, 2, LUA_TNUMBER);
			luaL_checktype(L, 3, LUA_TNUMBER);
			math::Vector* result = NewVector(L);
			result->x = lua_tonumber(L, 1);
			result->y = lua_tonumber(L, 2);
			result->z = lua_tonumber(L, 3);
			return 1;
		}
		if (count == 0)
		{
			math::Vector* result = NewVector(L);
			result->z = 0.0f;
			result->y = 0.0f;
			result->x = 0.0f;
			return 1;
		}
		lua_pushlstring(L, "syntax error", 12);
		lua_error(L);
		return 0;
	}

	// FUNCTION: ENGINE 0x1083FEB0
	static int LuaToString(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		lua_pushfstring(L, "<Vector:%f,%f,%f>", (double)vector->x, (double)vector->y, (double)vector->z);
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FEF0
	static int LuaNormalize(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		lua_pushnumber(L, vector->Normalize());
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FF20
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 20.6 %
	static int LuaDot(lua_State* L)
	{
		math::Vector first;
		math::Vector second;
		ReadVector(L, 1, &first);
		ReadVector(L, 2, &second);
		lua_pushnumber(L, first.x * second.x + first.y * second.y + first.z * second.z);
		return 1;
	}

	// FUNCTION: ENGINE 0x1083FF90
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 19.2 %
	static int LuaCross(lua_State* L)
	{
		math::Vector* result = CheckVector(L, 1);
		math::Vector first;
		ReadVector(L, 2, &first);
		if (lua_gettop(L) > 2)
		{
			math::Vector third;
			math::Vector* second = ReadVector(L, 3, &third);
			float x = second->z * first.y - second->y * first.z;
			float y = second->x * first.z - second->z * first.x;
			float z = second->y * first.x - second->x * first.y;
			result->x = x;
			result->y = y;
			result->z = z;
			return 0;
		}
		float x = result->y * first.z - result->z * first.y;
		float y = result->z * first.x - result->x * first.z;
		float z = result->x * first.y - result->y * first.x;
		result->x = x;
		result->y = y;
		result->z = z;
		return 0;
	}

	// FUNCTION: ENGINE 0x108400A0
	static int LuaClear(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		vector->z = 0.0f;
		vector->y = 0.0f;
		vector->x = 0.0f;
		return 0;
	}

	// FUNCTION: ENGINE 0x108400D0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 18.6 %
	static int LuaInterpolate(lua_State* L)
	{
		math::Vector* result = CheckVector(L, 1);
		math::Vector from;
		ReadVector(L, 2, &from);
		if (lua_gettop(L) > 3)
		{
			float amount = luaL_checknumber(L, 4);
			math::Vector toStorage;
			math::Vector* to = ReadVector(L, 3, &toStorage);
			result->x = from.x + (to->x - from.x) * amount;
			result->y = from.y + (to->y - from.y) * amount;
			result->z = from.z + (to->z - from.z) * amount;
			return 0;
		}
		float amount = luaL_checknumber(L, 3);
		result->x = result->x + (from.x - result->x) * amount;
		result->y = result->y + (from.y - result->y) * amount;
		result->z = result->z + (from.z - result->z) * amount;
		return 0;
	}

	// FUNCTION: ENGINE 0x108401E0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ); the tails of two cases are shared by the jump here, 24.7 %
	static int LuaScale(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		int count = lua_gettop(L);
		if (count <= 2)
		{
			float scale = luaL_checknumber(L, 2);
			vector->x = vector->x * scale;
			vector->y = scale * vector->y;
			vector->z = scale * vector->z;
			return 0;
		}
		if (count == 3)
		{
			float scale = luaL_checknumber(L, 2);
			math::Vector storage;
			math::Vector* source = ReadVector(L, 3, &storage);
			vector->x = source->x * scale;
			vector->y = source->y * scale;
			vector->z = scale * source->z;
			return 0;
		}
		float scaleX = luaL_checknumber(L, 2);
		float scaleY = luaL_checknumber(L, 3);
		float scaleZ = luaL_checknumber(L, 4);
		vector->x = vector->x * scaleX;
		vector->y = scaleY * vector->y;
		vector->z = scaleZ * vector->z;
		return 0;
	}

	// FUNCTION: ENGINE 0x108402B0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 31.7 %
	static int LuaAddTo(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		math::Vector first;
		math::Vector second;
		if (lua_gettop(L) <= 2)
		{
			math::Vector* other = ReadVector(L, 2, &first);
			vector->x = vector->x + other->x;
			vector->y = other->y + vector->y;
			vector->z = other->z + vector->z;
			return 0;
		}
		math::Vector* last = ReadVector(L, 3, &first);
		math::Vector* other = ReadVector(L, 2, &second);
		vector->x = other->x + last->x;
		vector->y = other->y + last->y;
		vector->z = other->z + last->z;
		return 0;
	}

	// FUNCTION: ENGINE 0x10840370
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 31.7 %
	static int LuaSubFrom(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		math::Vector first;
		math::Vector second;
		if (lua_gettop(L) <= 2)
		{
			math::Vector* other = ReadVector(L, 2, &first);
			vector->x = vector->x - other->x;
			vector->y = vector->y - other->y;
			vector->z = vector->z - other->z;
			return 0;
		}
		math::Vector* last = ReadVector(L, 3, &first);
		math::Vector* other = ReadVector(L, 2, &second);
		vector->x = other->x - last->x;
		vector->y = other->y - last->y;
		vector->z = other->z - last->z;
		return 0;
	}

	// FUNCTION: ENGINE 0x10840430
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 36.2 %
	static int LuaScaleAdd(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		if (lua_gettop(L) <= 3)
		{
			float scale = luaL_checknumber(L, 2);
			math::Vector storage;
			math::Vector* source = ReadVector(L, 3, &storage);
			vector->x = source->x * scale + vector->x;
			vector->y = source->y * scale + vector->y;
			vector->z = scale * source->z + vector->z;
			return 0;
		}
		float scale = luaL_checknumber(L, 3);
		math::Vector firstStorage;
		math::Vector* source = ReadVector(L, 4, &firstStorage);
		math::Vector secondStorage;
		math::Vector* base = ReadVector(L, 2, &secondStorage);
		vector->x = source->x * scale + base->x;
		vector->y = source->y * scale + base->y;
		vector->z = scale * source->z + base->z;
		return 0;
	}

	// FUNCTION: ENGINE 0x10840500
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 43.8 %
	static int LuaMagnitudeSqr(lua_State* L)
	{
		math::Vector vector;
		ReadVector(L, 1, &vector);
		lua_pushnumber(L, vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		return 1;
	}

	// FUNCTION: ENGINE 0x10840560
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 56.1 %
	static int LuaSet(lua_State* L)
	{
		math::Vector* vector = CheckVector(L, 1);
		if (lua_gettop(L) == 2)
		{
			math::Vector storage;
			math::Vector* source = ReadVector(L, 2, &storage);
			vector->x = source->x;
			vector->y = source->y;
			vector->z = source->z;
			return 0;
		}
		float x = luaL_checknumber(L, 2);
		float y = luaL_checknumber(L, 3);
		float z = luaL_checknumber(L, 4);
		vector->x = x;
		vector->y = y;
		vector->z = z;
		return 0;
	}

	// FUNCTION: ENGINE 0x108405F0
	// EQUIVALENT: calls ReplaceWithTable with the index in eax where the engine pushes it, 86.1 %
	static int LuaToTable(lua_State* L)
	{
		CheckVector(L, 1);
		ReplaceWithTable(L, 1);
		return 1;
	}

	// FUNCTION: ENGINE 0x10840840
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ); the engine loads the three components before the three products, 25.4 %
	static int LuaMul(lua_State* L)
	{
		bool firstIsVector = IsVector(L, 1);
		bool secondIsVector = IsVector(L, 2);
		if (firstIsVector)
		{
			if (secondIsVector)
			{
				math::Vector* result = NewVector(L);
				math::Vector firstStorage;
				math::Vector secondStorage;
				math::Vector* first = ReadVector(L, 1, &firstStorage);
				result->x = first->x;
				result->y = first->y;
				result->z = first->z;
				ReadVector(L, 2, &secondStorage);
				float x = result->x;
				float y = result->y;
				float z = result->z;
				result->x = x * secondStorage.x;
				result->y = y * secondStorage.y;
				result->z = z * secondStorage.z;
				return 1;
			}
		}
		else if (!secondIsVector)
		{
			lua_pushlstring(L, "neither operand is a vector", 27);
			lua_error(L);
		}
		math::Vector* result = NewVector(L);
		math::Vector storage;
		float scalar;
		if (firstIsVector)
		{
			math::Vector* source = ReadVector(L, 1, &storage);
			result->x = source->x;
			result->y = source->y;
			result->z = source->z;
			if (!lua_isnumber(L, 2))
			{
				lua_pushlstring(L, "second operand is neither a vector or number", 44);
				lua_error(L);
			}
			scalar = lua_tonumber(L, 2);
		}
		else
		{
			math::Vector* source = ReadVector(L, 2, &storage);
			result->x = source->x;
			result->y = source->y;
			result->z = source->z;
			if (!lua_isnumber(L, 1))
			{
				lua_pushlstring(L, "first operand is neither a vector or number", 43);
				lua_error(L);
			}
			scalar = lua_tonumber(L, 1);
		}
		result->x = scalar * result->x;
		result->y = result->y * scalar;
		result->z = scalar * result->z;
		return 1;
	}

	// scalar / vector, component by component (the engine keeps an unused out-of-line copy at 0x10840800)
	static inline math::Vector DivideScalarByVector(float scalar, const math::Vector& vector)
	{
		math::Vector result;
		result.x = scalar / vector.x;
		result.y = scalar / vector.y;
		result.z = scalar / vector.z;
		return result;
	}

	// FUNCTION: ENGINE 0x108409E0
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ); the scalar divided by the vector is divided on the x87 stack here (the same single precision result), the engine's divides in SSE and shares the store of z with the vector division, 39.0 %
	static int LuaDiv(lua_State* L)
	{
		bool firstIsVector = IsVector(L, 1);
		bool secondIsVector = IsVector(L, 2);
		float z;
		math::Vector* result;
		math::Vector storage;
		if (firstIsVector && secondIsVector)
		{
			result = NewVector(L);
			math::Vector* first = ReadVector(L, 1, &storage);
			result->x = first->x;
			result->y = first->y;
			result->z = first->z;
			ReadVector(L, 2, &storage);
			result->x = result->x / storage.x;
			result->y = result->y / storage.y;
			z = result->z / storage.z;
		}
		else
		{
			if (!firstIsVector && !secondIsVector)
			{
				lua_pushlstring(L, "neither operand is a vector", 27);
				lua_error(L);
			}
			result = NewVector(L);
			if (firstIsVector)
			{
				math::Vector* source = ReadVector(L, 1, &storage);
				result->x = source->x;
				result->y = source->y;
				result->z = source->z;
				if (!lua_isnumber(L, 2))
				{
					lua_pushlstring(L, "second operand is neither a vector or number", 44);
					lua_error(L);
				}
				float inverse = 1.0f / lua_tonumber(L, 2);
				result->x = inverse * result->x;
				result->y = result->y * inverse;
				result->z = inverse * result->z;
				return 1;
			}
			math::Vector* source = ReadVector(L, 2, &storage);
			result->x = source->x;
			result->y = source->y;
			result->z = source->z;
			if (!lua_isnumber(L, 1))
			{
				lua_pushlstring(L, "first operand is neither a vector or number", 43);
				lua_error(L);
			}
			float scalar = lua_tonumber(L, 1);
			*result = DivideScalarByVector(scalar, *result);
			return 1;
		}
		result->z = z;
		return 1;
	}

	// FUNCTION: ENGINE 0x10840B90
	// EQUIVALENT: ReadVector takes the state in ebx, the engine's on the stack (call sequences and stack offsets differ), 69.0 %
	static int LuaMagnitude(lua_State* L)
	{
		math::Vector vector;
		ReadVector(L, 1, &vector);
		lua_pushnumber(L, sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
		return 1;
	}

	static const luaL_Reg sVectorFunctions[] =
	{
		{ "Vector", LuaNewVectorFunction },
		{ 0, 0 }
	};

	static const luaL_Reg sVectorMethods[] =
	{
		{ "normalize", LuaNormalize },
		{ "mag", LuaMagnitude },
		{ "magnitude", LuaMagnitude },
		{ "dot", LuaDot },
		{ "dotProduct", LuaDot },
		{ "cross", LuaCross },
		{ "crossProduct", LuaCross },
		{ "clear", LuaClear },
		{ "interpolate", LuaInterpolate },
		{ "scale", LuaScale },
		{ "add", LuaAddTo },
		{ "sub", LuaSubFrom },
		{ "scaleAdd", LuaScaleAdd },
		{ "magnitudeSqr", LuaMagnitudeSqr },
		{ "set", LuaSet },
		{ "toTable", LuaToTable },
		{ "__index", LuaIndex },
		{ "__newindex", LuaNewIndex },
		{ "__add", LuaAdd },
		{ "__sub", LuaSub },
		{ "__mul", LuaMul },
		{ "__div", LuaDiv },
		{ "__pow", LuaPow },
		{ "__unm", LuaUnm },
		{ "__tostring", LuaToString },
		{ 0, 0 }
	};

	// FUNCTION: ENGINE 0x10840620
	// Registers the global function Vector and the metatable "Vector" (the component names and positions map to the
	// index of the component)
	static int OpenVectorLibrary(lua_State* L)
	{
		lua_pushvalue(L, LUA_GLOBALSINDEX);
		luaI_openlib(L, 0, sVectorFunctions, 0);
		lua_settop(L, -2);
		luaL_newmetatable(L, "Vector");
		luaI_openlib(L, 0, sVectorMethods, 0);
		lua_pushlstring(L, "__persist", 9);
		lua_pushboolean(L, 1);
		lua_rawset(L, -3);
		lua_pushlstring(L, "x", 1);
		lua_pushnumber(L, 0.0f);
		lua_rawset(L, -3);
		lua_pushlstring(L, "y", 1);
		lua_pushnumber(L, 1.0f);
		lua_rawset(L, -3);
		lua_pushlstring(L, "z", 1);
		lua_pushnumber(L, 2.0f);
		lua_rawset(L, -3);
		lua_pushnumber(L, 1.0f);
		lua_pushnumber(L, 0.0f);
		lua_rawset(L, -3);
		lua_pushnumber(L, 2.0f);
		lua_pushnumber(L, 1.0f);
		lua_rawset(L, -3);
		lua_pushnumber(L, 3.0f);
		lua_pushnumber(L, 2.0f);
		lua_rawset(L, -3);
		lua_settop(L, -2);
		return 0;
	}

	// FUNCTION: ENGINE 0x10840770
	int LuaPushVector(lua_State* L, const math::Vector& value)
	{
		math::Vector* vector = NewVector(L);
		vector->x = value.x;
		vector->y = value.y;
		vector->z = value.z;
		return 1;
	}

	// FUNCTION: ENGINE 0x108407A0
	const math::Vector* LuaToVector(lua_State* L, int index)
	{
		const math::Vector* vector = ToVectorUserdata(L, index);
		if (vector == 0)
		{
			luaL_typerror(L, index, "Vector");
		}
		return vector;
	}

	// FUNCTION: ENGINE 0x108407D0
	bool LuaIsVector(lua_State* L, int index)
	{
		return IsVector(L, index) != 0;
	}

	// FUNCTION: ENGINE 0x108407F0
	void LuaOpenVector(lua_State* L)
	{
		OpenVectorLibrary(L);
	}

	typedef core::Name<core::CaseSensitiveKey> UidName;

	// The Lua source that makes a UID persist: a function that gives a function building it again from its hash and text
	// (0x10E6FCA8; the global holds the pointer, 0x111C6CA4)
	const char* gLuaNamePersistScript = "return function( hashVal, string )\n    return function()\n        return UIDFromHash( hashVal, string )\n    end\nend\n";

	// FUNCTION: ENGINE 0x10840BE0
	const UidName* LuaToName(lua_State* L, int index)
	{
		return (const UidName*)luaL_checkudata(L, index, "UID");
	}

	// FUNCTION: ENGINE 0x10840C00
	bool LuaIsUid(lua_State* L, int index)
	{
		return LuaToTypedUserdata(L, index, "UID") != 0;
	}

	// FUNCTION: ENGINE 0x10840C20
	// A new empty name userdata with the metatable of the registry's "UID"
	static UidName* NewUid(lua_State* L)
	{
		UidName* name = (UidName*)lua_newuserdata(L, sizeof(UidName));
		if (name != 0)
		{
			new (name) UidName;
		}
		lua_pushlstring(L, "UID", 3);
		lua_rawget(L, LUA_REGISTRYINDEX);
		lua_setmetatable(L, -2);
		return name;
	}

	// FUNCTION: ENGINE 0x10840C60
	static int LuaUidNew(lua_State* L)
	{
		UidName* name = NewUid(L);
		const char* text = luaL_optlstring(L, 1, "", 0);
		if (name != 0)
		{
			new (name) UidName(text, 1);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10840CA0
	static int LuaUidClear(lua_State* L)
	{
		UidName* name = (UidName*)lua_touserdata(L, 1);
		name->SetText(0);
		return 1;
	}

	// FUNCTION: ENGINE 0x10840CC0
	static int LuaUidDebugGetString(lua_State* L)
	{
		const UidName* name = (const UidName*)luaL_checkudata(L, 1, "UID");
		lua_pushstring(L, name->GetText());
		return 1;
	}

	// FUNCTION: ENGINE 0x10840CF0
	static int LuaUidToString(lua_State* L)
	{
		const UidName* name = (const UidName*)luaL_checkudata(L, 1, "UID");
		char hash[0x20];
		unsigned __int64 value = name->GetHash();
		core::SNPrintf(hash, 0x20, "0x%08X%08X", (unsigned int)(value >> 32), (unsigned int)value);
		lua_pushfstring(L, "<UID:%s,%s>", name->GetText(), hash);
		return 1;
	}
	// FUNCTION: ENGINE 0x10840D60
	// EQUIVALENT: the engine sets the bool with mov eax, 1 / xor eax, eax where ours uses al, 99.0 %
	static int LuaUidEquals(lua_State* L)
	{
		const UidName* name = (const UidName*)luaL_checkudata(L, 1, "UID");
		unsigned __int64 hash = name->GetHash();
		unsigned __int64 other;
		int type = lua_type(L, 2);
		if (type == LUA_TSTRING)
		{
			const char* text = lua_tolstring(L, 2, 0);
			other = core::Hash64(text, 0);
		}
		else if (type == LUA_TUSERDATA && LuaIsUid(L, 2))
		{
			other = ((const UidName*)lua_touserdata(L, 2))->GetHash();
		}
		else
		{
			lua_pushboolean(L, 0);
			return 1;
		}
		bool equal = hash == other;
		lua_pushboolean(L, equal != 0);
		return 1;
	}

	// FUNCTION: ENGINE 0x10840E40
	static int LuaUidEq(lua_State* L)
	{
		const UidName* first = (const UidName*)lua_touserdata(L, 1);
		const UidName* second = (const UidName*)lua_touserdata(L, 2);
		lua_pushboolean(L, second->operator==(*first));
		return 1;
	}

	// FUNCTION: ENGINE 0x10840E80
	static int LuaUidFromHash(lua_State* L)
	{
		luaL_checktype(L, 1, LUA_TSTRING);
		luaL_checktype(L, 2, LUA_TSTRING);
		size_t length;
		const char* bytes = luaL_checklstring(L, 1, &length);
		if (length != 8)
		{
			luaL_error(L, "hash value '%s' is invalid", bytes);
		}
		unsigned __int64 hash = *(const unsigned __int64*)bytes;
		UidName* name = NewUid(L);
		if (name != 0)
		{
			new (name) UidName(lua_tolstring(L, 2, 0), 1);
		}
		name->SetHash(hash);
		return 1;
	}

	// FUNCTION: ENGINE 0x10840F00
	// The function __persist of a name returns: calls the persist script's function with the name's hash (8 bytes) and
	// text
	static int LuaUidPersist(lua_State* L)
	{
		const UidName* name = LuaToName(L, 1);
		lua_pushvalue(L, LUA_GLOBALSINDEX - 1);
		unsigned __int64 hash = name->GetHash();
		lua_pushlstring(L, (const char*)&hash, 8);
		lua_pushstring(L, name->GetText());
		lua_call(L, 2, 1);
		return 1;
	}

	static const luaL_Reg sUidFunctions[] =
	{
		{ "UID", LuaUidNew },
		{ "CreateUID", LuaUidNew },
		{ "UIDFromHash", LuaUidFromHash },
		{ 0, 0 }
	};

	static const luaL_Reg sUidMethods[] =
	{
		{ "DebugGetString", LuaUidDebugGetString },
		{ "Equals", LuaUidEquals },
		{ "__gc", LuaUidClear },
		{ "__tostring", LuaUidToString },
		{ "__eq", LuaUidEq },
		{ 0, 0 }
	};

	// FUNCTION: ENGINE 0x10840F70
	int LuaOpenUid(lua_State* L)
	{
		lua_pushvalue(L, LUA_GLOBALSINDEX);
		luaI_openlib(L, 0, sUidFunctions, 0);
		lua_settop(L, -2);
		luaL_newmetatable(L, "UID");
		lua_pushlstring(L, "__index", 7);
		lua_pushvalue(L, -2);
		lua_rawset(L, -3);
		luaI_openlib(L, 0, sUidMethods, 0);
		luaL_loadbuffer(L, gLuaNamePersistScript, core::StrLen(gLuaNamePersistScript), "=LuaNamePersistScript");
		lua_pcall(L, 0, LUA_MULTRET, 0);
		lua_pushcclosure(L, LuaUidPersist, 1);
		lua_pushlstring(L, "__persist", 9);
		lua_insert(L, -2);
		lua_rawset(L, -3);
		lua_settop(L, -2);
		return 0;
	}

	// FUNCTION: ENGINE 0x10841040
	int LuaPushName(lua_State* L, const UidName& name)
	{
		UidName* pushed = NewUid(L);
		*pushed = name;
		return 1;
	}
}
