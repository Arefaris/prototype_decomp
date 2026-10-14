#include "code/engine/luascriptmanager.h"
#include "code/core/debugger.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/vector.h"
#include "code/core/report.h"
#include "code/core/thread.h"
#include "code/core/time.h"
#include "code/engine/function.h"
#include "code/lua/lua.h"
#include <string.h>

namespace engine
{
	// FUNCTION: ENGINE 0x107FE6B0
	void* ScriptBlockPool::Take()
	{
		for (int i = 0; i < 2; i++)
		{
			if (free[i])
			{
				free[i] = false;
				return blocks[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107FE6E0
	bool ScriptBlockPool::Give(void* block)
	{
		bool result = false;
		for (int i = 0; i < 2; i++)
		{
			if (block == blocks[i])
			{
				result = true;
				free[i] = true;
				break;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x107FE720
	void* Function::operator new(unsigned int size)
	{
		if (size == 0x14000)
		{
			void* block = gScriptBlockPool->Take();
			if (block != 0)
			{
				return block;
			}
			return core::HeapAlloc(0x7a, 0x14000);
		}
		return core::HeapAlloc(0x7a, size);
	}

	// FUNCTION: ENGINE 0x107FE760
	void Function::operator delete(void* block)
	{
		if (block != 0 && !gScriptBlockPool->Give(block))
		{
			core::Free(block);
		}
	}

	// FUNCTION: ENGINE 0x107FE790
	void* ScriptRealloc(void* user, void* block, unsigned int oldSize, unsigned int newSize)
	{
		if (newSize == 0)
		{
			Function::operator delete(block);
			return 0;
		}
		void* result = Function::operator new(newSize);
		if (block != 0)
		{
			memcpy(result, block, oldSize <= newSize ? oldSize : newSize);
			Function::operator delete(block);
		}
		return result;
	}

	template<class T> bool ScriptNameTable<T>::Add(T* entry)
	{
		const char* name = entry->name;
		if (count >= capacity)
		{
			return false;
		}
		int index;
		if (name != 0 && *name != 0)
		{
			for (index = 0; index < count; index++)
			{
				const char* other = entries[index]->name;
				if (other == 0 || *other == 0 || strcmp(other, name) >= 0)
				{
					goto found;
				}
			}
		}
		index = count;
	found:
		for (int i = count; i > index; i--)
		{
			entries[i] = entries[i - 1];
		}
		entries[index] = entry;
		count++;
		return true;
	}

	template<class T> const char* ScriptNameTable<T>::Complete(const char* prefix, const char* previous)
	{
		if (prefix == 0 || *prefix == 0)
		{
			return 0;
		}
		int first;
		for (first = 0; first < count; first++)
		{
			if (strncmp(prefix, entries[first]->name, strlen(prefix)) == 0)
			{
				goto found;
			}
		}
		return 0;
	found:
		if (first < 0)
		{
			return 0;
		}
		if (previous != 0 && *previous != 0 && strncmp(prefix, previous, strlen(prefix)) == 0)
		{
			for (int i = first; i < count; i++)
			{
				if (strcmp(entries[i]->name, previous) == 0)
				{
					if (i >= 0 && i != count - 1)
					{
						if (strncmp(prefix, entries[i + 1]->name, strlen(prefix)) == 0)
						{
							return entries[i + 1]->name;
						}
						return entries[first]->name;
					}
					break;
				}
			}
		}
		return entries[first]->name;
	}

	template<class T> bool ScriptNameTable<T>::Remove(const char* name)
	{
		if (name != 0 && *name != 0)
		{
			for (int i = 0; i < count; i++)
			{
				const char* other = entries[i]->name;
				if (other != 0 && *other != 0 && strcmp(other, name) == 0)
				{
					if (entries[i] != 0)
					{
						delete entries[i];
						entries[i] = 0;
					}
					for (int j = i + 1; j < count; j++)
					{
						entries[j - 1] = entries[j];
					}
					entries[count - 1] = 0;
					count--;
					return true;
				}
			}
		}
		return false;
	}

	template<class T> void ScriptNameTable<T>::SetGeneration(unsigned char value)
	{
		for (int i = 0; i < count; i++)
		{
			entries[i]->generation = value;
		}
	}

	template class ScriptNameTable<Function>;
	template class ScriptNameTable<LuaCFunction>;

	// The object the breakpoint keeps updating while the game waits (0x10853890, another unit; names guessed)
	class ServicePump
	{
	public:
		virtual void Update(core::Time elapsed) = 0;
	};

	ServicePump* GetServicePump();

	// 0x108407D0 / 0x10840C00 (another unit): whether the value at index is a math::Vector / a UID userdata
	bool LuaIsVector(lua_State* L, int index);
	bool LuaIsUid(lua_State* L, int index);
	// 0x10840770 / 0x10841040 (another unit): push a math::Vector / a core::Name as their userdata
	void LuaPushVector(lua_State* L, const math::Vector& value);
	void LuaPushName(lua_State* L, const core::Name<core::CaseSensitiveKey>& name);
	// 0x108407A0 (another unit): the math::Vector of the userdata at index
	const math::Vector* LuaToVector(lua_State* L, int index);

	// FUNCTION: ENGINE 0x107FEFF0
	void ShutdownScriptManager()
	{
		delete gScriptManager;
		gScriptManager = 0;
		delete gScriptBlockPool;
		gScriptBlockPool = 0;
	}

	// FUNCTION: ENGINE 0x107FF030
	// print, writing the values through tostring (Lua's luaB_print with the output left on the stack)
	int LuaPrint(lua_State* L)
	{
		int count = lua_gettop(L);
		lua_getfield(L, LUA_GLOBALSINDEX, "tostring");
		lua_checkstack(L, count * 3 + 3);
		for (int i = 1; i <= count; i++)
		{
			lua_pushvalue(L, count + 1);
			lua_pushvalue(L, i);
			lua_call(L, 1, 1);
			if (lua_tolstring(L, -1, 0) == 0)
			{
				lua_pushstring(L, "`tostring' must return a string to `print'");
				lua_error(L);
			}
			if (i < count)
			{
				lua_pushlstring(L, " ", 1);
			}
		}
		lua_concat(L, count * 2 - 1);
		return 0;
	}

	// FUNCTION: ENGINE 0x107FF0E0
	// type, naming handles "GOH" and the vector / UID userdata
	int LuaType(lua_State* L)
	{
		luaL_checkany(L, 1);
		switch (lua_type(L, 1))
		{
		case LUA_TUSERDATA:
			if (LuaIsVector(L, 1))
			{
				lua_pushlstring(L, "Vector", 6);
			}
			else if (LuaIsUid(L, 1))
			{
				lua_pushlstring(L, "UID", 3);
			}
			else
			{
				lua_pushstring(L, lua_typename(L, lua_type(L, 1)));
			}
			break;
		case LUA_TLIGHTUSERDATA:
			lua_pushlstring(L, "GOH", 3);
			break;
		default:
			lua_pushstring(L, lua_typename(L, lua_type(L, 1)));
			break;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x107FF190
	// The stack traceback (Lua's db_errorfb)
	int LuaTraceback(lua_State* L)
	{
		int level = luaL_optinteger(L, 1, 0) + 1;
		int firstPart = 1;
		lua_settop(L, 0);
		lua_Debug ar;
		while (lua_getstack(L, level++, &ar))
		{
			if (level > 12 && firstPart)
			{
				if (!lua_getstack(L, level + 10, &ar))
				{
					level--;
				}
				else
				{
					lua_pushlstring(L, "\n\t...", 5);
					while (lua_getstack(L, level + 10, &ar))
					{
						level++;
					}
				}
				firstPart = 0;
				continue;
			}
			lua_pushlstring(L, "\n\t", 2);
			lua_getinfo(L, "Snl", &ar);
			lua_pushfstring(L, "%s:", ar.short_src);
			if (ar.currentline > 0)
			{
				lua_pushfstring(L, "%d:", ar.currentline);
			}
			switch (*ar.namewhat)
			{
			case 'g':
			case 'l':
			case 'f':
			case 'm':
				lua_pushfstring(L, " in function `%s'", ar.name);
				break;
			default:
				if (*ar.what == 'm')
				{
					lua_pushfstring(L, " in main chunk");
				}
				else if (*ar.what == 'C' || *ar.what == 't')
				{
					lua_pushlstring(L, " ?", 2);
				}
				else
				{
					lua_pushfstring(L, " in function <%s:%d>", ar.short_src, ar.linedefined);
				}
			}
			lua_concat(L, lua_gettop(L));
		}
		lua_concat(L, lua_gettop(L));
		return 1;
	}

	// FUNCTION: ENGINE 0x107FF360
	// breakpoint: asks what to do; "Continue" waits (servicing GameLink) until _BREAK is cleared
	int LuaBreakpoint(lua_State* L)
	{
		int level = luaL_optinteger(L, 1, 0) + 1;
		switch (core::DispatchReport(1, "lua", "", 0, ""))
		{
		case 0:
		case 4:
			core::DebugSignal(3);
			return 0;
		case 1:
		case 3:
			return 0;
		case 2:
			{
				lua_pushlstring(L, "Stack traceback:", 16);
				lua_pushcclosure(L, LuaTraceback, 0);
				lua_pushinteger(L, level);
				lua_call(L, 1, 1);
				lua_concat(L, 2);
				lua_pushboolean(L, 1);
				lua_setfield(L, LUA_GLOBALSINDEX, "_BREAK");
				lua_getfield(L, LUA_GLOBALSINDEX, "_BREAK");
				bool waiting = lua_toboolean(L, -1) != 0;
				lua_settop(L, -2);
				while (waiting)
				{
					core::ThreadSleep(0);
					ServicePump* pump = GetServicePump();
					if (pump != 0)
					{
						pump->Update(core::Time(0, 0));
					}
					lua_getfield(L, LUA_GLOBALSINDEX, "_BREAK");
					waiting = lua_toboolean(L, -1) != 0;
					lua_settop(L, -2);
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107FF4C0
	bool LuaScriptManager::RemoveCFunction(const char* name)
	{
		bool removed = cfunctions.Remove(name);
		if (removed && state != 0)
		{
			lua_pushnil(state);
			lua_setfield(state, LUA_GLOBALSINDEX, name);
		}
		return removed;
	}

	// FUNCTION: ENGINE 0x107FF500
	void LuaScriptManager::SetTableInteger(const char* table, const char* key, int value)
	{
		lua_getfield(state, LUA_GLOBALSINDEX, table);
		if (lua_type(state, -1) == LUA_TTABLE)
		{
			lua_pushstring(state, key);
			lua_pushinteger(state, value);
			lua_rawset(state, -3);
		}
		lua_settop(state, -2);
	}

	// FUNCTION: ENGINE 0x107FF570
	// The Lua side of a registered C function without an upvalue
	int CallCFunction(lua_State* L)
	{
		int (*function)(lua_State*) = (int (*)(lua_State*))lua_touserdata(L, LUA_GLOBALSINDEX - 1);
		return function(L);
	}

	// FUNCTION: ENGINE 0x107FF590
	// The same with the registered upvalue as a second argument
	int CallCFunctionUpvalue(lua_State* L)
	{
		if (!lua_isuserdata(L, LUA_GLOBALSINDEX - 1))
		{
			return 0;
		}
		int (*function)(lua_State*, void*) = (int (*)(lua_State*, void*))lua_touserdata(L, LUA_GLOBALSINDEX - 1);
		if (!lua_isuserdata(L, LUA_GLOBALSINDEX - 2))
		{
			return 0;
		}
		return function(L, lua_touserdata(L, LUA_GLOBALSINDEX - 2));
	}

	// FUNCTION: ENGINE 0x107FF5F0
	void LuaScriptManager::CopyGlobal(lua_State* L, const char* name, bool keyAfter)
	{
		if (!keyAfter)
		{
			lua_pushstring(L, name);
		}
		lua_getfield(L, LUA_GLOBALSINDEX, name);
		if (lua_type(L, -1) == LUA_TNIL)
		{
			lua_settop(L, -2);
			return;
		}
		if (keyAfter)
		{
			lua_pushstring(L, name);
		}
		lua_rawset(L, -3);
	}

	// FUNCTION: ENGINE 0x107FF660
	void LuaScriptManager::CopyRegistryValue(lua_State* L, const char* name, bool keyAfter)
	{
		if (!keyAfter)
		{
			lua_pushstring(L, name);
		}
		lua_pushstring(L, name);
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (lua_type(L, -1) == LUA_TNIL)
		{
			lua_settop(L, -2);
			return;
		}
		if (keyAfter)
		{
			lua_pushstring(L, name);
		}
		lua_rawset(L, -3);
	}

	// FUNCTION: ENGINE 0x107FF6D0
	// Whether the value on top holds no functions (tables are followed, visited marks them with the answer)
	bool LuaScriptManager::IsPlainData(lua_State* L, int visited, int unused)
	{
		if (lua_type(L, -1) == LUA_TFUNCTION)
		{
			lua_iscfunction(L, -1);
			return false;
		}
		if (lua_type(L, -1) == LUA_TTABLE)
		{
			lua_pushvalue(L, -1);
			lua_rawget(L, visited);
			if (lua_type(L, -1) == LUA_TNIL)
			{
				lua_settop(L, -2);
				int result = 1;
				lua_pushvalue(L, -1);
				lua_pushboolean(L, result);
				lua_rawset(L, visited);
				lua_pushnil(L);
				while (lua_next(L, -2))
				{
					if (!IsPlainData(L, visited, unused))
					{
						lua_settop(L, -3);
						result = 0;
						lua_pushvalue(L, -1);
						lua_pushboolean(L, result);
						lua_rawset(L, visited);
						break;
					}
					lua_settop(L, -2);
				}
				return result != 0;
			}
			int plain = lua_toboolean(L, -1);
			lua_settop(L, -2);
			return plain != 0;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x107FF810
	void LuaScriptManager::PushMetatables(lua_State* L, bool keyAfter)
	{
		lua_createtable(L, 0, 0);
		CopyRegistryValue(L, "Vector", keyAfter);
		CopyRegistryValue(L, "UID", keyAfter);
	}

	// FUNCTION: ENGINE 0x107FF870
	bool LuaScriptManager::RemoveFunction(const char* name)
	{
		bool removed = functions.Remove(name);
		if (removed && state != 0)
		{
			lua_pushnil(state);
			lua_setfield(state, LUA_GLOBALSINDEX, name);
		}
		return removed;
	}

	// FUNCTION: ENGINE 0x107FF8B0
	// The number of references in use (integer keys of the registry less the free list)
	int LuaScriptManager::CountReferences()
	{
		int count = 0;
		lua_pushvalue(state, LUA_REGISTRYINDEX);
		lua_pushnil(state);
		while (lua_next(state, -2))
		{
			if (lua_type(state, -2) == LUA_TNUMBER && lua_tointeger(state, -2) != 0)
			{
				count++;
			}
			lua_settop(state, -2);
		}
		lua_settop(state, -2);
		lua_rawgeti(state, LUA_REGISTRYINDEX, 0);
		if (lua_type(state, -1) != LUA_TNIL)
		{
			lua_rawget(state, LUA_REGISTRYINDEX);
			while (count > 0 && lua_type(state, -1) != LUA_TNIL)
			{
				count--;
				lua_rawget(state, LUA_REGISTRYINDEX);
			}
		}
		lua_settop(state, -2);
		return count;
	}

	// FUNCTION: ENGINE 0x107FF9B0
	void LuaScriptManager::CloseState(lua_State** L)
	{
		if (*L != 0)
		{
			lua_close(*L);
			*L = 0;
		}
	}

	// FUNCTION: ENGINE 0x107FF9D0
	bool IsGlobalDefined(lua_State* L, const char* name)
	{
		lua_pushstring(L, name);
		lua_rawget(L, LUA_GLOBALSINDEX);
		bool defined = lua_type(L, -1) != LUA_TNIL;
		lua_settop(L, -2);
		return defined;
	}

	// FUNCTION: ENGINE 0x107FFA10
	// The report level of a Lua error status (names guessed)
	int LuaScriptManager::GetErrorLevel(int status)
	{
		int level = 0;
		switch (status)
		{
		case 2:
			level = 3;
			break;
		case 3:
			level = 2;
			break;
		case 4:
			level = 3;
			break;
		case 5:
			level = 3;
			break;
		case 6:
			level = 1;
			break;
		}
		return level;
	}

	// FUNCTION: ENGINE 0x107FFA60
	bool LuaScriptManager::AddWatch(const char* name)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x107FFA70
	bool LuaScriptManager::DeleteWatch(const char* name)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x107FFA80
	bool LuaScriptManager::GetUnknownB4() const
	{
		return unknownB4;
	}

	// FUNCTION: ENGINE 0x107FFA90
	void LuaScriptManager::SetUnknownB4(bool value)
	{
		unknownB4 = value;
	}

	// FUNCTION: ENGINE 0x107FFAA0
	void LuaScriptManager::SetUnknownB6(bool value)
	{
		unknownB6 = value;
	}

	// FUNCTION: ENGINE 0x107FFAB0
	void LuaScriptManager::CollectGarbage(bool full)
	{
		if (full)
		{
			lua_gc(state, LUA_GCCOLLECT, 0);
			return;
		}
		lua_gc(state, LUA_GCSTEP, 5);
	}

	// FUNCTION: ENGINE 0x107FFAE0
	const char* LuaScriptManager::Complete(const char* prefix, const char* previous)
	{
		const char* name = functions.Complete(prefix, previous);
		if (name == 0)
		{
			name = cfunctions.Complete(prefix, previous);
		}
		return name;
	}

	// FUNCTION: ENGINE 0x107FFB10
	int ProtectedCall(lua_State* L, int argumentCount, int resultCount)
	{
		return lua_pcall(L, argumentCount, resultCount, 0);
	}

	// FUNCTION: ENGINE 0x107FFB30
	// HC_REGISTRY = the registry; context = { event = {} }
	void LuaScriptManager::InitContextTables(lua_State* L)
	{
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		lua_setfield(L, LUA_GLOBALSINDEX, "HC_REGISTRY");
		lua_pushlstring(L, "context", 7);
		lua_createtable(L, 0, 0);
		lua_pushlstring(L, "event", 5);
		lua_createtable(L, 0, 0);
		lua_rawset(L, -3);
		lua_rawset(L, LUA_GLOBALSINDEX);
	}

	// FUNCTION: ENGINE 0x107FFBA0
	int LuaRef(lua_State* L)
	{
		return luaL_ref(L, LUA_REGISTRYINDEX);
	}

	// FUNCTION: ENGINE 0x107FFBC0
	bool LuaUnref(lua_State* L, int reference)
	{
		if (reference == 0)
		{
			return false;
		}
		luaL_unref(L, LUA_REGISTRYINDEX, reference);
		return true;
	}

	// FUNCTION: ENGINE 0x107FFBF0
	bool LuaPushRef(lua_State* L, int reference)
	{
		if (reference == 0)
		{
			return false;
		}
		lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
		if (lua_type(L, -1) == LUA_TNIL)
		{
			lua_settop(L, -2);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x107FFC30
	bool LuaScriptManager::PushReference(int reference)
	{
		return LuaPushRef(state, reference);
	}

	// FUNCTION: ENGINE 0x107FFC50
	// Calls the function at base with the values above it; the number of results, -1 on an error
	int LuaScriptManager::Call(int base)
	{
		int top = lua_gettop(state);
		if (base < 0)
		{
			base += top + 1;
		}
		if (ProtectedCall(state, top - base, -1) != 0)
		{
			return -1;
		}
		return lua_gettop(state) + (1 - base);
	}

	// FUNCTION: ENGINE 0x107FFCB0
	bool LuaScriptManager::CreateTable(const char* name, bool global)
	{
		int index = -3;
		if (global)
		{
			index = LUA_GLOBALSINDEX;
		}
		lua_pushstring(state, name);
		lua_createtable(state, 0, 0);
		lua_rawset(state, index);
		return true;
	}

	// FUNCTION: ENGINE 0x107FFD00
	void LuaScriptManager::Pop(int count)
	{
		lua_settop(state, -1 - count);
	}

	// FUNCTION: ENGINE 0x107FFD20
	bool LuaHasField(lua_State* L, const char* name)
	{
		lua_pushstring(L, name);
		lua_rawget(L, -2);
		bool found = lua_type(L, -1) != LUA_TNIL;
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x107FFD60
	bool LuaToString(lua_State* L, char* buffer, int size, bool pop)
	{
		const char* text = lua_tolstring(L, -1, 0);
		bool result = true;
		if (text == 0)
		{
			result = false;
		}
		else
		{
			core::SNPrintf(buffer, size, "%s", text);
		}
		if (pop)
		{
			lua_settop(L, -2);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x107FFDB0
	bool LuaPushString(lua_State* L, const char* text)
	{
		lua_pushstring(L, text);
		return true;
	}

	// FUNCTION: ENGINE 0x107FFDD0
	bool LuaToFloat(lua_State* L, float* value)
	{
		bool result = true;
		if (lua_type(L, -1) != LUA_TNUMBER)
		{
			result = false;
		}
		else
		{
			*value = lua_tonumber(L, -1);
		}
		lua_settop(L, -2);
		return result;
	}

	// FUNCTION: ENGINE 0x107FFE20
	bool LuaPushFloat(lua_State* L, float value)
	{
		lua_pushnumber(L, value);
		return true;
	}

	// FUNCTION: ENGINE 0x107FFE40
	bool LuaToBool(lua_State* L, bool* value)
	{
		bool result = true;
		switch (lua_type(L, -1))
		{
		case LUA_TNIL:
			*value = false;
			break;
		case LUA_TBOOLEAN:
			*value = lua_toboolean(L, -1) != 0;
			break;
		case LUA_TNUMBER:
			*value = lua_tonumber(L, -1) != 0.0f;
			break;
		default:
			result = false;
		}
		lua_settop(L, -2);
		return result;
	}

	// FUNCTION: ENGINE 0x107FFF10
	bool LuaPushBool(lua_State* L, bool value)
	{
		lua_pushboolean(L, value);
		return true;
	}

	// FUNCTION: ENGINE 0x107FFF30
	bool LuaToFunctionRef(lua_State* L, int* reference)
	{
		bool result = true;
		if (lua_type(L, -1) != LUA_TFUNCTION)
		{
			result = false;
			lua_settop(L, -2);
		}
		else
		{
			*reference = LuaRef(L);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x107FFF70
	// Starts walking the table on top (up to eight walks nest)
	bool LuaScriptManager::BeginTableWalk()
	{
		if (walkDepth < 7 && walkDepth >= -1)
		{
			walkDepth++;
			walkTops[walkDepth] = lua_gettop(state);
			lua_pushnil(state);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107FFFB0
	bool LuaScriptManager::NextTableEntry(int index)
	{
		if (walkDepth < 0)
		{
			return false;
		}
		int top = lua_gettop(state);
		int base = walkTops[walkDepth];
		if (top != base + 1)
		{
			lua_settop(state, base);
			return false;
		}
		return lua_next(state, index) != 0;
	}

	// FUNCTION: ENGINE 0x10800010
	void LuaScriptManager::EndTableWalk()
	{
		if (walkDepth >= 0)
		{
			int top = lua_gettop(state);
			int base = walkTops[walkDepth];
			if (top != base)
			{
				lua_settop(state, base);
			}
			walkDepth--;
		}
	}

	// FUNCTION: ENGINE 0x10800050
	// Pushes the context table
	bool LuaScriptManager::OpenContext()
	{
		int top = lua_gettop(state);
		lua_pushlstring(state, "context", 7);
		lua_rawget(state, LUA_GLOBALSINDEX);
		if (lua_type(state, -1) != LUA_TTABLE)
		{
			lua_settop(state, top);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108000B0
	bool LuaScriptManager::Close()
	{
		lua_settop(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x108000D0
	bool LuaScriptManager::CloseContext()
	{
		lua_settop(state, -2);
		return true;
	}

	// FUNCTION: ENGINE 0x108000F0
	bool LuaScriptManager::SetString(const char* key, const char* value)
	{
		lua_pushstring(state, key);
		lua_pushstring(state, value);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x10800130
	bool LuaScriptManager::SetFloat(const char* key, float value)
	{
		lua_pushstring(state, key);
		lua_pushnumber(state, value);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x10800170
	bool LuaScriptManager::SetInt(const char* key, int value)
	{
		lua_pushstring(state, key);
		lua_pushnumber(state, (float)value);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x108001B0
	bool LuaScriptManager::SetBool(const char* key, bool value)
	{
		lua_pushstring(state, key);
		lua_pushboolean(state, value);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x108001F0
	bool LuaScriptManager::SetVector(const char* key, math::Vector value)
	{
		lua_pushstring(state, key);
		LuaPushVector(state, value);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x10800230
	bool LuaScriptManager::SetHandle(const char* key, SerializedHandle handle)
	{
		lua_pushstring(state, key);
		lua_pushlightuserdata(state, *(void**)&handle);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x10800270
	bool LuaScriptManager::SetName(const char* key, const core::Name<core::CaseSensitiveKey>& name)
	{
		lua_pushstring(state, key);
		LuaPushName(state, name);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x108002B0
	bool LuaScriptManager::ClearField(const char* key)
	{
		lua_pushstring(state, key);
		lua_pushnil(state);
		lua_rawset(state, -3);
		return true;
	}

	// FUNCTION: ENGINE 0x108002F0
	void SetScriptError(LuaScriptManager* manager, const char* format, ...)
	{
		manager->hasError = true;
		core::VSNPrintf(manager->errorText, 0x100, format, (char*)(&format + 1));
	}

	// FUNCTION: ENGINE 0x10800320
	const char* LuaScriptManager::GetErrorText()
	{
		return errorText;
	}

	// FUNCTION: ENGINE 0x10800330
	// Calls the function below the arguments for one result; on an error prints the message (false)
	bool LuaScriptManager::CallPrintingErrors(int argumentCount)
	{
		if (ProtectedCall(state, argumentCount, 1) == 0)
		{
			return true;
		}
		lua_getfield(state, LUA_GLOBALSINDEX, "print");
		lua_insert(state, -2);
		lua_pcall(state, 1, 0, 0);
		return false;
	}

	// FUNCTION: ENGINE 0x10800390
	int LuaScriptManager::GetTopType()
	{
		return lua_type(state, -1);
	}

	// FUNCTION: ENGINE 0x108003A0
	// The value on top as each type; true without a destination, false when the value is not of the type
	bool LuaGetBool(lua_State* L, bool* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) == 0)
			{
				return false;
			}
			if (lua_type(L, -1) != LUA_TBOOLEAN)
			{
				return false;
			}
			*value = lua_toboolean(L, -1) != 0;
			return true;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108003F0
	bool LuaGetInt(lua_State* L, int* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) == 0)
			{
				return false;
			}
			if (lua_type(L, -1) != LUA_TNUMBER)
			{
				return false;
			}
			*value = (int)lua_tonumber(L, -1);
			return true;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10800440
	bool LuaGetFloat(lua_State* L, float* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) == 0)
			{
				return false;
			}
			if (lua_type(L, -1) != LUA_TNUMBER)
			{
				return false;
			}
			*value = lua_tonumber(L, -1);
			return true;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10800490
	bool LuaGetString(lua_State* L, LuaStringBuffer* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) == 0)
			{
				return false;
			}
			if (lua_type(L, -1) != LUA_TSTRING)
			{
				return false;
			}
			if (lua_objlen(L, -1) >= value->capacity)
			{
				return false;
			}
			core::StrCpy(value->buffer, lua_tolstring(L, -1, 0));
			return true;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108004F0
	bool LuaGetVector(lua_State* L, math::Vector* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) != 0 && LuaIsVector(L, -1))
			{
			const math::Vector* vector = LuaToVector(L, -1);
			value->x = vector->x;
			value->y = vector->y;
			value->z = vector->z;
				return true;
			}
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10800550
	bool LuaGetHandle(lua_State* L, GameObjectHandle* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) != 0 && lua_type(L, -1) == LUA_TLIGHTUSERDATA)
			{
			SerializedHandle saved;
			saved.value = (unsigned int)lua_touserdata(L, -1);
			*value = DeserializeHandle(saved);
				return true;
			}
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108005B0
	void LuaScriptManager::PushInt(int value)
	{
		lua_pushnumber(state, (float)value);
	}

	// FUNCTION: ENGINE 0x108005D0
	void LuaScriptManager::PushFloat(float value)
	{
		lua_pushnumber(state, value);
	}

	// FUNCTION: ENGINE 0x108005F0
	void LuaScriptManager::PushBool(bool value)
	{
		lua_pushboolean(state, value);
	}

	// FUNCTION: ENGINE 0x10800610
	void LuaScriptManager::PushString(const char* value)
	{
		lua_pushstring(state, value);
	}

	// FUNCTION: ENGINE 0x10800630
	void LuaScriptManager::PushVector(math::Vector value)
	{
		LuaPushVector(state, value);
	}

	// FUNCTION: ENGINE 0x10800650
	void LuaScriptManager::PushHandle(GameObjectHandle handle)
	{
		SerializedHandle saved = SerializeHandle(handle);
		lua_pushlightuserdata(state, (void*)saved.value);
	}

	// FUNCTION: ENGINE 0x10800680
	bool LuaScriptManager::PushGlobalFunction(const char* name)
	{
		lua_pushstring(state, name);
		lua_rawget(state, LUA_GLOBALSINDEX);
		if (lua_type(state, -1) != LUA_TFUNCTION)
		{
			lua_settop(state, -2);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108006D0
	int LuaScriptManager::GetTop()
	{
		return lua_gettop(state);
	}

	// FUNCTION: ENGINE 0x108006E0
	void LuaScriptManager::SetTop(int index)
	{
		lua_settop(state, index);
	}

	// FUNCTION: ENGINE 0x10800700
	// Copies the table at source into the table at target, nested tables as copies
	void LuaCopyTable(lua_State* L, int source, int target)
	{
		lua_pushnil(L);
		while (lua_next(L, source - 1))
		{
			if (lua_type(L, -1) == LUA_TTABLE)
			{
				lua_pushvalue(L, -2);
				lua_createtable(L, 0, 0);
				lua_rawset(L, target - 4);
				lua_pushvalue(L, -2);
				lua_rawget(L, target - 3);
				LuaCopyTable(L, -2, -1);
				lua_settop(L, -3);
			}
			else
			{
				lua_pushvalue(L, -2);
				lua_insert(L, -2);
				lua_rawset(L, target - 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x108007B0
	// The state of the coroutine on top: 1 running, 2 suspended or normal, 3 dead
	int LuaScriptManager::GetThreadStatus(int unused)
	{
		lua_State* thread = lua_tothread(state, -1);
		if (state == thread)
		{
			return 1;
		}
		lua_Debug ar;
		if (lua_getstack(thread, 0, &ar) == 0 && lua_gettop(thread) == 0)
		{
			return 3;
		}
		return 2;
	}

	// FUNCTION: ENGINE 0x10800820
	void LuaScriptManager::NextGeneration()
	{
		generation++;
		functions.SetGeneration(generation);
		cfunctions.SetGeneration(generation);
	}

	// FUNCTION: ENGINE 0x107FEFB0
	LuaScriptManager* GetScriptManager()
	{
		return gScriptManager;
	}

	// FUNCTION: ENGINE 0x107FF850
	void LuaScriptManager::SetOwner(const void* newOwner)
	{
		owner = newOwner;
	}

	// FUNCTION: ENGINE 0x107FF860
	void LuaScriptManager::ClearOwner()
	{
		owner = 0;
	}
}
