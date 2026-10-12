// engine::ScriptContext (class and member names guessed; the object at 0x11284254, its unit is 0x107FExxx -
// 0x1080xxxx): the engine's Lua state (at +0xC) and the native functions units register with it. A unit registers
// its functions between SetOwner and ClearOwner under the address of one of its statics, and Unregister takes
// everything registered under that address away again.
#ifndef ENGINE_SCRIPTCONTEXT_H
#define ENGINE_SCRIPTCONTEXT_H

#include "code/core/name.h"

namespace engine
{
	struct SerializedHandle;
	class Function;

	class ScriptContext
	{
	public:
		// 0x108021F0: pushes context.event; 0x108000B0: pops it again
		bool OpenEvent();
		bool Close();
		// 0x10800230 / 0x10800270: event[key] = a handle (light userdata) / a name
		bool SetHandle(const char* key, SerializedHandle handle);
		bool SetName(const char* key, const core::Name<core::CaseSensitiveKey>& name);

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
	};

	// 0x107FEFB0: the current script context, null when no script runs
	ScriptContext* GetScriptContext();
}

#endif
