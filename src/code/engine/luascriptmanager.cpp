#include "code/engine/luascriptmanager.h"
#include "code/core/debugger.h"
#include "code/core/file/file.h"
#include "code/core/file/filesystem.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/message.h"
#include "code/engine/luaenvironmentmessage.h"
#include "code/math/vector.h"
#include "code/core/report.h"
#include "code/core/thread.h"
#include "code/core/time.h"
#include "code/engine/function.h"
#include "code/lua/lua.h"
#include <string.h>

namespace engine
{
	// FUNCTION: ENGINE 0x107FE6A0
	ScriptBlockPool::ScriptBlockPool()
	{
		memset(free, true, sizeof(free));
	}

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

	// FUNCTION: ENGINE 0x107FE7E0
	LuaCFunction::LuaCFunction(const char* newName, int (*newFunction)(lua_State*), bool newHasUpvalue, void* newUpvalue)
	{
		owner = 0;
		name = newName;
		function = newFunction;
		hasUpvalue = newHasUpvalue;
		upvalue = newUpvalue;
		generation = 0;
	}

	inline void* LuaCFunction::operator new(unsigned int size)
	{
		return Function::operator new(size);
	}

	inline void LuaCFunction::operator delete(void* block)
	{
		Function::operator delete(block);
	}

	template<class T> ScriptNameTable<T>::ScriptNameTable(unsigned int newCapacity)
	{
		capacity = newCapacity;
		count = 0;
		entries = new (0x7a) T*[newCapacity];
	}

	template<class T> ScriptNameTable<T>::~ScriptNameTable()
	{
		delete[] entries;
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

	// FUNCTION: ENGINE 0x107FEF70
	bool ScheduledCall::IsLater(const ScheduledCall& other) const
	{
		if (time > other.time)
		{
			return true;
		}
		if (time == other.time)
		{
			return id > other.id;
		}
		return false;
	}

	// 0x107EF1D0 (gameobjectsystem.cpp)
	MessageListenerRef GetListeners(MessageListeners* listeners);

	// 0x1005F240 (another unit's copy of the inline GameObjectHandle::Get; a thiscall without stack arguments)
	GameObject* __fastcall GameObjectHandleGet(const GameObjectHandle* handle);

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
	int LuaPushVector(lua_State* L, const math::Vector& value);
	int LuaPushName(lua_State* L, const core::Name<core::CaseSensitiveKey>& name);
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
	// print, writing the values through tostring (Lua's luaB_print with the output left on the stack); the channel is
	// not used in this build
	int LuaPrint(lua_State* L, const char* channel)
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

	// The command completion state: the prefix and the last name answered (0x11284258 / 0x11284658)
	extern char gCompletionPrefix[0x400];
	extern char gCompletionLast[0x400];

	// 0x108A6DA0 (another unit): reads the file and line out of a chunk name ("=L<file>:<line>"); names guessed
	bool ParseChunkName(const char* name, unsigned int* first, unsigned int* second);
	// 0x105A84D0 (another unit): shows a script error (names guessed)
	void ShowScriptError(int kind, const char* text, const char* title, unsigned int first, unsigned int second,
		int line);
	// 0x10840BE0 (another unit): the core::Name of the UID userdata at index
	const core::Name<core::CaseSensitiveKey>* LuaToName(lua_State* L, int index);
	// The Lua libraries the state opens (0x10B7EAE0 and the following; the first also opens coroutine)
	int luaopen_base(lua_State* L);
	int luaopen_string(lua_State* L);
	int luaopen_math(lua_State* L);
	int luaopen_table(lua_State* L);
	int luaopen_debug(lua_State* L);
	// 0x108407F0 / 0x10840F70 / 0x108A6FA0 (other units): register the Vector and UID userdata types and a third
	// library in a state
	void LuaOpenVector(lua_State* L);
	int LuaOpenUid(lua_State* L);
	void LuaOpenGame(lua_State* L);
	// 0x10098F50 (another unit): stores value in slot, taking a reference on it and releasing the old one
	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
	// 0x10B77640 / 0x10B78990 (other unit): write / read the table on top of a state with the given arguments
	void LuaSerialize(lua_State* L, int first, int second);
	void LuaDeserialize(lua_State* L, int first, int second);

	// FUNCTION: ENGINE 0x10800860
	// The userdata at index when its metatable is the registry's typeName
	void* LuaToTypedUserdata(lua_State* L, int index, const char* typeName)
	{
		void* data = lua_touserdata(L, index);
		if (data != 0 && lua_getmetatable(L, index) != 0)
		{
			lua_getfield(L, LUA_REGISTRYINDEX, typeName);
			if (lua_rawequal(L, -1, -2) != 0)
			{
				lua_settop(L, -3);
				return data;
			}
			lua_settop(L, -3);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108008D0
	void DebugEnableChannel(const char* channel)
	{
	}

	// FUNCTION: ENGINE 0x108008E0
	void DebugDisableChannel(const char* channel)
	{
	}

	// FUNCTION: ENGINE 0x10800D10
	// The type code of the ScriptResult enumeration (4 bytes)
	char GetScriptResultTypeCode()
	{
		return Function::GetTypeCode(typeid(LuaScriptManager::ScriptResult), 4);
	}

	// FUNCTION: ENGINE 0x10800E40
	bool ScheduleOrder::operator()(const ScheduledCall& first, const ScheduledCall& second) const
	{
		return first.IsLater(second);
	}

	// FUNCTION: ENGINE 0x10800E60
	// The next function name after the last answer that starts with the prefix (the search wraps around)
	const char* NextCommandCompletion()
	{
		for (;;)
		{
			lua_State* L = GetScriptManager()->state;
			lua_gettop(L);
			unsigned int length = strlen(gCompletionPrefix);
			bool found = gCompletionLast[0] == 0;
			lua_pushnil(L);
			while (lua_next(L, LUA_GLOBALSINDEX) != 0)
			{
				if (lua_type(L, -1) == LUA_TFUNCTION && lua_type(L, -2) == LUA_TSTRING)
				{
					const char* name = lua_tolstring(L, -2, 0);
					if (found)
					{
						if (strncmp(gCompletionPrefix, name, length) == 0)
						{
							core::StrNCpy(gCompletionLast, name, 0x400u);
							lua_settop(L, -3);
							return gCompletionLast;
						}
					}
					else if (strcmp(name, gCompletionLast) == 0)
					{
						found = true;
					}
				}
				lua_settop(L, -2);
			}
			if (gCompletionLast[0] == 0)
			{
				return "";
			}
			gCompletionLast[0] = 0;
		}
	}

	// FUNCTION: ENGINE 0x10800FA0
	const char* StartCommandCompletion(const char* prefix)
	{
		core::StrNCpy(gCompletionPrefix, prefix, 0x400u);
		gCompletionLast[0] = 0;
		return NextCommandCompletion();
	}

	// FUNCTION: ENGINE 0x10800FD0
	// The error function of the protected calls: the message and a traceback, then the report decides (break into
	// the debugger, run LuaBreakpoint, or go on); a runtime error shows its script location
	int LuaErrorHandler(lua_State* L)
	{
		if (lua_gettop(L) == 0)
		{
			lua_pushlstring(L, "", 0);
		}
		else
		{
			if (lua_isstring(L, 1) == 0)
			{
				return 1;
			}
			lua_pushlstring(L, "\n", 1);
		}
		lua_pushlstring(L, "\n***** LUA SCRIPT ERROR *****\n", 0x1e);
		lua_insert(L, 1);
		lua_pushlstring(L, "stack traceback:", 0x10);
		lua_pushcclosure(L, LuaTraceback, 0);
		lua_pushinteger(L, 1);
		lua_call(L, 1, 1);
		lua_concat(L, 4);
		const char* file = "unknown";
		int line = 0;
		lua_Debug ar;
		if (lua_getstack(L, 1, &ar) != 0)
		{
			lua_getinfo(L, "Snl", &ar);
			file = ar.short_src;
			if (ar.currentline > 0)
			{
				line = ar.currentline;
			}
		}
		const char* message = lua_tolstring(L, -1, 0);
		switch (core::DispatchReport(GetScriptManager()->unknownB4 != 0, "error/lua", file, line, message))
		{
		case 0:
		case 4:
			core::DebugSignal(3);
			return 0;
		case 1:
			lua_pushcclosure(L, LuaBreakpoint, 0);
			lua_pushinteger(L, 1);
			lua_call(L, 1, 0);
			break;
		}
		int level = 1;
		if (lua_getstack(L, level, &ar) != 0)
		{
			do
			{
				level++;
				lua_getinfo(L, "S", &ar);
				if (*ar.source == '=' && (*ar.what == 'L' || *ar.what == 'm'))
				{
					unsigned int first = 0;
					unsigned int second = 0;
					if (ParseChunkName(ar.source + 1, &first, &second))
					{
						char text[0x400];
						core::SNPrintf(text, 0x400, "LUA RUNTIME ERROR\n%s\n", message);
						ShowScriptError(1, text, "Lua Error", first, second, line);
						return 1;
					}
				}
			}
			while (lua_getstack(L, level, &ar) != 0);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10801200
	// print (registered as the global)
	int LuaGlobalPrint(lua_State* L)
	{
		return LuaPrint(L, "/lua");
	}

	// FUNCTION: ENGINE 0x10801220
	// EQUIVALENT: the engine keeps -1 in edi for its returns, the compiler here uses immediates
	// cdebug(channel, ...): print on a channel named by the first argument
	int LuaChannelPrint(lua_State* L)
	{
		if (lua_gettop(L) < 1)
		{
			return -1;
		}
		lua_getfield(L, LUA_GLOBALSINDEX, "tostring");
		lua_pushvalue(L, 1);
		lua_call(L, 1, 1);
		const char* name = lua_tolstring(L, -1, 0);
		if (name == 0)
		{
			lua_settop(L, -2);
			lua_pushstring(L, "'LuaDebugChannel':  invalid channel name.");
			lua_error(L);
			return -1;
		}
		char channel[0x40];
		core::SNPrintf(channel, 0x40, "%s", name);
		lua_settop(L, -2);
		lua_remove(L, 1);
		return LuaPrint(L, channel);
	}

	// FUNCTION: ENGINE 0x108012E0
	// checkError(condition, message, level): reports the message with the script location when the condition fails
	int LuaCheckError(lua_State* L)
	{
		luaL_checkany(L, 1);
		bool ok = lua_toboolean(L, 1) != 0;
		const char* message = luaL_checklstring(L, 2, 0);
		int level = luaL_optinteger(L, 3, 0) + 1;
		if (!ok)
		{
			const char* file = "unknown";
			int line = 0;
			lua_Debug ar;
			if (lua_getstack(L, level, &ar) != 0)
			{
				lua_getinfo(L, "Snl", &ar);
				file = ar.short_src;
				if (ar.currentline > 0)
				{
					line = ar.currentline;
				}
			}
			char text[0x200];
			core::SNPrintf(text, 0x200, "Lua Error: %s(%d): %s", file, line, message);
			switch (core::DispatchReport(GetScriptManager()->unknownB4 != 0, "lua", file, line, text))
			{
			case 0:
			case 4:
				core::DebugSignal(3);
				break;
			case 1:
				lua_pushcclosure(L, LuaBreakpoint, 0);
				lua_pushinteger(L, level);
				lua_call(L, 1, 0);
				break;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10801410
	void LuaScriptManager::BindCFunction(LuaCFunction* function)
	{
		lua_pushlightuserdata(state, (void*)function->function);
		if (function->hasUpvalue)
		{
			lua_pushlightuserdata(state, function->upvalue);
			lua_pushcclosure(state, CallCFunctionUpvalue, 2);
		}
		else
		{
			lua_pushcclosure(state, CallCFunction, 1);
		}
		lua_setfield(state, LUA_GLOBALSINDEX, function->name);
	}

	// FUNCTION: ENGINE 0x10801480
	// A global table for an enumeration; its __dummyFunction is the error function
	void LuaScriptManager::CreateEnum(const char* name)
	{
		lua_createtable(state, 0, 0);
		int table = lua_gettop(state);
		lua_pushstring(state, name);
		lua_pushvalue(state, table);
		lua_rawset(state, LUA_GLOBALSINDEX);
		lua_pushstring(state, "__dummyFunction");
		lua_pushcclosure(state, LuaErrorHandler, 0);
		lua_rawset(state, table);
		lua_settop(state, -2);
	}

	// FUNCTION: ENGINE 0x10801500
	void LuaScriptManager::AddEnumValue(const char* table, const char* key, int value)
	{
		SetTableInteger(table, key, value);
		if (!reloaded && enumValues.end < enumValues.capacity)
		{
			LuaEnumValue* slot = enumValues.end;
			enumValues.end = slot + 1;
			if (slot != 0)
			{
				slot->table = table;
				slot->key = key;
				slot->value = value;
			}
		}
	}

	// FUNCTION: ENGINE 0x10801550
	// A new table with the entries of the globals (or of the table of reference) that hold no functions
	void LuaScriptManager::CopyPlainData(lua_State* L, int reference, int unused)
	{
		lua_createtable(L, 0, 0);
		int result = lua_gettop(L);
		int source = LUA_GLOBALSINDEX;
		if (reference >= 0)
		{
			PushReference(reference);
			source = lua_gettop(L);
		}
		lua_createtable(L, 0, 0);
		int visited = lua_gettop(L);
		lua_pushvalue(L, source);
		lua_pushboolean(L, 0);
		lua_rawset(L, visited);
		lua_pushnil(L);
		while (lua_next(L, source) != 0)
		{
			if (IsPlainData(L, visited, unused))
			{
				lua_pushvalue(L, -2);
				lua_insert(L, -2);
				lua_rawset(L, result);
			}
			else
			{
				lua_settop(L, -2);
			}
		}
		lua_settop(L, result);
	}

	// FUNCTION: ENGINE 0x10801630
	// Copies the entries of the table on top back into the globals (or the table of reference)
	void LuaScriptManager::RestorePlainData(lua_State* L, int reference)
	{
		int target = LUA_GLOBALSINDEX;
		if (reference >= 0)
		{
			PushReference(reference);
			lua_insert(L, -2);
			target = -5;
		}
		lua_pushnil(L);
		while (lua_next(L, -2) != 0)
		{
			lua_pushvalue(L, -2);
			lua_insert(L, -2);
			lua_rawset(L, target);
		}
		lua_settop(L, -2);
		lua_settop(L, -2);
		if (reference >= 0)
		{
			lua_settop(L, -2);
		}
	}

	// FUNCTION: ENGINE 0x108016C0
	void LuaScriptManager::Unregister(const void* owner)
	{
		int count = functions.count;
		for (int i = 0; i < count; i++)
		{
			Function* function = functions.entries[i];
			if (function->owner == owner)
			{
				const char* name = function->name;
				if (RemoveFunction(name))
				{
					count = functions.count;
					i--;
				}
			}
		}
		count = cfunctions.count;
		for (int i = 0; i < count; i++)
		{
			LuaCFunction* function = cfunctions.entries[i];
			if (function->owner == owner)
			{
				const char* name = function->name;
				if (RemoveCFunction(name))
				{
					count = cfunctions.count;
					i--;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10801740
	void LuaScriptManager::UnregisterAll()
	{
		while (functions.count > 0)
		{
			RemoveFunction(functions.entries[0]->name);
		}
		while (cfunctions.count > 0)
		{
			RemoveCFunction(cfunctions.entries[0]->name);
		}
	}

	// FUNCTION: ENGINE 0x10801790
	// EQUIVALENT: same control flow and calls; the frame is one word larger (the locals are laid out differently) and
	// the registers that hold the function and its name differ
	// The Lua side of every registered Function: checks the arguments of the call, converts them into slots, calls
	// the function and pushes its result
	int LuaDispatch(lua_State* L)
	{
		if (lua_isuserdata(L, LUA_GLOBALSINDEX - 1) == 0)
		{
			luaL_error(L, "LuaScriptManager::Dispatch(): userdata not found\n");
		}
		Function* function = (Function*)lua_touserdata(L, LUA_GLOBALSINDEX - 1);
		if (function->argumentCount != lua_gettop(L))
		{
			luaL_error(L, "%s: wrong number of parameters %d/%d\n", function->name, lua_gettop(L),
				function->argumentCount);
		}
		math::Vector vectorResult;
		float floatResult;
		int intResult;
		const char* stringResult;
		bool boolResult;
		unsigned int handleResult;
		ScriptArguments args;
		args.cursor = args.data;
		memset(args.cursor, 0, sizeof(args.data));
		for (int i = 1; i <= function->argumentCount; i++)
		{
			int type = lua_type(L, i);
			core::Name<core::CaseSensitiveKey> name;
			void* value;
			char code = function->GetArgumentType(i - 1);
			switch (code)
			{
			case 'e':
			case 'i':
				if (type != LUA_TNUMBER)
				{
					luaL_error(L, "%s:  arg %d: not a number\n", function->name, i);
				}
				value = (void*)(int)lua_tonumber(L, i);
				goto pushValue;
			case 'f':
				{
					if (type != LUA_TNUMBER)
					{
						luaL_error(L, "%s:  arg %d: not a number\n", function->name, i);
					}
					float number = lua_tonumber(L, i);
					args.Push(number);
				}
				break;
			case 's':
				if (lua_type(L, i) != LUA_TNIL)
				{
					if (type != LUA_TSTRING)
					{
						luaL_error(L, "%s:  arg %d: not a string\n", function->name, i);
					}
					value = (void*)lua_tolstring(L, i, 0);
				}
				else
				{
					value = 0;
				}
				goto pushValue;
			case 'h':
			case 'v':
				if (type == LUA_TLIGHTUSERDATA)
				{
					value = lua_touserdata(L, i);
				pushValue:
					args.Push(value);
				}
				else if (type == LUA_TNIL)
				{
					if (code == 'h')
					{
						args.Push((void*)0xffffffff);
					}
					else
					{
						args.Push((void*)0);
					}
				}
				else
				{
					luaL_error(L, "%s:  arg %d: not a lightuserdata value\n", function->name, i);
				}
				break;
			case 'b':
				args.Push(lua_toboolean(L, i) != 0);
				break;
			case 'V':
				args.Push(*LuaToVector(L, i));
				break;
			case 'n':
				if (lua_type(L, i) == LUA_TSTRING)
				{
					name = core::Name<core::CaseSensitiveKey>(lua_tolstring(L, i, 0), 1);
				}
				else
				{
					name = *LuaToName(L, i);
				}
				args.Push(name);
				break;
			default:
				return 0;
			}
		}
		LuaScriptManager* manager = GetScriptManager();
		manager->hasError = false;
		char resultCode = function->resultType;
		core::Name<core::CaseSensitiveKey> nameResult;
		handleResult = 0xffffffff;
		int pushed = 0;
		switch (resultCode)
		{
		case 'e':
		case 'i':
			function->Invoke(0, (const FunctionArgument*)args.data, &intResult);
			lua_pushnumber(L, (float)intResult);
			pushed = 1;
			break;
		case 'f':
			function->Invoke(0, (const FunctionArgument*)args.data, &floatResult);
			lua_pushnumber(L, floatResult);
			pushed = 1;
			break;
		case 's':
			function->Invoke(0, (const FunctionArgument*)args.data, &stringResult);
			lua_pushstring(L, stringResult);
			pushed = 1;
			break;
		case 'v':
			function->Invoke(0, (const FunctionArgument*)args.data, 0);
			break;
		case 'b':
			function->Invoke(0, (const FunctionArgument*)args.data, &boolResult);
			lua_pushboolean(L, boolResult != false);
			pushed = 1;
			break;
		case 'V':
			function->Invoke(0, (const FunctionArgument*)args.data, &vectorResult);
			LuaPushVector(L, vectorResult);
			pushed = 1;
			break;
		case 'n':
			function->Invoke(0, (const FunctionArgument*)args.data, &nameResult);
			LuaPushName(L, nameResult);
			pushed = 1;
			break;
		case 'h':
			function->Invoke(0, (const FunctionArgument*)args.data, &handleResult);
			lua_pushlightuserdata(L, (void*)handleResult);
			pushed = 1;
			break;
		}
		if (manager->hasError)
		{
			manager->hasError = false;
			lua_pushcclosure(L, LuaErrorHandler, 0);
			lua_pushstring(L, manager->errorText);
			lua_call(L, 1, 0);
		}
		return pushed;
	}

	// FUNCTION: ENGINE 0x10801D10
	void LuaScriptManager::BindFunction(const char* name, Function* function, lua_State* L)
	{
		lua_pushstring(L, name);
		lua_pushlightuserdata(L, function);
		lua_pushcclosure(L, LuaDispatch, 1);
		lua_rawset(L, LUA_GLOBALSINDEX);
	}

	// FUNCTION: ENGINE 0x10801D50
	void LuaScriptManager::AddFunction(const char* name, Function* function)
	{
		function->SetName(name);
		function->owner = owner;
		functions.Add(function);
		BindFunction(name, function, state);
	}

	// FUNCTION: ENGINE 0x10801D90
	void LuaScriptManager::CloseScriptState()
	{
		CountReferences();
		CloseState(&state);
		currentState = 0;
	}

	// FUNCTION: ENGINE 0x10801DB0
	void LuaScriptManager::BindFunctions()
	{
		for (int i = 0; i < functions.count; i++)
		{
			BindFunction(functions.entries[i]->name, functions.entries[i], state);
		}
		for (int i = 0; i < cfunctions.count; i++)
		{
			BindCFunction(cfunctions.entries[i]);
		}
	}

	// FUNCTION: ENGINE 0x10801E00
	// EQUIVALENT: the entries are addressed [offset + base] where the compiler writes [base + offset]
	void LuaScriptManager::RestoreEnums()
	{
		int count = enumValues.end - enumValues.begin;
		for (int i = 0; i < count; i++)
		{
			lua_getfield(state, LUA_GLOBALSINDEX, (i + enumValues.begin)->table);
			if (lua_type(state, -1) != LUA_TTABLE)
			{
				CreateEnum((i + enumValues.begin)->table);
			}
			lua_settop(state, -2);
			SetTableInteger((i + enumValues.begin)->table, (i + enumValues.begin)->key, (i + enumValues.begin)->value);
		}
	}

	// FUNCTION: ENGINE 0x10801E90
	void LuaScriptManager::Shutdown()
	{
		if (open)
		{
			CloseScriptState();
			open = false;
		}
	}

	// FUNCTION: ENGINE 0x10801EB0
	bool LuaScriptManager::IsVariableDefined(const char* name)
	{
		return IsGlobalDefined(state, name);
	}

	// FUNCTION: ENGINE 0x10801ED0
	// Loads and runs a chunk in L; the Lua status (the stack is cleaned up on an error)
	int LuaScriptManager::DoLuaBuffer(lua_State* L, const char* buffer, int length, const char* chunkName)
	{
		int top = lua_gettop(state);
		if (length == -1)
		{
			length = strlen(buffer);
		}
		if (chunkName == 0)
		{
			chunkName = "=LuaScriptManager::DoLuaBuffer";
		}
		int status = luaL_loadbuffer(L, buffer, length, chunkName);
		if (status == 0)
		{
			status = ProtectedCall(L, 0, -1);
		}
		if (status != 0)
		{
			lua_settop(L, top);
		}
		return status;
	}

	// FUNCTION: ENGINE 0x10801F50
	int LuaScriptManager::MakeReference()
	{
		return LuaRef(state);
	}

	// FUNCTION: ENGINE 0x10801F60
	bool LuaScriptManager::ReleaseReference(int reference)
	{
		return LuaUnref(state, reference);
	}

	// FUNCTION: ENGINE 0x10801F80
	// EQUIVALENT: the engine places the failure exit before the code that creates the table
	bool LuaScriptManager::OpenTable(const char* name, bool global, bool create)
	{
		int index = -2;
		if (global)
		{
			index = LUA_GLOBALSINDEX;
		}
		int top = lua_gettop(state);
		lua_pushstring(state, name);
		lua_rawget(state, index);
		if (lua_type(state, -1) != LUA_TTABLE)
		{
			if (create)
			{
				lua_settop(state, -2);
				CreateTable(name, global);
				lua_pushstring(state, name);
				lua_rawget(state, index);
				if (lua_type(state, -1) == LUA_TTABLE)
				{
					return true;
				}
			}
			lua_settop(state, top);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10802040
	// The string / number / ... under key in the table on top (the value is popped)
	bool LuaGetStringField(lua_State* L, const char* key, char* buffer, int size)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		return LuaToString(L, buffer, size, true);
	}

	// FUNCTION: ENGINE 0x10802070
	bool LuaGetStringField(lua_State* L, int key, char* buffer, int size)
	{
		lua_pushinteger(L, key);
		lua_rawget(L, -2);
		return LuaToString(L, buffer, size, true);
	}

	// FUNCTION: ENGINE 0x108020A0
	bool LuaGetFloatField(lua_State* L, const char* key, float* value)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		return LuaToFloat(L, value);
	}

	// FUNCTION: ENGINE 0x108020D0
	// EQUIVALENT: the engine converts into ecx and keeps the destination in edx
	// An integer stored as a number, rounded
	void LuaGetIntField(lua_State* L, const char* key, int* value)
	{
		float number = 0.0f;
		if (LuaGetFloatField(L, key, &number))
		{
			*value = (int)(number + 0.5f);
		}
	}

	// FUNCTION: ENGINE 0x10802110
	bool LuaGetBoolField(lua_State* L, const char* key, bool* value)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		return LuaToBool(L, value);
	}

	// FUNCTION: ENGINE 0x10802140
	bool LuaGetHandleField(lua_State* L, const char* key, GameObjectHandle* value)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		bool found = LuaGetHandle(L, value);
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x10802180
	bool LuaGetVectorField(lua_State* L, const char* key, math::Vector* value)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		bool found = LuaGetVector(L, value);
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x108021C0
	bool LuaGetFunctionField(lua_State* L, const char* key, int* reference)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		return LuaToFunctionRef(L, reference);
	}

	// FUNCTION: ENGINE 0x108021F0
	bool LuaScriptManager::OpenEvent()
	{
		int top = lua_gettop(state);
		OpenContext();
		lua_pushlstring(state, "event", 5);
		lua_rawget(state, -2);
		if (lua_type(state, -1) != LUA_TTABLE)
		{
			lua_settop(state, top);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10802250
	// Empties the event table
	bool LuaScriptManager::ClearEvent()
	{
		if (OpenEvent())
		{
			lua_pushnil(state);
			while (lua_next(state, -2) != 0)
			{
				lua_settop(state, -2);
				lua_pushvalue(state, -1);
				lua_pushnil(state);
				lua_rawset(state, -4);
			}
			Close();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108022D0
	// Fills the context for a collision event
	bool LuaScriptManager::SetCollisionEvent(const char* actor, const math::Vector* pushbackVelocity,
		const char* sourceMotionNode)
	{
		OpenContext();
		SetString("actor", actor);
		if (pushbackVelocity != 0)
		{
			OpenTable("collision", false, true);
			if (sourceMotionNode != 0)
			{
				SetString("sourceMotionNode", sourceMotionNode);
			}
			SetVector("pushbackVelocity", *pushbackVelocity);
			Pop(1);
		}
		CloseContext();
		return true;
	}

	// FUNCTION: ENGINE 0x10802350
	// actors[actor].command[command] of the globals, null when a table is missing
	const char* LuaScriptManager::GetActorCommand(const char* actor, const char* command)
	{
		const char* result = 0;
		if (OpenTable("actors", true, true))
		{
			if (OpenTable(actor, false, true))
			{
				if (OpenTable("command", false, true))
				{
					lua_pushstring(state, command);
					lua_rawget(state, -2);
					result = lua_tolstring(state, -1, 0);
				}
			}
		}
		lua_settop(state, 0);
		return result;
	}

	// FUNCTION: ENGINE 0x108023D0
	bool LuaScriptManager::IsScheduleFull()
	{
		return scheduled.end == scheduled.capacity;
	}

	// FUNCTION: ENGINE 0x108023F0
	// Whether the persistent calls hold a call with the id of call (only persistent calls are looked up)
	bool LuaScriptManager::IsPersistent(const ScheduledCall* call)
	{
		if (call->persistent)
		{
			unsigned int count = persistent.Size();
			for (unsigned int i = 0; i < count; i++)
			{
				if (persistent[i].id == call->id)
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10802450
	bool LuaGetName(lua_State* L, core::Name<core::CaseSensitiveKey>* value)
	{
		if (value != 0)
		{
			if (lua_gettop(L) != 0 && LuaIsUid(L, -1))
			{
				*value = *LuaToName(L, -1);
				return true;
			}
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108024A0
	void LuaScriptManager::SetContext(core::IRefCount* newContext)
	{
		AssignRefCounted(&context, newContext);
	}

	// FUNCTION: ENGINE 0x108024C0
	// The name of the string or UID argument at index
	void LuaGetNameArgument(lua_State* L, int index, core::Name<core::CaseSensitiveKey>* name)
	{
		int type = lua_type(L, index);
		if (type == LUA_TSTRING)
		{
			core::Name<core::CaseSensitiveKey> text(lua_tolstring(L, index, 0), 1);
			*name = text;
		}
		else if (type == LUA_TUSERDATA)
		{
			*name = *LuaToName(L, index);
		}
		else
		{
			name->SetText(0);
			luaL_argerror(L, index, "expected a string or UID");
		}
	}

	// FUNCTION: ENGINE 0x10802550
	// Turns the function on top into a coroutine and keeps it as a reference
	int LuaScriptManager::CreateCoroutine()
	{
		lua_State* thread = lua_newthread(state);
		lua_insert(state, -2);
		lua_xmove(state, thread, 1);
		return MakeReference();
	}

	// FUNCTION: ENGINE 0x10802590
	bool LuaScriptManager::ResumeCoroutine(int reference, bool* failed)
	{
		PushReference(reference);
		lua_State* thread = lua_tothread(state, -1);
		GetThreadStatus((int)state);
		lua_State* previous = currentState;
		currentState = thread;
		int status = lua_resume(thread, 0);
		currentState = previous;
		lua_settop(thread, 0);
		lua_settop(state, -2);
		bool yielded = status == 1;
		if (status != 0)
		{
			if (!yielded)
			{
				*failed = true;
				ReleaseReference(reference);
				return false;
			}
		}
		else if (!yielded)
		{
			ReleaseReference(reference);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10802A70
	// Moves value up the schedule heap from hole to where it belongs (the ordering object is not used)
	void SiftUp(ScheduledCall* first, unsigned int hole, const ScheduledCall* value, ScheduleOrder order)
	{
		while (hole != 0)
		{
			unsigned int parent = (hole - 1) >> 1;
			if (value->IsLater(first[parent]))
			{
				break;
			}
			first[hole] = first[parent];
			hole = parent;
		}
		first[hole] = *value;
	}

	// FUNCTION: ENGINE 0x10802AF0
	// Takes the element at hole out of the heap of count elements: the hole sinks to a leaf, the last element is
	// put there and moves up
	void SiftDown(ScheduledCall* first, unsigned int count, unsigned int hole, ScheduleOrder order)
	{
		if (count == 1)
		{
			return;
		}
		while (hole < (count >> 1))
		{
			unsigned int left = hole * 2 + 1;
			unsigned int right = hole * 2 + 2;
			if (right < count && first[left].IsLater(first[right]))
			{
				first[hole] = first[right];
				hole = right;
			}
			else
			{
				first[hole] = first[left];
				hole = left;
			}
		}
		unsigned int last = count - 1;
		if (hole != last)
		{
			while (hole != 0)
			{
				unsigned int parent = (hole - 1) >> 1;
				if (!first[parent].IsLater(first[last]))
				{
					break;
				}
				first[hole] = first[parent];
				hole = parent;
			}
			first[hole] = first[last];
		}
	}

	// FUNCTION: ENGINE 0x10802C40
	void SiftDown(ScheduledCall* first, unsigned int count, ScheduleOrder order)
	{
		SiftDown(first, count, 0, order);
	}

	// FUNCTION: ENGINE 0x10802C60
	// tostring: the __tostring metamethod, else the value as text (game object handles by their pointer)
	int LuaToStringFunction(lua_State* L)
	{
		luaL_checkany(L, 1);
		if (luaL_callmeta(L, 1, "__tostring") == 0)
		{
			switch (lua_type(L, 1))
			{
			case LUA_TNUMBER:
				lua_pushstring(L, lua_tolstring(L, 1, 0));
				return 1;
			case LUA_TSTRING:
				lua_pushvalue(L, 1);
				return 1;
			case LUA_TBOOLEAN:
				lua_pushstring(L, lua_toboolean(L, 1) != 0 ? "true" : "false");
				return 1;
			case LUA_TNIL:
				lua_pushlstring(L, "nil", 3);
				return 1;
			case LUA_TLIGHTUSERDATA:
				{
					SerializedHandle saved;
					saved.value = (unsigned int)lua_touserdata(L, 1);
					GameObjectHandle handle = DeserializeHandle(saved);
					GameObject* object = GameObjectHandleGet(&handle);
					if (object != 0)
					{
						lua_pushfstring(L, "<GOH:?Name?,0x%p>", object);
						return 1;
					}
					lua_pushlstring(L, "<GOH:*INVALID*>", 15);
					return 1;
				}
			default:
				lua_pushfstring(L, "<%s:0x%p>", lua_typename(L, lua_type(L, 1)), lua_topointer(L, 1));
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10802DB0
	void LuaScriptManager::RegisterCFunction(const char* name, int (*function)(lua_State*))
	{
		LuaCFunction* entry = new LuaCFunction(name, function, false, 0);
		entry->owner = owner;
		cfunctions.Add(entry);
		BindCFunction(entry);
	}

	// FUNCTION: ENGINE 0x10802E00
	void LuaScriptManager::RegisterCFunction(const char* name, int (*function)(lua_State*, void*), void* upvalue)
	{
		LuaCFunction* entry = new LuaCFunction(name, (int (*)(lua_State*))function, true, upvalue);
		entry->owner = owner;
		cfunctions.Add(entry);
		BindCFunction(entry);
	}

	// FUNCTION: ENGINE 0x10802E50
	// Writes the script state (the globals without functions, the metatables) with the writer, keeping the values
	// that are on the stack in references meanwhile
	void LuaScriptManager::SaveState(lua_State* L, int stream, int reference, int unused, int flags)
	{
		int references[32];
		lua_gettop(L);
		int count = 0;
		while (lua_gettop(L) > 0)
		{
			references[count++] = MakeReference();
		}
		PushMetatables(L, true);
		CopyPlainData(L, reference, unused);
		LuaSerialize(L, stream, flags);
		lua_settop(L, -3);
		for (int i = 0; i < count; i++)
		{
			PushReference(references[i]);
			ReleaseReference(references[i]);
		}
	}

	// FUNCTION: ENGINE 0x10802F10
	// Reads a state written by SaveState back
	void LuaScriptManager::LoadState(lua_State* L, int stream, int reference, int flags)
	{
		int references[32];
		int count = 0;
		while (lua_gettop(L) > 0)
		{
			references[count++] = MakeReference();
		}
		PushMetatables(L, false);
		LuaDeserialize(L, stream, flags);
		RestorePlainData(L, reference);
		for (int i = 0; i < count; i++)
		{
			PushReference(references[i]);
			ReleaseReference(references[i]);
		}
	}

	// FUNCTION: ENGINE 0x10802FB0
	// EQUIVALENT: the engine shares the formatting calls of the cases that print one value
	// Describes the entries of the table at index (nested tables as far as depth goes; each table once). The text is
	// built and dropped in this build.
	void LuaDumpTable(lua_State* L, int index, bool showFunctions, int depth, container::ArrayDynamicHeap<void*>* visited)
	{
		lua_pushnil(L);
		while (lua_next(L, index) != 0)
		{
			char line[0x400];
			line[0] = 0;
			if (depth > 0)
			{
				for (int level = depth - 1; level > 0; level--)
				{
					core::StrNCat(line, "  ", 0x400u);
				}
				core::StrNCat(line, "|- ", 0x400u);
			}
			const char* key = "???";
			if (lua_type(L, -2) == LUA_TSTRING)
			{
				key = lua_tolstring(L, -2, 0);
			}
			switch (lua_type(L, -1))
			{
			case LUA_TNIL:
				core::SNPrintf(line, 0x400, "%s%s=NIL\n", line, key);
				break;
			case LUA_TBOOLEAN:
				core::SNPrintf(line, 0x400, "%s%s=%s\n", line, key, lua_toboolean(L, -1) != 0 ? "true" : "false");
				break;
			case LUA_TLIGHTUSERDATA:
				core::SNPrintf(line, 0x400, "%s%s=(%p)\n", line, key, lua_touserdata(L, -1));
				break;
			case LUA_TNUMBER:
				core::SNPrintf(line, 0x400, "%s%s=%f\n", line, key, (double)lua_tonumber(L, -1));
				break;
			case LUA_TSTRING:
				core::SNPrintf(line, 0x400, "%s%s=\"%s\"\n", line, key, lua_tolstring(L, -1, 0));
				break;
			case LUA_TTABLE:
				{
					const void* table = lua_topointer(L, -1);
					bool seen = false;
					for (int i = 0; i < (int)visited->Size(); i++)
					{
						if (table == (*visited)[i])
						{
							core::SNPrintf(line, 0x400, "%s%s DUP (%p)\n", line, key, table);
							seen = true;
							break;
						}
					}
					if (!seen)
					{
						core::SNPrintf(line, 0x400, "%s%s (%p)\n", line, key, table);
						visited->PushBack((void*)table);
						LuaDumpTable(L, lua_gettop(L), showFunctions, depth + 1, visited);
					}
				}
				break;
			case LUA_TFUNCTION:
				if (showFunctions || lua_iscfunction(L, -1) == 0)
				{
					core::SNPrintf(line, 0x400, "%s%s=<%s function>\n", line, key,
						lua_iscfunction(L, -1) != 0 ? "C" : "Lua");
				}
				break;
			case LUA_TUSERDATA:
				core::SNPrintf(line, 0x400, "%s%s=[%p]\n", line, key, lua_touserdata(L, -1));
				break;
			case LUA_TTHREAD:
				core::SNPrintf(line, 0x400, "%s%s=<thread>\n", line, key);
				break;
			default:
				core::SNPrintf(line, 0x400, "%s%s=UNKNOWN\n", line, key);
			}
			lua_settop(L, -2);
		}
	}

	// FUNCTION: ENGINE 0x10803300
	LuaScriptManager::ScriptResult LuaScriptManager::DoBuffer(const char* buffer, const char* chunkName, int length)
	{
		return (ScriptResult)GetErrorLevel(DoLuaBuffer(state, buffer, length, chunkName));
	}

	// FUNCTION: ENGINE 0x10803330
	// EQUIVALENT: the engine passes the path through a stack slot it fills after pushing and saves two more registers
	LuaScriptManager::ScriptResult LuaScriptManager::DoFile(const char* path, int unused)
	{
		core::IFile* file;
		core::FileSystemOpenFileAsync(&file, path, false, 0, 1, 0, 1, 1, 0);
		file->Wait();
		if (!file->IsOpen())
		{
			file->Release();
			return SCRIPT_MISSING;
		}
		unsigned int size = file->GetCurrentSize();
		if (size == 0)
		{
			file->Release();
			return SCRIPT_OK;
		}
		char* buffer = new char[size + 1];
		file->Read(buffer, size, 1);
		file->Wait();
		buffer[size] = 0;
		file->Release();
		char chunkName[0x100];
		core::SNPrintf(chunkName, 0x100, "@%s", path);
		int status = DoLuaBuffer(state, buffer, size, chunkName);
		CollectGarbage(true);
		delete[] buffer;
		return (ScriptResult)GetErrorLevel(status);
	}

	// FUNCTION: ENGINE 0x10803450
	// Runs the remembered script files again
	void LuaScriptManager::RunScripts()
	{
		int count = scripts.Size();
		for (int i = 0; i < count; i++)
		{
			DoFile(scripts[i], 0);
		}
	}

	// FUNCTION: ENGINE 0x10803480
	bool LuaGetNameField(lua_State* L, const char* key, core::Name<core::CaseSensitiveKey>* value)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		bool found = LuaGetName(L, value);
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x108034C0
	// The game object of the handle argument at index
	GameObject* LuaToGameObject(lua_State* L, int index)
	{
		if (lua_type(L, index) != LUA_TLIGHTUSERDATA)
		{
			luaL_argerror(L, index, "expected a GameObjectHandle");
		}
		SerializedHandle saved;
		saved.value = (unsigned int)lua_touserdata(L, index);
		GameObject* object = DeserializeHandle(saved).Get();
		if (object == 0)
		{
			luaL_argerror(L, index, "invalid GameObjectHandle");
		}
		return object;
	}

	// FUNCTION: ENGINE 0x10803540
	int LuaScriptManager::LoadCoroutine(const char* buffer, int length, const char* name)
	{
		if (name == 0)
		{
			name = "anon_coroutine";
		}
		luaL_loadbuffer(state, buffer, length, name);
		return CreateCoroutine();
	}

	// FUNCTION: ENGINE 0x10803580
	int LuaScriptManager::CreateCoroutineFromReference(int reference)
	{
		PushReference(reference);
		return CreateCoroutine();
	}

	// FUNCTION: ENGINE 0x10803800
	// The global functions of the scripts: the error function, print, tostring, type and the debugging helpers
	void LuaScriptManager::RegisterBaseFunctions(lua_State* L)
	{
		lua_pushcclosure(L, LuaErrorHandler, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "_TRACEBACK");
		lua_pushcclosure(L, LuaGlobalPrint, 0);
		lua_pushvalue(L, -1);
		lua_setfield(L, LUA_GLOBALSINDEX, "debug");
		lua_setfield(L, LUA_GLOBALSINDEX, "print");
		lua_pushcclosure(L, LuaChannelPrint, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "cdebug");
		lua_pushcclosure(L, LuaToStringFunction, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "tostring");
		lua_pushcclosure(L, LuaType, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "type");
		lua_pushcclosure(L, LuaCheckError, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "checkError");
		lua_pushcclosure(L, LuaBreakpoint, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "breakpoint");
		lua_pushcclosure(L, LuaTraceback, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "getStackTrace");
		lua_pushboolean(L, 0);
		lua_setfield(L, LUA_GLOBALSINDEX, "_BREAK");
	}

	// FUNCTION: ENGINE 0x10803930
	LuaScriptManager::ScriptResult LuaScriptManager::ProcessFile(const char* path, int unused)
	{
		ScriptResult result = DoFile(path, unused);
		if (result != SCRIPT_MISSING && !reloaded)
		{
			if (!scripts.IsFull())
			{
				scripts.PushBack(path);
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10803970
	LuaScriptManager::ScriptResult LuaScriptManager::ProcessFile(const char* path)
	{
		return ProcessFile(path, 0);
	}

	// FUNCTION: ENGINE 0x10803980
	// Creates the state at *target (closing the one it holds): the standard libraries, the Vector and UID types
	// and the base functions
	void LuaScriptManager::CreateState(lua_State** target)
	{
		if (*target != 0)
		{
			CloseState(target);
		}
		*target = lua_newstate(ScriptRealloc, 0);
		lua_pushcclosure(*target, luaopen_base, 0);
		ProtectedCall(*target, 0, 0);
		lua_pushcclosure(*target, luaopen_string, 0);
		ProtectedCall(*target, 0, 0);
		lua_pushcclosure(*target, luaopen_math, 0);
		ProtectedCall(*target, 0, 0);
		lua_pushcclosure(*target, luaopen_table, 0);
		ProtectedCall(*target, 0, 0);
		lua_pushcclosure(*target, luaopen_debug, 0);
		ProtectedCall(*target, 0, 0);
		LuaOpenVector(*target);
		LuaOpenUid(*target);
		LuaOpenGame(*target);
		RegisterBaseFunctions(*target);
		InitContextTables(*target);
	}

	// The channel of the Lua environment query (0x11284A58)
	extern MessageListeners gLuaEnvironmentListeners;

	// FUNCTION: ENGINE 0x10803A60
	// EQUIVALENT: the engine keeps the iterator's handle in a register and copies the end iterator each round; ours
	// keeps the iterator in memory
	bool LuaScriptManager::FindFunctionSource(const char* functionName, char* sourceBuffer, unsigned int bufferSize,
		int* line)
	{
		MessageListenerRef ref = GetListeners(&gLuaEnvironmentListeners);
		MessageListenerList* list = ref.list;
		for (HandleIterator it = list != 0 ? list->Begin() : HandleIterator();
			it != (list != 0 ? list->End() : HandleIterator()); ++it)
		{
			GetLuaEnvironmentMessage message;
			GetGameObjectEntries()[it->index].object->PostMessage(&message);
			if (PushReference(message.reference))
			{
				if (lua_type(state, -1) == LUA_TTABLE)
				{
					lua_pushstring(state, functionName);
					lua_rawget(state, -2);
					if (lua_type(state, -1) == LUA_TFUNCTION)
					{
						lua_Debug ar;
						lua_getinfo(state, ">S", &ar);
						if (sourceBuffer != 0)
						{
							const char* source = ar.source;
							if (*source == '=' || *source == '@')
							{
								source++;
							}
							core::StrNCpy(sourceBuffer, source, bufferSize);
						}
						*line = ar.linedefined;
						lua_settop(state, -2);
						return true;
					}
					lua_settop(state, -2);
				}
				lua_settop(state, -2);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10803C20
	// Releases the references of the persistent calls that are not in the schedule any more, and forgets them
	void LuaScriptManager::ReleasePersistent()
	{
		for (unsigned int i = 0; i < persistent.Size(); i++)
		{
			ScheduledCall call = persistent[i];
			bool scheduledToo = false;
			for (unsigned int j = 0; j < scheduled.Size(); j++)
			{
				if (scheduled[j].id == call.id)
				{
					scheduledToo = true;
					break;
				}
			}
			if (!scheduledToo)
			{
				luaL_unref(state, LUA_REGISTRYINDEX, call.reference);
			}
		}
		persistent.Clear();
	}

	// FUNCTION: ENGINE 0x10803D40
	void LuaScriptManager::RunInitScript()
	{
		ProcessFile("init.lua", 0);
	}

	// FUNCTION: ENGINE 0x10803EA0
	// EQUIVALENT: register choice around the array's allocation and release
	// Describes the entries of the table at index
	void LuaDumpTables(lua_State* L, int index, bool showFunctions, int depth)
	{
		container::ArrayDynamicHeap<void*> visited;
		visited.Allocate(0x1000);
		visited.PushBack((void*)lua_topointer(L, index));
		LuaDumpTable(L, index, showFunctions, depth, &visited);
	}

	// FUNCTION: ENGINE 0x10803F60
	void LuaScriptManager::OpenState()
	{
		CreateState(&state);
		currentState = state;
		lua_pushlstring(state, "RAD_WIN32", 9);
		lua_pushboolean(state, 1);
		lua_rawset(state, LUA_GLOBALSINDEX);
		lua_pushlstring(state, "RAD_RELEASE", 11);
		lua_pushboolean(state, 1);
		lua_rawset(state, LUA_GLOBALSINDEX);
	}

	// FUNCTION: ENGINE 0x10803FD0
	void LuaScriptManager::Restart()
	{
		if (!open)
		{
			open = true;
			OpenState();
			BindFunctions();
			RestoreEnums();
			RunScripts();
		}
	}

	// FUNCTION: ENGINE 0x10804000
	void LuaScriptManager::Reload()
	{
		Shutdown();
		Restart();
		NextGeneration();
		reloaded = true;
	}

	// FUNCTION: ENGINE 0x10804020
	// Copies the persistent scheduled calls, their times relative to now
	void LuaScriptManager::SavePersistent()
	{
		ReleasePersistent();
		for (unsigned int i = 0; i < scheduled.Size(); i++)
		{
			if (scheduled[i].persistent)
			{
				ScheduledCall call = scheduled[i];
				call.time = call.time - time.seconds;
				persistent.PushBack(call);
			}
		}
	}

	// FUNCTION: ENGINE 0x10804110
	inline void PushHeap(ScheduleArray* array, const ScheduledCall* value, ScheduleOrder order)
	{
		int size = array->Size();
		ScheduledCall blank;
		array->Resize(size + 1, blank);
		SiftUp(array->begin, size, value, order);
	}

	// FUNCTION: ENGINE 0x10804170
	inline void PopHeap(ScheduleArray* array, unsigned int hole, ScheduleOrder order)
	{
		int size = array->Size();
		SiftDown(array->begin, size, hole, order);
		ScheduledCall blank;
		array->Resize(size - 1, blank);
	}

	// FUNCTION: ENGINE 0x108041D0
	inline void PopHeap(ScheduleArray* array, ScheduleOrder order)
	{
		int size = array->Size();
		SiftDown(array->begin, size, 0, order);
		ScheduledCall blank;
		array->Resize(size - 1, blank);
	}

	// FUNCTION: ENGINE 0x108047E0
	void SchedulePush(ScheduleArray* array, const ScheduledCall* value)
	{
		ScheduleOrder order;
		PushHeap(array, value, order);
	}

	// FUNCTION: ENGINE 0x10804800
	void ScheduleRemove(ScheduleArray* array, unsigned int hole)
	{
		ScheduleOrder order;
		PopHeap(array, hole, order);
	}

	// FUNCTION: ENGINE 0x10804820
	void ScheduleRemoveFirst(ScheduleArray* array)
	{
		ScheduleOrder order;
		PopHeap(array, order);
	}

}

template class Function0<const char*>;
template class Function1<void, const char*>;
template class Function1<const char*, const char*>;
template class Method1<engine::LuaScriptManager, engine::LuaScriptManager::ScriptResult, const char*>;
template class Method1<engine::LuaScriptManager, bool, const char*>;
template class Closure1<engine::LuaScriptManager, engine::LuaScriptManager::ScriptResult, const char*>;
template class Closure1<engine::LuaScriptManager, bool, const char*>;
template void engine::LuaScriptManager::Register<const char*>(const char*, const char* (*)());
template void engine::LuaScriptManager::RegisterMethod<engine::LuaScriptManager, engine::LuaScriptManager::ScriptResult,
	const char*>(const char*, engine::LuaScriptManager*, engine::LuaScriptManager::ScriptResult
	(engine::LuaScriptManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::LuaScriptManager, bool, const char*>(const char*,
	engine::LuaScriptManager*, bool (engine::LuaScriptManager::*)(const char*));

namespace engine
{
	// FUNCTION: ENGINE 0x10804230
	// EQUIVALENT: the engine delays the third store of the unused array's initialisation behind the first allocation
	LuaScriptManager::LuaScriptManager(const ScriptManagerConfig& config)
		: unknown4(0), unknown8(0), state(0), currentState(0), functions(config.functionCapacity),
		cfunctions(config.cfunctionCapacity), reloaded(false), context(0), open(true), generation(0), walkDepth(-1),
		owner(0), scheduled(config.scheduleCapacity), nextScheduleId(1), time(0, 0), persistent(8),
		unknownB4(config.unknownB4), hasError(false), unknownB6(false)
	{
		enumValues.Create(0x100);
		scripts.Create(8);
		unknown58 = 0;
		errorText[0] = 0;
		memset(walkTops, 0xff, sizeof(walkTops));
		OpenState();
		AddFunction("sh_ProcessFile", new Closure1<LuaScriptManager, ScriptResult, const char*>("sh_ProcessFile", this,
			(ScriptResult (LuaScriptManager::*)(const char*))&LuaScriptManager::ProcessFile, ClosureInPlace()));
		AddFunction("debug_EnableChannel", new Function1<void, const char*>("debug_EnableChannel", DebugEnableChannel));
		AddFunction("debug_DisableChannel",
			new Function1<void, const char*>("debug_DisableChannel", DebugDisableChannel));
		AddFunction("dbg_AddWatch",
			new Closure1<LuaScriptManager, bool, const char*>("dbg_AddWatch", this, &LuaScriptManager::AddWatch,
				ClosureInPlace()));
		AddFunction("dbg_DeleteWatch",
			new Closure1<LuaScriptManager, bool, const char*>("dbg_DeleteWatch", this, &LuaScriptManager::DeleteWatch,
				ClosureInPlace()));
		AddFunction("dbg_IsVariableDefined", new Closure1<LuaScriptManager, bool, const char*>("dbg_IsVariableDefined",
			this, &LuaScriptManager::IsVariableDefined, ClosureInPlace()));
		AddFunction("StartCommandCompletion",
			new Function1<const char*, const char*>("StartCommandCompletion", StartCommandCompletion));
		AddFunction("NextCommandCompletion", new Function0<const char*>("NextCommandCompletion", NextCommandCompletion));
	}

	// FUNCTION: ENGINE 0x10804690
	LuaScriptManager::~LuaScriptManager()
	{
		unknown4 = 0;
		RemoveFunction("sh_ProcessFile");
		RemoveFunction("debug_EnableChannel");
		RemoveFunction("debug_DisableChannel");
		RemoveFunction("dbg_AddWatch");
		RemoveFunction("dbg_DeleteWatch");
		RemoveFunction("dbg_IsVariableDefined");
		CloseScriptState();
		for (int i = 0; i < functions.count; i++)
		{
			delete functions.entries[i];
		}
		functions.count = 0;
		for (int i = 0; i < cfunctions.count; i++)
		{
			delete cfunctions.entries[i];
		}
		cfunctions.count = 0;
		enumValues.Clear();
		scripts.Clear();
	}

	// FUNCTION: ENGINE 0x10804840
	void CreateScriptManager(const ScriptManagerConfig& config)
	{
		core::HeapScope scope(0x7a);
		gScriptBlockPool = new ScriptBlockPool;
		gScriptManager = new LuaScriptManager(config);
	}

	// FUNCTION: ENGINE 0x108048E0
	// EQUIVALENT: the engine spills the clock after storing the next id, the compiler before
	int LuaScriptManager::Schedule(float delay, int reference, bool persistent, GameObjectHandle owner)
	{
		if (IsScheduleFull())
		{
			return 0;
		}
		float now = time.seconds;
		int id = nextScheduleId;
		nextScheduleId = id + 1;
		ScheduledCall call;
		call.time = now + delay;
		call.id = id;
		call.reference = reference;
		call.owner = owner;
		call.hasOwner = owner.Get() != 0;
		call.persistent = persistent;
		ScheduleOrder order;
		PushHeap(&scheduled, &call, order);
		return id;
	}

	// FUNCTION: ENGINE 0x108049A0
	bool LuaScriptManager::CancelScheduled(int id)
	{
		unsigned int count = scheduled.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			if (scheduled[i].id == id)
			{
				if (!IsPersistent(&scheduled[i]))
				{
					luaL_unref(state, LUA_REGISTRYINDEX, scheduled[i].reference);
				}
				ScheduleOrder order;
				PopHeap(&scheduled, i, order);
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10804A70
	// Removes the scheduled calls of owner (the handles are compared as one word)
	bool LuaScriptManager::CancelScheduledFor(GameObjectHandle owner)
	{
		ScheduleArray* queue = &scheduled;
		unsigned int count = queue->Size();
		bool found = false;
		unsigned int i = 0;
		while (i < count)
		{
			if (*(unsigned int*)&(*queue)[i].owner == *(unsigned int*)&owner)
			{
				luaL_unref(state, LUA_REGISTRYINDEX, (*queue)[i].reference);
				ScheduleOrder order;
				PopHeap(queue, i, order);
				count--;
				found = true;
			}
			else
			{
				i++;
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x10804B50
	// Advances the clock and runs the scheduled calls that are due (the owner of a call must still exist)
	void LuaScriptManager::RunScheduled(core::Time elapsed)
	{
		time.Add(elapsed.milliseconds, elapsed.microseconds);
		lua_State* L = state;
		float now = time.seconds;
		while (scheduled.Size() != 0 && now > scheduled.begin[0].time)
		{
			ScheduledCall call = scheduled.begin[0];
			ScheduleOrder order;
			PopHeap(&scheduled, 0, order);
			if (!call.hasOwner || call.owner.IsValid())
			{
				lua_rawgeti(L, LUA_REGISTRYINDEX, call.reference);
				if (!IsPersistent(&call))
				{
					luaL_unref(L, LUA_REGISTRYINDEX, call.reference);
				}
				if (ProtectedCall(L, 0, 0) != 0)
				{
					lua_pushlstring(L, "Error executing scheduled function: ", 0x24);
					lua_pushvalue(L, -2);
					lua_concat(L, 2);
				}
				lua_settop(L, 0);
			}
			else
			{
				luaL_unref(L, LUA_REGISTRYINDEX, call.reference);
			}
		}
	}

	// FUNCTION: ENGINE 0x10804D10
	void LuaScriptManager::CancelAllScheduled()
	{
		while (!scheduled.IsEmpty())
		{
			CancelScheduled(scheduled.Begin()->id);
		}
		ReleasePersistent();
	}

	// FUNCTION: ENGINE 0x10804D50
	// EQUIVALENT: the engine adds the clock as the memory operand, the compiler loads it first
	// Takes the persistent calls (their times are relative to now) back into the schedule
	void LuaScriptManager::RestoreScheduled()
	{
		ScheduleArray* queue = &scheduled;
		unsigned int count = queue->Size();
		for (unsigned int i = 0; i < count; i++)
		{
			if (!IsPersistent(&(*queue)[i]))
			{
				luaL_unref(state, LUA_REGISTRYINDEX, (*queue)[i].reference);
			}
		}
		queue->end = queue->begin;
		count = persistent.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			ScheduledCall call = persistent[i];
			call.time = call.time + time.seconds;
			ScheduleOrder order;
			PushHeap(queue, &call, order);
		}
	}

	// FUNCTION: ENGINE 0x10804E80
	void LuaScriptManager::Update(core::Time elapsed)
	{
		lua_settop(state, 0);
		if (!unknownB6)
		{
			RunScheduled(elapsed);
		}
		CollectGarbage(false);
	}
}

namespace container
{
	template class ArrayDynamic<engine::ScheduledCall, AllocatorCoreStatic<0x7a, 16> >;
	template class ArrayDynamicNew<engine::LuaEnumValue>;
	template class ArrayDynamicNew<const char*>;
	template class ArrayDynamicHeap<void*>;
}

namespace engine
{
	template math::Vector* ScriptArguments::Push<math::Vector>(math::Vector);
	template core::Name<core::CaseSensitiveKey>* ScriptArguments::Push<core::Name<core::CaseSensitiveKey> >(
		core::Name<core::CaseSensitiveKey>);
	template bool* ScriptArguments::Push<bool>(bool);
	template float* ScriptArguments::Push<float>(float);
	template int* ScriptArguments::Push<int>(int);
	template void** ScriptArguments::Push<void*>(void*);
}

// Kept copies: the container, callback and registration template members this unit instantiates
// FUNCTION: ENGINE 0x10800850
// FUNCTION: ENGINE 0x108008F0
// FUNCTION: ENGINE 0x10800910
// FUNCTION: ENGINE 0x10800920
// FUNCTION: ENGINE 0x10800930
// FUNCTION: ENGINE 0x10800950
// FUNCTION: ENGINE 0x10800960
// FUNCTION: ENGINE 0x10800970
// FUNCTION: ENGINE 0x10800980
// FUNCTION: ENGINE 0x108009A0
// FUNCTION: ENGINE 0x108009B0
// FUNCTION: ENGINE 0x108009C0
// FUNCTION: ENGINE 0x108009D0
// FUNCTION: ENGINE 0x108009E0
// FUNCTION: ENGINE 0x108009F0
// FUNCTION: ENGINE 0x10800A00
// FUNCTION: ENGINE 0x10800A70
// FUNCTION: ENGINE 0x10800AC0
// FUNCTION: ENGINE 0x10800AD0
// FUNCTION: ENGINE 0x10800AE0
// FUNCTION: ENGINE 0x10800B90
// FUNCTION: ENGINE 0x10800BB0
// FUNCTION: ENGINE 0x10800BF0
// FUNCTION: ENGINE 0x10800C10
// FUNCTION: ENGINE 0x10800C30
// FUNCTION: ENGINE 0x10800C70
// FUNCTION: ENGINE 0x10800CA0
// FUNCTION: ENGINE 0x10800CC0
// FUNCTION: ENGINE 0x10800CF0
// FUNCTION: ENGINE 0x10800D60
// FUNCTION: ENGINE 0x10800DC0
// FUNCTION: ENGINE 0x10800E00
// FUNCTION: ENGINE 0x10802640
// FUNCTION: ENGINE 0x10802650
// FUNCTION: ENGINE 0x108026A0
// FUNCTION: ENGINE 0x108026B0
// FUNCTION: ENGINE 0x10802700
// FUNCTION: ENGINE 0x10802770
// FUNCTION: ENGINE 0x108027A0
// FUNCTION: ENGINE 0x108027F0
// FUNCTION: ENGINE 0x10802890
// FUNCTION: ENGINE 0x108028D0
// FUNCTION: ENGINE 0x108028E0
// FUNCTION: ENGINE 0x10802940
// FUNCTION: ENGINE 0x10802960
// FUNCTION: ENGINE 0x10802980
// FUNCTION: ENGINE 0x108029D0
// FUNCTION: ENGINE 0x108029F0
// FUNCTION: ENGINE 0x10802A10
// FUNCTION: ENGINE 0x10802A50
// FUNCTION: ENGINE 0x108035A0
// FUNCTION: ENGINE 0x108035B0
// FUNCTION: ENGINE 0x108035C0
// FUNCTION: ENGINE 0x108035E0
// FUNCTION: ENGINE 0x108035F0
// FUNCTION: ENGINE 0x10803620
// FUNCTION: ENGINE 0x10803630
// FUNCTION: ENGINE 0x108036A0
// FUNCTION: ENGINE 0x108036F0
// FUNCTION: ENGINE 0x10803710
// FUNCTION: ENGINE 0x10803760
// FUNCTION: ENGINE 0x10803780
// FUNCTION: ENGINE 0x10803D50
// FUNCTION: ENGINE 0x10803D70
// FUNCTION: ENGINE 0x10803D90
// FUNCTION: ENGINE 0x10803DB0
// FUNCTION: ENGINE 0x10803DD0
// FUNCTION: ENGINE 0x10803E20
// FUNCTION: ENGINE 0x10803E70
// FUNCTION: ENGINE 0x108048C0
