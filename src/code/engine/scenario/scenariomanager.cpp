#include "code/content/loadinventory.h"
#include "code/core/heap.h"
#include "code/engine/fight/chunk.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/scenario/scenarioconditions.h"
#include "code/engine/scenario/scenariolisters.h"
#include "code/engine/scenario/scenariomanager.h"
#include "code/engine/scenario/scenariotreebehaviour.h"
#include "code/engine/system/streampackage.h"
#include "code/lua/lua.h"
#include <new>

namespace engine
{
	// GLOBAL: ENGINE 0x1130D438
	GameObject* gScenarioObject;

	// 0x1130D448 (statics/dialoguenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gMasterScenario;

	// FUNCTION: ENGINE 0x1082FEE0
	ScenarioTreeBehaviour* GameObject::AddScenarioTreeBehaviour(fight::Branch* root)
	{
		core::HeapScope scope(GetConstructionHeap());
		ScenarioTreeBehaviour* behaviour = new ScenarioTreeBehaviour(this, root);
		behaviours.AddBehaviour(behaviour);
		return behaviour;
	}

	// FUNCTION: ENGINE 0x10830200
	ScenarioMessage* SetLuaEnvironmentMessage::Clone(void* memory, int unused)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10830270
	// NONMATCHING: 92.1 %, the engine stores the new object in the global right before the call that adds the tree
	// (behind the load of the registry's branch), ours stores it straight after the call that made it
#ifdef NONMATCHING
	void StartScenario(fight::TrackRegistry* registry)
	{
		GameObject* object = CreateGameObjectInHeap(gMasterScenario, core::GetCurrentHeap(), 0);
		gScenarioObject = object;
		object->AddScenarioTreeBehaviour(registry->branches);
		gScenarioObject->Slot5();
		gScenarioObject->Slot3((int)content::gRootInventory);
		LuaScriptManager* script = GetScriptManager();
		lua_pushvalue(script->state, LUA_GLOBALSINDEX);
		SetLuaEnvironmentMessage message;
		message.reference = script->MakeReference();
		gScenarioObject->SendMessage(&message);
	}
#endif

	// FUNCTION: ENGINE 0x10830E90
	void StartScenarioContext(int heap)
	{
		int previous = core::SetCurrentHeap(heap);
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = listeners->FindContext(core::Name<core::CaseSensitiveKey>(gScenarioContextName, 1));
		StartScenario(registry);
		core::SetCurrentHeap(previous);
	}

	// FUNCTION: ENGINE 0x10832330
	void MakeScenarioContext()
	{
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(core::Name<core::CaseSensitiveKey>(gScenarioContextName, 1));
		gLoadListeners->AddContext(registry);
		fight::RegisterNodeBranchFactory(registry);
		fight::RegisterBankBranchFactory(registry);
		fight::RegisterStoreBranchFactory(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		fight::RegisterCoreFactories(registry);
		RegisterLightTrackFactory(registry, "light");
		scenario::RegisterLuaConditionFactory(registry, "lua");
		scenario::RegisterLuaTrackFactory(registry, "lua");
		scenario::RegisterScenarioConditionFactories(registry);
		RegisterOnlineConditionFactories(registry);
		RegisterAudioTrackFactories(registry);
		registry->Prepare();
		registry->Complete();
		scenario::RegisterMessageKind<ScenarioInitializeMessage>(1, "Game Init");
		scenario::RegisterMessageKind<ObjectDestroyedMessage>(5, "Object Destroyed");
		scenario::RegisterMessageKind<ObjectStateChangedMessage>(6, "Object State Changed");
		scenario::RegisterMessageKind<StringMessage>(2, "String");
		scenario::RegisterMessageKind<EnterTriggerMessage>(3, "Trigger Volume - Enter");
		scenario::RegisterMessageKind<ExitTriggerMessage>(4, "Trigger Volume - Exit");
		scenario::RegisterMessageKind<ScenarioNISBeginMessage>(0xB, "NIS Begin");
		scenario::RegisterMessageKind<ScenarioNISEndMessage>(0xC, "NIS End");
		scenario::RegisterMessageKind<ScenarioNISLoadCompleteMessage>(0xD, "NIS Load Complete");
		scenario::RegisterMessageKind<ScenarioStreamPackageLoadedMessage>(0x10, "Stream Package Loaded");
		scenario::RegisterMessageKind<ScenarioStreamPackageUnloadedMessage>(0x11, "Stream Package Unloaded");
		scenario::SortListers();
	}
}
