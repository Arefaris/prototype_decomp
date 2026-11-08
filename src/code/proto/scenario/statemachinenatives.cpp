// The script natives of the state machines (fsm_*, registered by 0x10494E90; unit 0x10493880 - 0x10494E90, no assert path;
// the function names are the natives' names written as C++ names). The ones that take a state machine's handle answer
// nothing for a handle that names no object.
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luaenvironmentmessage.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/scenario/scriptowner.h"
#include "code/lua/lua.h"
#include "code/engine/system/streampackage.h"
#include "code/proto/messages/statemachinemessages.h"

namespace engine
{
	// 0x108024C0 (luascriptmanager.cpp)
	void LuaGetNameArgument(lua_State* L, int index, core::Name<core::CaseSensitiveKey>* name);
	// 0x107FFBF0 (another unit)
	bool LuaPushRef(lua_State* L, int reference);
	// 0x1126BB80: the channel of the state machines (statics)
	extern MessageListeners gScenario81;
	// 0x111C17D4: the name of the scenario fight context
	extern const char* const gScenarioContextName;
}

namespace proto
{
	// FUNCTION: ENGINE 0x10493930
	int fsm_GetNumActive()
	{
		return engine::CountListeners(&engine::gScenario81);
	}

	// FUNCTION: ENGINE 0x10493950
	const char* fsm_GetInfo(engine::LuaGOH machine)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10493960
	void fsm_DumpInfo(engine::LuaGOH machine)
	{
	}

	// FUNCTION: ENGINE 0x10494050
	void fsm_Stop(engine::LuaGOH machine)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineSetStateMessage message;
			object->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x104946C0
	bool fsm_MessageSupress(engine::LuaGOH machine, bool suppress)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineSetInfoMessageProperties message;
			message.enabled = suppress;
			object->SendMessage(&message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10494750
	bool fsm_MessageChannel(engine::LuaGOH machine, const char* channel)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineSetInfoMessageProperties message;
			message.text = channel;
			object->SendMessage(&message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10494840
	// NONMATCHING: 43.6 %: stack layout of the handle buffer, the name temporary and the message, and the register of the load listeners
#ifdef NONMATCHING
	bool fsm_MatchLastTransition(engine::LuaGOH machine, const char* path)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineGetLastTransitionMessage message;
			object->SendMessage(&message);
			fight::TrackRegistry* context = engine::gLoadListeners->FindContext(
				core::Name<core::CaseSensitiveKey>(engine::gScenarioContextName, 1));
			fight::Branch* branch = context->branches->FindInTree(path);
			if (branch != 0)
			{
				return message.transition.branch == branch;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10494960
	// NONMATCHING: 57.3 %: stack layout of the handle buffer, the name temporary and the message, and the register of the load listeners
#ifdef NONMATCHING
	bool fsm_MatchCurrentState(engine::LuaGOH machine, const char* path)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineGetStateMessage message;
			object->SendMessage(&message);
			fight::TrackRegistry* context = engine::gLoadListeners->FindContext(
				core::Name<core::CaseSensitiveKey>(engine::gScenarioContextName, 1));
			fight::Branch* branch = context->branches->FindInTree(path);
			if (branch != 0)
			{
				return message.state == branch;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10493EA0
	// NONMATCHING: 92.9 %: the engine's frame is four bytes smaller
#ifdef NONMATCHING
	engine::LuaGOH fsm_GetParent(engine::LuaGOH machine)
	{
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			StateMachineGetParentMessage message;
			object->SendMessage(&message);
			return engine::SerializeHandle(static_cast<const engine::GameObjectHandle&>(message.parent));
		}
		engine::SetScriptError(engine::GetScriptManager(), "Invalid GameObjectHandle");
		engine::GameObjectHandle none;
		return engine::SerializeHandle(none);
	}
#endif

	// FUNCTION: ENGINE 0x10493FA0
	int fsm_GetEnv(lua_State* L)
	{
		engine::LuaGOH machine;
		machine.value = (unsigned int)lua_touserdata(L, 1);
		engine::GameObject* object = engine::DeserializeHandle(machine).Get();
		if (object != 0)
		{
			engine::GetLuaEnvironmentMessage message;
			object->PostMessage(&message);
			engine::GetScriptManager()->PushReference(message.reference);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10494B50
	int fsm_GetPublicData(lua_State* L)
	{
		int result = 0;
		if (lua_gettop(L) >= 1 && lua_type(L, -1) == LUA_TLIGHTUSERDATA)
		{
			engine::LuaGOH machine;
			machine.value = (unsigned int)lua_touserdata(L, -1);
			engine::GameObjectHandle handle = engine::DeserializeHandle(machine);
			engine::GameObject* object = handle.Get();
			if (object != 0)
			{
				GetPublicLuaEnvironmentMessage message;
				object->SendMessage(&message);
				if (message.reference != 0)
				{
					engine::GetScriptManager();
					if (engine::LuaPushRef(L, message.reference))
					{
						result = 1;
					}
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10494A50
	int fsm_GetPrivateEnvironment(lua_State* L)
	{
		int result = 0;
		if (lua_gettop(L) >= 1 && lua_type(L, -1) == LUA_TLIGHTUSERDATA)
		{
			engine::LuaGOH machine;
			machine.value = (unsigned int)lua_touserdata(L, -1);
			engine::GameObjectHandle handle = engine::DeserializeHandle(machine);
			engine::GameObject* object = handle.Get();
			if (object != 0)
			{
				engine::GetLuaEnvironmentMessage message;
				object->PostMessage(&message);
				if (message.reference != 0)
				{
					engine::GetScriptManager();
					if (engine::LuaPushRef(L, message.reference))
					{
						result = 1;
					}
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x104940E0
	// NONMATCHING: 31 %: the engine builds the by-value handle argument in place and keeps the argument count in a stack slot
#ifdef NONMATCHING
	int fsm_PostEventString(lua_State* L)
	{
		engine::GameObjectHandle handles[4];
		int count = lua_gettop(L) - 1;
		count = count > 4 ? 4 : count;
		if ((unsigned int)count > 0)
		{
			int index = 2;
			engine::GameObjectHandle* handle = handles;
			do
			{
				if (lua_type(L, index) != LUA_TLIGHTUSERDATA)
				{
					luaL_argerror(L, index, "expected GameObjectHandle");
				}
				engine::LuaGOH saved;
				saved.value = (unsigned int)lua_touserdata(L, index);
				*handle = engine::DeserializeHandle(saved);
				index++;
				handle++;
				count--;
			}
			while (count != 0);
		}
		core::Name<core::CaseSensitiveKey> name;
		engine::LuaGetNameArgument(L, 1, &name);
		engine::StringMessage message(name);
		message.handles[0] = handles[0];
		message.handles[1] = handles[1];
		message.handles[2] = handles[2];
		message.handles[3] = handles[3];
		engine::ScriptOwner* owner = (engine::ScriptOwner*)engine::GetScriptManager()->context;
		if (owner != 0 && owner->IsNode())
		{
			engine::GameObject* target = owner->handle.Get();
			if (target != 0)
			{
				StateMachinePropagateMessage propagate(&message);
				target->SendMessage(&propagate);
			}
		}
		return 0;
	}
#endif
}
