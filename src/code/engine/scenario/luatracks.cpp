// The scenario's Lua fight nodes (see luatracks.h). The unit runs 0x10808840 - 0x10809B90.
#include "code/engine/scenario/luatracks.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luaenvironmentmessage.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/scenario/scriptowner.h"
#include "code/engine/system/enginememory.h"
#include "code/lua/lua.h"
#include <stdlib.h>
#include <string.h>

namespace engine
{
	// 0x105A84D0 (another unit): shows a script error (names guessed)
	int ShowScriptError(int kind, const char* text, const char* title, unsigned int first, unsigned int second,
		int line);

	// The hook the scripting calls around a node's script and its data (0x111BF298 / 0x11284B58)
	extern ScriptHook gScriptHook;
	void* gScriptHookData;

	// The property lists of the track and the condition (0x11284B5C / 0x11284B60)
	namespace scenario
	{
		fight::Property** gLuaTrackProperties;
		fight::Property** gLuaConditionProperties;
	}

	// ---- the script hook -----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10808890
	void SetScriptHook(ScriptHook hook, void* data)
	{
		gScriptHook = hook;
		gScriptHookData = data;
	}

	// FUNCTION: ENGINE 0x108088B0
	void GetScriptHook(ScriptHook* hook, void** data)
	{
		*hook = gScriptHook;
		*data = gScriptHookData;
	}

	// FUNCTION: ENGINE 0x108088D0
	void CallScriptHook(ScriptHookArgs* args, bool finish)
	{
		gScriptHook(gScriptHookData, false, finish, args);
	}

#ifdef NONMATCHING
	// FUNCTION: ENGINE 0x10808DA0
	// NONMATCHING: the same steps; the engine tests the owner's kind with an add and an unsigned compare, keeps its id in
	// ebp across the current-id call and tests the owner again in the second range check, 49.5 %
	bool DefaultScriptHook(void* data, bool keepOpen, bool finish, ScriptHookArgs* args)
	{
		bool opened;
		if (keepOpen || (args->manager != 0 && args->manager->OpenContext()))
		{
			opened = true;
		}
		else
		{
			opened = false;
		}
		GameObjectHandle handle;
		ScriptOwner* owner = (ScriptOwner*)args->owner;
		if (owner != 0)
		{
			if (owner->kind - 1 <= 0xfffe)
			{
				int ownerId = owner->id;
				if (!finish && opened && ScriptOwner::GetCurrentId() != ownerId)
				{
					args->manager->ClearEvent();
					ScriptOwner::SetCurrentId(owner->id);
					owner->GetPart()->WriteEvent();
				}
				handle = owner->handle;
			}
			else if (owner != 0 && owner->kind - 0x10000 <= 0x1ffff)
			{
				handle = *(GameObjectHandle*)&owner->id;
			}
		}
		args->object = handle.Get();
		if (opened)
		{
			if (finish)
			{
				args->manager->ClearField("gameObject");
				args->manager->ClearField("node");
			}
			else
			{
				args->manager->SetHandle("gameObject", SerializeHandle(handle));
				args->manager->SetString("node", args->name);
			}
			if (!keepOpen)
			{
				args->manager->CloseContext();
			}
		}
		return true;
	}
#endif

	namespace scenario
	{
		// FUNCTION: ENGINE 0x10809460
		// EQUIVALENT: the same operations; the engine passes the script in ecx and the length in eax (two register
		// parameters), ours only the script in eax and the length on the stack (its caller, Slot6, differs likewise)
		// The expression of a condition: wrapped in "return (...)" unless it is already a compiled chunk; the name is
		// the chunk's (the branch's path when empty)
		static int CompileExpression(const char* script, fight::Condition* node, const char* name, int length, fight::Track* listener)
		{
			int result = 0;
			if (script != 0)
			{
				LuaScriptManager* manager = GetScriptManager();
				bool wrapped = false;
				char* buffer = 0;
				if (script[0] != 0x1b)
				{
					buffer = new(1) char[length + 16];
					wrapped = true;
					core::SNPrintf(buffer, length + 16, "return (%s)", script);
					length = strlen(buffer);
					script = buffer;
				}
				char path[256];
				if (name == 0 || name[0] == 0)
				{
					listener->GetPath(path, 256, 0);
					name = path;
				}
				char chunkName[256] = "=";
				core::StrNCat(chunkName, name, 254);
				lua_State* L = manager->state;
				if (luaL_loadbuffer(L, script, length, chunkName) != 0)
				{
					const char* message = lua_tolstring(L, -1, 0);
					if (core::StrStr(message, name) != 0)
					{
						message += core::StrLen(name) + 1;
					}
					int line = atoi(message);
					char text[1024];
					core::SNPrintf(text, 1024, "\nLUA SYNTAX ERROR\nBranch: %s\nLine %s\n", name, message);
					ShowScriptError(0, text, "Lua Error", (unsigned int)listener, (unsigned int)node, line);
					lua_settop(L, -2);
					result = 0;
				}
				else
				{
					result = manager->MakeReference();
				}
				if (wrapped)
				{
					delete[] buffer;
				}
			}
			return result;
		}

		// ---- the track ---------------------------------------------------------------------------------------------

		// FUNCTION: ENGINE 0x10808860
		bool LuaTrack::SetTimeBegin(float value)
		{
			timeBegin = value;
			return true;
		}

		// FUNCTION: ENGINE 0x10808870
		bool LuaTrack::SetTimeEnd(float value)
		{
			timeEnd = value;
			return true;
		}

		// FUNCTION: ENGINE 0x108088F0
		fight::Property* LuaTrack::GetProperty(int index)
		{
			return gLuaTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10808900
		void LuaTrack::ClearProperties()
		{
			fight::FreePropertyList(&gLuaTrackProperties);
		}

		// FUNCTION: ENGINE 0x10808910
		LuaTrack::LuaTrack()
			: timeBegin(0.0f), timeEnd(-1.0f), script(0), scriptLength(0), function(0)
		{
		}

		// FUNCTION: ENGINE 0x10808950
		float LuaTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10808960
		float LuaTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x10808980
		void LuaTrack::ReleaseFunction()
		{
			LuaScriptManager* manager = GetScriptManager();
			manager->ReleaseReference(function);
			function = 0;
		}

		// FUNCTION: ENGINE 0x108089A0
		bool LuaTrack::Slot5(int a, int b, int c)
		{
			bool result = fight::Track::Slot5(a, b, c);
			if (result && b != 0)
			{
				((fight::Branch*)b)->ListChild(this);
			}
			return result;
		}

		// FUNCTION: ENGINE 0x108089E0
		void LuaTrack::Slot6(int a, int b)
		{
		}

		// FUNCTION: ENGINE 0x10808A90
		LuaTrack::~LuaTrack()
		{
			delete[] script;
			ReleaseFunction();
		}

		// FUNCTION: ENGINE 0x10808AC0
		bool LuaTrack::SetScript(const char* text, int length)
		{
			script = AssignString(script, &scriptLength, text, length);
			ReleaseFunction();
			return true;
		}

		// FUNCTION: ENGINE 0x10808AF0
		void LuaTrack::Compile(fight::Track* listener)
		{
			ReleaseFunction();
			if (script != 0)
			{
				LuaScriptManager* manager = GetScriptManager();
				char path[256];
				listener->GetPath(path, 256, 0);
				char chunkName[256] = "=";
				core::StrNCat(chunkName, path, 254);
				lua_State* L = manager->state;
				if (luaL_loadbuffer(L, script, scriptLength, chunkName) != 0)
				{
					const char* message = lua_tolstring(L, -1, 0);
					if (core::StrStr(message, path) != 0)
					{
						message += core::StrLen(path) + 1;
					}
					int line = atoi(message);
					char text[1024];
					core::SNPrintf(text, 1024, "\nLUA SYNTAX ERROR\nBranch: %s\nLine %s\n", path, message);
					ShowScriptError(0, text, "Lua Error", (unsigned int)listener, (unsigned int)this, line);
					lua_settop(L, -2);
					return;
				}
				function = manager->MakeReference();
			}
		}

		// FUNCTION: ENGINE 0x108093E0
		fight::Action* LuaTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			Compile(listener);
			if (function != 0)
			{
				return new LuaAction(listener, this, owner, function);
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x108090D0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch; ours sinks the push behind the
		// branch (97.7 %)
		void LuaTrack::RegisterProperties()
		{
			if (gLuaTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = new fight::PropertyFloatConstRange<LuaTrack>("timeBegin", &LuaTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<LuaTrack>("timeEnd", &LuaTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyScript<LuaTrack>("script", &LuaTrack::SetScript);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gLuaTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10808FE0
		fight::TrackFactory* CreateLuaTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<LuaTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108090A0
		void RegisterLuaTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<LuaTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		// ---- the action --------------------------------------------------------------------------------------------

		// FUNCTION: ENGINE 0x108091B0
		LuaAction::LuaAction(fight::Track* listener, LuaTrack* newTrack, core::IRefCount* newOwner, int reference)
			: fight::Action(0xE00), link(newTrack), owner(newOwner), watch(listener), coroutine(0), function(0), environment(0)
		{
			LuaScriptManager* manager = GetScriptManager();
			if (manager->PushReference(reference))
			{
				function = manager->MakeReference();
			}
		}

		__forceinline void LuaAction::ReleaseReferences()
		{
			LuaScriptManager* manager = GetScriptManager();
			manager->ReleaseReference(coroutine);
			coroutine = 0;
			manager->ReleaseReference(function);
			function = 0;
		}

		// FUNCTION: ENGINE 0x108089F0
		void LuaAction::Slot6()
		{
			ReleaseReferences();
		}


		// FUNCTION: ENGINE 0x10808F10
		LuaAction::~LuaAction()
		{
			ReleaseReferences();
		}

		// FUNCTION: ENGINE 0x10808C30
		bool LuaAction::Slot5(int arg, float value)
		{
			LuaScriptManager* manager = GetScriptManager();
			ScriptHookArgs args(0, owner, "");
			CallScriptHook(&args, false);
			if (args.object != 0)
			{
				GetLuaEnvironmentMessage message;
				args.object->PostMessage(&message);
				if (message.reference != 0)
				{
					lua_State* L = manager->state;
					manager->PushReference(function);
					manager->PushReference(message.reference);
					lua_setfenv(L, -2);
					lua_settop(L, -2);
					environment = message.reference;
				}
			}
			coroutine = manager->CreateCoroutineFromReference(function);
			return true;
		}

		// FUNCTION: ENGINE 0x10809270
		bool LuaAction::Slot7(int arg, float value)
		{
			if (coroutine == 0)
			{
				return false;
			}
			if (link.object == 0)
			{
				return false;
			}
			LuaScriptManager* manager = GetScriptManager();
			core::IRefCount* savedContext = manager->context;
			if (savedContext != 0)
			{
				savedContext->AddRef();
			}
			manager->SetContext(owner);
			ScriptHookArgs args(manager, owner, "Debugging only. DO NOT USE THIS IN RELEASE MODE!");
			CallScriptHook(&args, false);
			if (environment != 0)
			{
				manager->PushReference(function);
				manager->PushReference(environment);
				lua_setfenv(manager->state, -2);
				manager->Pop(1);
			}
			bool failed = false;
			bool resumed = manager->ResumeCoroutine(coroutine, &failed);
			manager->SetContext(savedContext);
			if (savedContext != 0)
			{
				savedContext->Release();
			}
			CallScriptHook(&args, true);
			if (!resumed)
			{
				coroutine = 0;
			}
			if (coroutine == 0)
			{
				manager->ReleaseReference(coroutine);
				coroutine = 0;
				manager->ReleaseReference(function);
				function = 0;
				return false;
			}
			return true;
		}

		// ---- the condition -----------------------------------------------------------------------------------------

		// FUNCTION: ENGINE 0x108095F0
		fight::Property* LuaCondition::GetProperty(int index)
		{
			return gLuaConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x10809600
		void LuaCondition::ClearProperties()
		{
			fight::FreePropertyList(&gLuaConditionProperties);
		}

		// FUNCTION: ENGINE 0x10809610
		LuaCondition::LuaCondition()
			: fight::Condition(0), script(0), scriptLength(0), function(0)
		{
		}

		// FUNCTION: ENGINE 0x10809650
		void LuaCondition::ReleaseFunction()
		{
			LuaScriptManager* manager = GetScriptManager();
			manager->ReleaseReference(function);
			function = 0;
		}

		// FUNCTION: ENGINE 0x10809760
		bool LuaCondition::Slot5(int a, int b, int c)
		{
			bool result = fight::Condition::Slot5(a, b, c);
			if (result && b != 0)
			{
				((fight::Branch*)b)->ListChild(this);
			}
			return result;
		}

		// FUNCTION: ENGINE 0x108097A0
		// EQUIVALENT: calls the helper above with the length on the stack instead of in eax
		void LuaCondition::Slot6(int a, int b)
		{
			function = CompileExpression(script, this, "", scriptLength, (fight::Track*)a);
		}

		// FUNCTION: ENGINE 0x108097D0
		LuaCondition::~LuaCondition()
		{
			delete[] script;
			ReleaseFunction();
		}

		// FUNCTION: ENGINE 0x10809800
		bool LuaCondition::SetScript(const char* text, int length)
		{
			script = AssignString(script, &scriptLength, text, length);
			ReleaseFunction();
			return true;
		}

		// FUNCTION: ENGINE 0x10809670
		bool LuaCondition::Evaluate(int a, int b, int c, int d)
		{
			int expression = function;
			LuaScriptManager* manager = GetScriptManager();
			bool result = false;
			ScriptHookArgs args(manager, (core::IRefCount*)c, "Debugging ony. DO NOT USE THIS IN RELEASE MODE!");
			CallScriptHook(&args, false);
			if (expression == 0)
			{
				return false;
			}
			manager->PushReference(expression);
			lua_State* L = manager->state;
			if (args.object != 0)
			{
				GetLuaEnvironmentMessage message;
				args.object->PostMessage(&message);
				if (message.reference != 0)
				{
					manager->PushReference(message.reference);
					lua_setfenv(L, -2);
				}
			}
			int count = manager->Call(-1);
			if (count < 0)
			{
				manager->Pop(1);
			}
			else if (count > 0)
			{
				result = lua_toboolean(L, -1) != 0;
				manager->Pop(count);
			}
			CallScriptHook(&args, true);
			return result;
		}

		// FUNCTION: ENGINE 0x10809930
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch; ours sinks the push behind the
		// branch (97.4 %)
		void LuaCondition::RegisterProperties()
		{
			if (gLuaConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = new fight::PropertyScript<LuaCondition>("script", &LuaCondition::SetScript);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gLuaConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x10809890
		fight::ConditionFactory* CreateLuaConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<LuaCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10809900
		void RegisterLuaConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<LuaCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<LuaTrack>;
		template class fight::PropertyScript<LuaTrack>;
		template class fight::TrackFactoryTemplate<LuaTrack>;
		template class fight::TrackFactoryCasterTemplate<LuaTrack>;
		template class fight::PropertyScript<LuaCondition>;
		template class fight::ConditionFactoryTemplate<LuaCondition>;
		template class fight::ConditionFactoryCasterTemplate<LuaCondition>;
	}
}
