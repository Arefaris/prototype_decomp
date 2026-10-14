// engine::LuaScriptManager (RTTI name; 1 vftable slot, the deleting destructor; the singleton is 0x11284254, the unit
// 0x107FE510 - 0x10804EC0; member names guessed): the engine's Lua state (at +0xC) and the native functions units
// register with it. A unit registers
// its functions between SetOwner and ClearOwner under the address of one of its statics, and Unregister takes
// everything registered under that address away again.
#ifndef ENGINE_LUASCRIPTMANAGER_H
#define ENGINE_LUASCRIPTMANAGER_H

#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/engine/system/enginememory.h"
#include <string.h>

struct lua_State;

namespace engine
{
	struct SerializedHandle;
	class Function;
	class GameObjectHandle;
	class LuaScriptManager;

	// A destination string for LuaGetString
	struct LuaStringBuffer
	{
		char* buffer;
		unsigned int capacity;
	};

	// 0x108002F0: records an error message
	void SetScriptError(LuaScriptManager* manager, const char* format, ...);

	// Two blocks of 0x14000 bytes the script allocator hands out first for requests of exactly that size (the Lua
	// state's large arrays; 0x11284250)
	struct ScriptBlockPool
	{
		void Reset()
		{
			free[0] = true;
			free[1] = true;
		}
		// A free block, or null (0x107FE6B0)
		void* Take();
		// True when block is one of the pool's (it is free again; 0x107FE6E0)
		bool Give(void* block);

		char blocks[2][0x14000];
		bool free[2];
	};

	extern ScriptBlockPool* gScriptBlockPool;

	// 0x107FE790: the Lua state's allocator (lua_Alloc)
	void* ScriptRealloc(void* user, void* block, unsigned int oldSize, unsigned int newSize);

	// A C function registered with the scripts, with an optional upvalue (0x14 bytes)
	struct LuaCFunction
	{
		LuaCFunction(const char* newName, int (*newFunction)(lua_State*), bool newHasUpvalue, void* newUpvalue)
		{
			name = newName;
			function = newFunction;
			hasUpvalue = newHasUpvalue;
			owner = 0;
			upvalue = newUpvalue;
			generation = 0;
		}

		int (*function)(lua_State*);
		void* upvalue;
		const void* owner;
		const char* name;
		bool hasUpvalue;
		unsigned char generation;
	};

	// Entries kept sorted by name, for command completion (names guessed)
	template<class T> class ScriptNameTable
	{
	public:
		explicit ScriptNameTable(unsigned int newCapacity)
		{
			capacity = newCapacity;
			count = 0;
			entries = new (0x7a) T*[newCapacity];
		}
		~ScriptNameTable()
		{
			delete[] entries;
		}
		bool Add(T* entry);
		// The next name after previous that starts with prefix (the first such name when previous is not one)
		const char* Complete(const char* prefix, const char* previous);
		bool Remove(const char* name);
		void SetGeneration(unsigned char value);
		void Unused(int unused)
		{
		}

		T** entries;
		unsigned int capacity;
		int count;
	};

	class LuaScriptManager
	{
	public:
		virtual ~LuaScriptManager();

		// 0x108021F0: pushes context.event; 0x108000B0: pops it again
		bool OpenEvent();
		bool Close();
		// The table below the top: [key] = value
		bool SetString(const char* key, const char* value);
		bool SetFloat(const char* key, float value);
		bool SetInt(const char* key, int value);
		bool SetBool(const char* key, bool value);
		bool SetVector(const char* key, math::Vector value);
		// 0x10800230 / 0x10800270: event[key] = a handle (light userdata) / a name
		bool SetHandle(const char* key, SerializedHandle handle);
		bool SetName(const char* key, const core::Name<core::CaseSensitiveKey>& name);
		bool ClearField(const char* key);
		void InitContextTables(lua_State* L);
		bool PushReference(int reference);
		int Call(int base);
		bool CreateTable(const char* name, bool global);
		void Pop(int count);
		bool BeginTableWalk();
		bool NextTableEntry(int index);
		void EndTableWalk();
		bool OpenContext();
		bool CloseContext();
		const char* GetErrorText();
		bool CallPrintingErrors(int argumentCount);
		int GetTopType();
		void PushInt(int value);
		void PushFloat(float value);
		void PushBool(bool value);
		void PushString(const char* value);
		void PushVector(math::Vector value);
		void PushHandle(GameObjectHandle handle);
		bool PushGlobalFunction(const char* name);
		int GetTop();
		void SetTop(int index);
		int GetThreadStatus(int unused);
		// Marks the registered functions with the next generation
		void NextGeneration();

		// 0x107FF850 / 0x107FF860: the owner the functions registered from now on belong to (+0x80)
		void SetOwner(const void* owner);
		void ClearOwner();
		// 0x108016C0: removes the functions and the other registrations of owner
		void Unregister(const void* owner);
		// Registers a native function under name (out of line in the units that instantiate it; <int, LuaGOH>:
		// 0x10289C10, which wraps the function in a Function1<int, LuaGOH>)
		template<class R, class A> void Register(const char* name, R (*function)(A));
		// 0x10801D50: adds the function under name
		void AddFunction(const char* name, Function* function);
		// Binds method of object under name as a closure (function.h; out of line per instantiation)
		template<class C, class R> void RegisterMethod(const char* name, C* object, R (C::*method)());
		template<class C, class R, class A1> void RegisterMethod(const char* name, C* object, R (C::*method)(A1));
		template<class C, class R, class A1, class A2> void RegisterMethod(const char* name, C* object,
			R (C::*method)(A1, A2));
		template<class C, class R, class A1, class A2, class A3> void RegisterMethod(const char* name, C* object,
			R (C::*method)(A1, A2, A3));
		template<class C, class R, class A1, class A2, class A3, class A4> void RegisterMethod(const char* name,
			C* object, R (C::*method)(A1, A2, A3, A4));

		bool RemoveCFunction(const char* name);
		bool RemoveFunction(const char* name);
		void SetTableInteger(const char* table, const char* key, int value);
		// t[name] = the global / registry value name, for the table below the top (keyAfter: the key is pushed
		// after the value)
		void CopyGlobal(lua_State* L, const char* name, bool keyAfter);
		void CopyRegistryValue(lua_State* L, const char* name, bool keyAfter);
		bool IsPlainData(lua_State* L, int visited, int unused);
		// A table of the Vector and UID metatables
		void PushMetatables(lua_State* L, bool keyAfter);
		int CountReferences();
		void CloseState(lua_State** L);
		bool AddWatch(const char* name);
		bool DeleteWatch(const char* name);
		bool GetUnknownB4() const;
		void SetUnknownB4(bool value);
		void SetUnknownB6(bool value);
		void CollectGarbage(bool full);
		const char* Complete(const char* prefix, const char* previous);
		int GetErrorLevel(int status);

		int unknown4;
		int unknown8;
		lua_State* state;
		int unknown10;
		ScriptNameTable<Function> functions;
		ScriptNameTable<LuaCFunction> cfunctions;
		unsigned char unknown2C[0x55 - 0x2C];
		unsigned char generation;
		unsigned char unknown56[0x5C - 0x56];
		// The stack tops of the nested table walks
		int walkTops[8];
		int walkDepth;
		const void* owner;
		unsigned char unknown84[0xB4 - 0x84];
		bool unknownB4;
		bool hasError;
		bool unknownB6;
		char errorText[0x100];
		unsigned char unknown1B7[0x1C8 - 0x1B7];
	};

	// The script manager (0x11284254)
	extern LuaScriptManager* gScriptManager;

	// 0x107FEFB0: the current script context, null when no script runs
	LuaScriptManager* GetScriptManager();
}

#endif
