// engine::LuaScriptManager (RTTI name; 1 vftable slot, the deleting destructor; the singleton is 0x11284254, the unit
// 0x107FE510 - 0x10804EC0; member names guessed): the engine's Lua state (at +0xC) and the native functions units
// register with it. A unit registers
// its functions between SetOwner and ClearOwner under the address of one of its statics, and Unregister takes
// everything registered under that address away again.
#ifndef ENGINE_LUASCRIPTMANAGER_H
#define ENGINE_LUASCRIPTMANAGER_H

#include "code/core/name.h"
#include "code/core/time.h"
#include "code/container/arraydynamicnew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"
#include "code/engine/system/enginememory.h"
#include <string.h>

struct lua_State;

namespace engine
{
	struct LuaGOH;
	typedef LuaGOH SerializedHandle;
	class Function;
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
		// 0x107FE6A0
		ScriptBlockPool();
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
		// 0x107FE7E0
		LuaCFunction(const char* newName, int (*newFunction)(lua_State*), bool newHasUpvalue, void* newUpvalue);
		// The same heap as Function (luascriptmanager.cpp)
		static void* operator new(unsigned int size);
		static void operator delete(void* block);

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
		explicit ScriptNameTable(unsigned int newCapacity);
		~ScriptNameTable();
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

	// What the manager is created from (EngineInitialize fills it in; names guessed)
	struct ScriptManagerConfig
	{
		int scheduleCapacity;
		bool unknownB4;
		int functionCapacity;
		int cfunctionCapacity;
	};

	// A Lua function to call later: the manager's schedule is a heap ordered by time (0x14 bytes; names guessed)
	struct ScheduledCall
	{
		// 0x107FEF70: whether this call comes after other (later time, or the same time and a later id)
		bool IsLater(const ScheduledCall& other) const;

		float time;
		unsigned int id;
		int reference;
		GameObjectHandle owner;
		bool hasOwner;
		bool persistent;
	};

	typedef container::ArrayDynamic<ScheduledCall, container::AllocatorCoreStatic<0x7a, 16> > ScheduleArray;

	// The (empty) ordering of the schedule heap (the heap helpers take it by value)
	struct ScheduleOrder
	{
		// 0x10800E40
		bool operator()(const ScheduledCall& first, const ScheduledCall& second) const;
	};

	// An enumeration value to register again when the script state is rebuilt (0xC bytes; names guessed)
	struct LuaEnumValue
	{
		const char* table;
		const char* key;
		int value;
	};

	// The arguments of a call as Function::Invoke takes them: values stored one after the other in 4-byte slots
	// (a cursor in front of a 0x40-byte buffer; the last slot of the buffer is never used). Names guessed.
	struct ScriptArguments
	{
		// The slot the value went to, null when the buffer is full (the value is dropped)
		template<class T> T* Push(T value)
		{
			if ((unsigned int)(cursor - data + sizeof(T)) >= 0x40)
			{
				return 0;
			}
			T* slot = (T*)cursor;
			Store(slot, value);
			cursor += (sizeof(T) + 3) & ~3;
			return slot;
		}
		template<class T> static void Store(T* slot, const T& value)
		{
			*slot = value;
		}
		// Vectors are copied component by component
		static void Store(math::Vector* slot, const math::Vector& value)
		{
			slot->x = value.x;
			slot->y = value.y;
			slot->z = value.z;
		}

		char* cursor;
		char data[0x40];
	};

	// A growable array of words the manager never fills (names guessed)
	struct UnusedArray
	{
		UnusedArray()
		{
			begin = 0;
			capacity = 0;
			end = 0;
		}
		~UnusedArray()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}

		int* begin;
		int* end;
		int* capacity;
	};

	class LuaScriptManager
	{
	public:
		// The result of running a script file (RTTI engine::LuaScriptManager::ScriptResult; values guessed from
		// GetErrorLevel)
		enum ScriptResult
		{
			SCRIPT_OK = 0,
			SCRIPT_MISSING = 1,
			SCRIPT_SYNTAX_ERROR = 2,
			SCRIPT_RUN_ERROR = 3
		};

		explicit LuaScriptManager(const ScriptManagerConfig& config);
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
		// 0x10801740: removes every registered function
		void UnregisterAll();
		// 0x10801550 / 0x10801630: a table of the data in the globals (or in the table of reference) that holds no
		// functions / puts such a table back
		void CopyPlainData(lua_State* L, int reference, int unused);
		void RestorePlainData(lua_State* L, int reference);
		// Registers a native function under name (out of line in the units that instantiate it; <int, LuaGOH>:
		// 0x10289C10, which wraps the function in a Function1<int, LuaGOH>)
		template<class R, class A> void Register(const char* name, R (*function)(A));
		// 0x10803630: the same for a function without arguments (the Function0 form)
		template<class R> void Register(const char* name, R (*function)());
		// Defined in function.h with the rest of the wrappers: the forms of two, three and four arguments
		template<class R, class A1, class A2> void Register(const char* name, R (*function)(A1, A2));
		template<class R, class A1, class A2, class A3> void Register(const char* name, R (*function)(A1, A2, A3));
		template<class R, class A1, class A2, class A3, class A4> void Register(const char* name,
			R (*function)(A1, A2, A3, A4));
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
		template<class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7> void RegisterMethod(const char* name, C* object,
			R (C::*method)(A1, A2, A3, A4, A5, A6, A7));
		template<class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> void RegisterMethod(const char* name, C* object,
			R (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8));
		// 0x10802DB0 / 0x10802E00: registers a C function (with an upvalue)
		void RegisterCFunction(const char* name, int (*function)(lua_State*));
		void RegisterCFunction(const char* name, int (*function)(lua_State*, void*), void* upvalue);
		// 0x10801480 / 0x10801500: a global table for an enumeration and its values (kept to be registered again
		// when the state is rebuilt)
		void CreateEnum(const char* name);
		void AddEnumValue(const char* table, const char* key, int value);

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

		// 0x10801410: pushes a registered C function (its pointer and upvalue) and stores it as a global
		void BindCFunction(LuaCFunction* function);
		// 0x10801D10: stores the closure that dispatches to function as the global name in L
		void BindFunction(const char* name, Function* function, lua_State* L);
		// 0x10801D90: counts the references left and closes the state
		void CloseScriptState();
		// 0x10801DB0: binds every registered function in the (new) state; 0x10801E00: creates the enumerations again
		void BindFunctions();
		void RestoreEnums();
		// 0x10801E90 / 0x10803FD0: closes the state / opens it again (functions, enumerations, scripts)
		void Shutdown();
		void Restart();
		// 0x10804000: closes the state, rebuilds it and starts a new generation of registrations
		void Reload();
		// 0x10803F60: creates the Lua state
		void OpenState();
		bool IsVariableDefined(const char* name);
		// 0x10801ED0: loads and runs a chunk; the Lua status
		int DoLuaBuffer(lua_State* L, const char* buffer, int length, const char* chunkName);
		// 0x10803300: the same for the manager's own state, as a ScriptResult; 0x10803330: runs a script file
		ScriptResult DoBuffer(const char* buffer, const char* chunkName, int length);
		ScriptResult DoFile(const char* path, int unused);
		// 0x10803930 (0x10803970 for the script function sh_ProcessFile): runs the file and remembers it to run it
		// again when the state is rebuilt; 0x10803450 runs the remembered files
		ScriptResult ProcessFile(const char* path, int unused);
		ScriptResult ProcessFile(const char* path);
		// 0x10803D40
		void RunInitScript();
		// 0x10803800: registers the global functions of the scripts (print, tostring, type, the debugging helpers)
		void RegisterBaseFunctions(lua_State* L);
		// 0x10803980: creates the Lua state at *target, closing the one it holds
		void CreateState(lua_State** target);
		// 0x10802E50 / 0x10802F10: writes / reads the script state
		void SaveState(lua_State* L, int stream, int reference, int unused, int flags);
		void LoadState(lua_State* L, int stream, int reference, int flags);
		void RunScripts();
		// 0x10801F50 / 0x10801F60: stores the value on top as a reference / releases a reference
		int MakeReference();
		bool ReleaseReference(int reference);
		// A table by name: the global one or one in the table below the top, optionally created when missing
		bool OpenTable(const char* name, bool global, bool create);
		bool ClearEvent();
		// 0x108022D0
		bool SetCollisionEvent(const char* actor, const math::Vector* pushbackVelocity, const char* sourceMotionNode);
		const char* GetActorCommand(const char* actor, const char* command);
		bool IsScheduleFull();
		bool IsPersistent(const ScheduledCall* call);
		void SetContext(core::IRefCount* newContext);
		// 0x10802550: turns the function on top into a coroutine and keeps it as a reference
		int CreateCoroutine();
		int LoadCoroutine(const char* buffer, int length, const char* name);
		int CreateCoroutineFromReference(int reference);
		// 0x10802590: resumes the coroutine of reference; false when it finished or failed (then the reference is
		// released; failed is set on an error)
		bool ResumeCoroutine(int reference, bool* failed);
		// 0x108048E0: calls the function of reference at the given time (seconds from now), for owner
		int Schedule(float delay, int reference, bool persistent, GameObjectHandle owner);
		// 0x108049A0 / 0x10804A70: removes the scheduled call with the id / the calls of an owner
		bool CancelScheduled(int id);
		bool CancelScheduledFor(GameObjectHandle owner);
		// 0x10804B50: the schedule runs the calls that are due; 0x10804E80: the frame update
		void RunScheduled(core::Time elapsed);
		void Update(core::Time elapsed);
		// 0x10804D10 / 0x10804D50: removes all scheduled calls / moves the persistent ones back to the schedule
		void CancelAllScheduled();
		void RestoreScheduled();
		// 0x10803A60: asks the objects on the Lua environment channel for their environment and looks the function
		// up in it; its source file (into sourceBuffer, when given) and line
		bool FindFunctionSource(const char* functionName, char* sourceBuffer, unsigned int bufferSize, int* line);
		// 0x10803C20: releases the references of the persistent calls that are no longer scheduled
		void ReleasePersistent();
		// 0x10804020: copies the persistent calls (their times relative to now)
		void SavePersistent();

		int unknown4;
		int unknown8;
		lua_State* state;
		// The thread a coroutine runs in
		lua_State* currentState;
		ScriptNameTable<Function> functions;
		ScriptNameTable<LuaCFunction> cfunctions;
		// Set by Reload: from then on enumeration values and script files are no longer recorded
		bool reloaded;
		unsigned char unknown2D[3];
		container::ArrayDynamicNew<LuaEnumValue> enumValues;
		int unknown3C;
		container::ArrayDynamicNew<const char*> scripts;
		int unknown4C;
		core::IRefCount* context;
		bool open;
		unsigned char generation;
		unsigned char unknown56[2];
		int unknown58;
		// The stack tops of the nested table walks
		int walkTops[8];
		int walkDepth;
		const void* owner;
		container::ArrayDynamic<ScheduledCall, container::AllocatorCoreStatic<0x7a, 16> > scheduled;
		int nextScheduleId;
		core::Time time;
		container::ArrayDynamic<ScheduledCall, container::AllocatorCoreStatic<0x7a, 16> > persistent;
		bool unknownB4;
		bool hasError;
		bool unknownB6;
		char errorText[0x100];
		UnusedArray unknown1B8;
		int unknown1C4;
	};

	// The script manager (0x11284254)
	extern LuaScriptManager* gScriptManager;

	// 0x107FEFB0: the current script context, null when no script runs
	LuaScriptManager* GetScriptManager();
}

#endif
