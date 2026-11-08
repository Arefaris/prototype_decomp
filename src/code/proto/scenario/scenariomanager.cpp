// The scenario manager: the timers and clocks of the scenario scripts, the package swaps and dynamic slot groups of the
// streaming and the deactivation of objects the scripts ask for (unit 0x10488E10 - 0x1048B3B0).
#include "code/proto/scenario/scenariomanager.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/streamtrigger.h"
#include "code/math/vector.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/system/streammanager.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include <new>

namespace engine
{
	// 0x1126B8B8: the name "Undefined_SlotGroup"
	extern core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup230;
	// 0x1126B8C8: the channel "scenario"
	extern MessageListeners gScenario79;
}

// The one-argument registration (each unit that registers one keeps a copy)
template<class R, class A> inline void engine::LuaScriptManager::Register(const char* name, R (*function)(A))
{
	AddFunction(name, new Function1<R, A>(name, function));
}

namespace proto
{
	// 0x1126EE68: the name of the mission package slot group
	extern core::Name<core::CaseSensitiveKey> gGroupName1126EE68;

	// 0x1027FCB0: the package of that name (name guess)
	engine::StreamPackage* FindPackageByText(const char* name);
	// 0x104887E0 (scenario_package.h)
	void Unknown104887E0(const core::Name<core::CaseSensitiveKey>& packageName);

	namespace scenario
	{
		// 0x10489280 / 0x104892B0: whether the package is not loaded (no instance, or in the unloaded, evictable or
		// no state) / is loaded (names guessed)
		bool IsPackageUnloaded(engine::StreamPackage* package);
		bool IsPackageLoaded(engine::StreamPackage* package);

		// 0x1048AD40 / 0x1048ADF0 / 0x1048AE70: the script natives that set and get the corners of a stream trigger's box
		// (stream_SetCellTriggerBoundingBox, stream_GetCellTriggerHigh, stream_GetCellTriggerLow)
		bool SetCellTriggerBoundingBox(const char* name, math::Vector low, math::Vector high);
		math::Vector GetCellTriggerHigh(const char* name);
		math::Vector GetCellTriggerLow(const char* name);

		// 0x1126B8A8
		ScenarioManager* gScenarioManager;

		// FUNCTION: ENGINE 0x1048B1E0
		ScenarioManager::ScenarioManager() : nextTimerId(0), elapsedTime(0.0f), simulationDelta(0.0f), elapsedRealTime(0.0f), realTimeDelta(0.0f), heartbeatTime(0.0f), missionFirst(0), missionSecond(0), swapIn(0), swapOut(0), savedGroupName(), slotsCombined(false)
		{
			deferred.Create(0x20);
			for (int i = 0; i < 0x20; i++)
			{
				engine::GameObjectHandle none;
				deferred.PushBack(DeferredDeactivation(none, 0));
			}
			deferredHead = 0;
			deferredTail = 0;
			deferredCount = 0;
			gScenarioManager = this;
		}

		// FUNCTION: ENGINE 0x1048B370
		ScenarioManager::~ScenarioManager()
		{
			FlushDeferred(true);
			gScenarioManager = 0;
		}

		// FUNCTION: ENGINE 0x10488F80
		void ScenarioManager::AdvanceRealTime(float delta)
		{
			elapsedRealTime = delta + elapsedRealTime;
			realTimeDelta = delta;
		}

		// FUNCTION: ENGINE 0x10488FB0
		// NONMATCHING: register allocation of the string scan (ebp where the engine has ebx), 93.8 %
#ifdef NONMATCHING
		int ScenarioManager::StartTimer(float time, const char* message)
		{
			if (time < 0.0f)
			{
				return -1;
			}
			const char* end = message;
			const char* start = end + 1;
			do
			{
			}
			while (*end++ != 0);
			if (end - start < 0x100)
			{
				for (int i = 0; i < 16; i++)
				{
					if (timers[i].time == -1.0f)
					{
						timers[i].time = time;
						core::StrNCpy(timers[i].message, message, 0x100);
						timers[i].id = nextTimerId;
						nextTimerId++;
						return timers[i].id;
					}
				}
			}
			return -1;
		}
#endif

		// FUNCTION: ENGINE 0x10489080
		void ScenarioManager::CancelTimer(int id)
		{
			for (int i = 0; i < 16; i++)
			{
				if (timers[i].id == id)
				{
					ScenarioTimer* timer = &timers[i];
					timer->time = -1.0f;
					timer->message[0] = 0;
					timer->id = -1;
					return;
				}
			}
		}

		// FUNCTION: ENGINE 0x104890E0
		float ScenarioManager::GetElapsedTime()
		{
			return elapsedTime;
		}

		// FUNCTION: ENGINE 0x104890F0
		float ScenarioManager::GetSimulationDelta()
		{
			return simulationDelta;
		}

		// FUNCTION: ENGINE 0x10489100
		float ScenarioManager::GetElapsedRealTime()
		{
			return elapsedRealTime;
		}

		// FUNCTION: ENGINE 0x10489110
		float ScenarioManager::GetRealTimeDelta()
		{
			return realTimeDelta;
		}

		// FUNCTION: ENGINE 0x10489120
		void ScenarioManager::UpdateTimers(float delta)
		{
			ScenarioTimer* timer = timers;
			for (int count = 16; count != 0; count--)
			{
				if (0.0f <= timer->time)
				{
					timer->time = timer->time - delta;
					if (timer->time < 0.0f)
					{
						char name[0x40];
						engine::LuaScriptManager* script = engine::GetScriptManager();
						core::SNPrintf(name, 0x40, "=timer: %.50s", timer->message);
						script->DoBuffer(timer->message, name, -1);
						timer->time = -1.0f;
						timer->message[0] = 0;
						timer->id = -1;
					}
				}
				timer++;
			}
		}

		// FUNCTION: ENGINE 0x104891D0
		void ScenarioManager::ClearTimers()
		{
			float free = -1.0f;
			for (int i = 0; i < 16; i++)
			{
				timers[i].time = free;
				timers[i].message[0] = 0;
				timers[i].id = -1;
			}
			nextTimerId = 0;
		}

		// FUNCTION: ENGINE 0x10489690
		void ScenarioManager::SaveTimers(container::ArrayFixed<ScenarioTimer, 16>* saved, int* nextId)
		{
			ScenarioTimer* timer = timers;
			for (int i = 0; i < 4; i++)
			{
				if (0.0f <= timer[0].time)
				{
					if (saved->Size() != 16)
					{
						ScenarioTimer* slot = saved->end;
						saved->end++;
						*new (slot) ScenarioTimer = timer[0];
					}
				}
				if (0.0f <= timer[1].time)
				{
					if (saved->Size() != 16)
					{
						ScenarioTimer* slot = saved->end;
						saved->end++;
						*new (slot) ScenarioTimer = timer[1];
					}
				}
				if (0.0f <= timer[2].time)
				{
					if (saved->Size() != 16)
					{
						ScenarioTimer* slot = saved->end;
						saved->end++;
						*new (slot) ScenarioTimer = timer[2];
					}
				}
				if (0.0f <= timer[3].time)
				{
					if (saved->Size() != 16)
					{
						ScenarioTimer* slot = saved->end;
						saved->end++;
						*new (slot) ScenarioTimer = timer[3];
					}
				}
				timer += 4;
			}
			*nextId = nextTimerId;
		}

		// FUNCTION: ENGINE 0x10489900
		void ScenarioManager::RestoreTimers(container::ArrayFixed<ScenarioTimer, 16>* saved, int newNextId)
		{
			ClearTimers();
			nextTimerId = newNextId;
			int count = saved->Size();
			if (count >= 16)
			{
				count = 16;
			}
			for (int i = 0; i < count; i++)
			{
				timers[i] = (*saved)[i];
			}
		}

		// FUNCTION: ENGINE 0x10489230
		void ScenarioManager::SetMission(unsigned int first, unsigned int second)
		{
			missionFirst = first;
			missionSecond = second;
		}

		// FUNCTION: ENGINE 0x10489250
		void ScenarioManager::GetMission(unsigned int* first, unsigned int* second)
		{
			*first = missionFirst;
			*second = missionSecond;
		}
		// FUNCTION: ENGINE 0x104892D0
		bool ScenarioManager::ConfirmMissionPackageSlotGroupEmpty()
		{
			engine::StreamSlotGroup* group = engine::StreamManager::FindSlotGroup(gGroupName1126EE68);
			int missionPackageSlotGroupAllocations = 0;
			engine::StreamSlot* slot = group->GetSlot(0);
			core::IMemoryAllocator* allocator = core::GetHeapAllocator(slot->heap);
			allocator->GetStat(0, &missionPackageSlotGroupAllocations);
			OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\proto\\scenario\\scenariomanager.cpp", 0x15B, missionPackageSlotGroupAllocations == 0, "missionPackageSlotGroupAllocations == 0");
			return missionPackageSlotGroupAllocations == 0;
		}

		// FUNCTION: ENGINE 0x10489370
		bool ScenarioManager::RestoreDynamicSlots()
		{
			if (slotsCombined)
			{
				dynamicGroup->SetName(savedGroupName);
				dynamicGroup->priority = savedPriority;
				dynamicGroup->shared = savedShared;
				dynamicGroup->unknown67 = savedUnknown67;
				dynamicGroup->Reconfigure(savedSlotCount, (const engine::SlotHeapConfig*)savedConfig);
				slotsCombined = false;
				return true;
			}
			return false;
		}
		// FUNCTION: ENGINE 0x10489280
		bool IsPackageUnloaded(engine::StreamPackage* package)
		{
			if (package->instance != 0)
			{
				int state = package->instance->state;
				if (state != engine::StreamPackageInstance::STATE_UNLOADED && state != engine::StreamPackageInstance::STATE_EVICTABLE && state != engine::StreamPackageInstance::STATE_NONE)
				{
					return false;
				}
			}
			return true;
		}

		// FUNCTION: ENGINE 0x104892B0
		bool IsPackageLoaded(engine::StreamPackage* package)
		{
			if (package->instance != 0 && package->instance->state == engine::StreamPackageInstance::STATE_LOADED)
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x10489410
		void ScenarioManager::UpdatePackageSwap()
		{
			if (swapOut != 0 && swapIn != 0)
			{
				if (IsPackageUnloaded(swapOut))
				{
					swapIn->Load(0, 0xFFFF, engine::gUndefinedSlotGroup230, true);
					swapIn = 0;
					swapOut = 0;
				}
			}
		}

		// FUNCTION: ENGINE 0x10489980
		void ScenarioManager::PackageSwap(const char* oldName, const char* newName)
		{
			engine::StreamPackage* oldPackage = FindPackageByText(oldName);
			engine::StreamPackage* newPackage = FindPackageByText(newName);
			if (oldPackage != 0 && IsPackageLoaded(oldPackage) && newPackage != 0 && IsPackageUnloaded(newPackage))
			{
				core::Name<core::CaseSensitiveKey> name(oldName, 1);
				Unknown104887E0(name);
				oldPackage->Unload(0, true);
				swapOut = oldPackage;
				swapIn = newPackage;
			}
		}

		// FUNCTION: ENGINE 0x10489A20
		// NONMATCHING: scheduling of the group stores and the name temporaries, 26.1 %
#ifdef NONMATCHING
		bool ScenarioManager::CombineDynamicSlots()
		{
			if (!slotsCombined)
			{
				savedGroupName = core::Name<core::CaseSensitiveKey>("DynamicPackageSlotGroup", 1);
				dynamicGroup = engine::StreamManager::FindSlotGroup(savedGroupName);
				savedSlotCount = dynamicGroup->slotCount;
				{
					int config[3];
					int* saved = dynamicGroup->GetSlotHeapConfig(config);
					savedConfig[0] = saved[0];
					savedConfig[1] = saved[1];
					savedConfig[2] = saved[2];
				}
				savedPriority = dynamicGroup->priority;
				savedShared = dynamicGroup->shared;
				savedUnknown67 = dynamicGroup->unknown67;
				engine::SlotHeapConfig combined = { 0x780000, false, 0x1000 };
				dynamicGroup->SetName(core::Name<core::CaseSensitiveKey>("DynamicPackageSlotGroup", 1));
				dynamicGroup->shared = true;
				dynamicGroup->Reconfigure(savedSlotCount, &combined);
				slotsCombined = true;
				return true;
			}
			return false;
		}
#endif
		// FUNCTION: ENGINE 0x1048A320
		void ScenarioManager::FinishDeactivation(engine::GameObjectHandle handle)
		{
			if (handle.Get() != 0)
			{
				if (proto::gAmbientManager->Unknown104138E0(handle))
				{
					proto::gAmbientManager->Unknown10411D20(handle);
				}
				engine::DeferUpdate(handle, false);
			}
		}

		// FUNCTION: ENGINE 0x1048A390
		// NONMATCHING: the engine tests the handle's serial twice, 31.3 %
#ifdef NONMATCHING
		void ScenarioManager::DeactivateObject(engine::GameObjectHandle handle)
		{
			engine::GameObject* object = handle.Get();
			if (object != 0)
			{
				object = handle.Get();
				object->SetActive(false);
				if (deferredCount < (int)deferred.Capacity())
				{
					DeferredDeactivation* entry = deferred.Begin() + deferredHead;
					if (entry != 0)
					{
						int frame = engine::GetGameObjectFrame() + 1;
						entry->handle = handle;
						entry->frame = frame;
					}
					deferredHead++;
					deferredCount++;
					deferredHead = deferredHead % deferred.Capacity();
				}
				else
				{
					FinishDeactivation(handle);
				}
			}
		}
#endif

		// FUNCTION: ENGINE 0x1048A490
		void ScenarioManager::FlushDeferred(bool all)
		{
			while (deferredCount != 0)
			{
				DeferredDeactivation entry = deferred[deferredTail];
				if (!all && entry.frame != engine::GetGameObjectFrame())
				{
					break;
				}
				FinishDeactivation(entry.handle);
				deferredTail++;
				deferredCount--;
				deferredTail = deferredTail % deferred.Capacity();
			}
		}
		// FUNCTION: ENGINE 0x10489480
		void ScenarioManager::UnregisterScript()
		{
			engine::LuaScriptManager* script = engine::GetScriptManager();
			script->Unregister(this);
		}

		// FUNCTION: ENGINE 0x1048A930
		void ScenarioManager::Update(float delta)
		{
			elapsedTime = delta + elapsedTime;
			simulationDelta = delta;
			UpdateTimers(delta);
			UpdatePackageSwap();
			FlushDeferred(false);
			heartbeatTime = heartbeatTime + delta;
			if (heartbeatTime >= 0.1f)
			{
				core::Name<core::CaseSensitiveKey> name("SCRIPT_HeartBeat", 1);
				engine::StringMessage message(name);
				engine::SendMessage(&message, &engine::gScenario79);
				heartbeatTime = 0.0f;
			}
		}
		// FUNCTION: ENGINE 0x1048AD40
		// NONMATCHING: register choice of the inventory lookup, 12 %
#ifdef NONMATCHING
		bool SetCellTriggerBoundingBox(const char* name, math::Vector low, math::Vector high)
		{
			engine::StreamTrigger* trigger = content::gRootInventory->Find<engine::StreamTrigger>(name);
			if (trigger != 0)
			{
				trigger->boundingBox.max.x = high.x;
				trigger->boundingBox.max.y = high.y;
				trigger->boundingBox.max.z = high.z;
				trigger->boundingBox.min.x = low.x;
				trigger->boundingBox.min.y = low.y;
				trigger->boundingBox.min.z = low.z;
				return true;
			}
			return false;
		}
#endif

		// FUNCTION: ENGINE 0x1048ADF0
		// NONMATCHING: the vector copy is three movss loads then stores in the engine, 61 %
#ifdef NONMATCHING
		math::Vector GetCellTriggerHigh(const char* name)
		{
			math::Vector result;
			content::LoadInventory* inventory = content::gRootInventory;
			engine::StreamTrigger* trigger = inventory->Find<engine::StreamTrigger>(name);
			if (trigger != 0)
			{
				float x = trigger->boundingBox.max.x;
				float y = trigger->boundingBox.max.y;
				float z = trigger->boundingBox.max.z;
				result.x = x;
				result.y = y;
				result.z = z;
			}
			return result;
		}
#endif

		// FUNCTION: ENGINE 0x1048AE70
		// NONMATCHING: the vector copy is three movss loads then stores in the engine, 61 %
#ifdef NONMATCHING
		math::Vector GetCellTriggerLow(const char* name)
		{
			math::Vector result;
			content::LoadInventory* inventory = content::gRootInventory;
			engine::StreamTrigger* trigger = inventory->Find<engine::StreamTrigger>(name);
			if (trigger != 0)
			{
				result.x = trigger->boundingBox.min.x;
				result.y = trigger->boundingBox.min.y;
				result.z = trigger->boundingBox.min.z;
			}
			return result;
		}
#endif

		// FUNCTION: ENGINE 0x1048B3B0
		void ScenarioManager::RegisterScript()
		{
			engine::LuaScriptManager* script = engine::GetScriptManager();
			script->SetOwner(this);
			script->RegisterMethod("sm_StartTimer", this, &ScenarioManager::StartTimer);
			script->RegisterMethod("sm_CancelTimer", this, &ScenarioManager::CancelTimer);
			script->RegisterMethod("time_GetSimulationDelta", this, &ScenarioManager::GetSimulationDelta);
			script->RegisterMethod("time_GetElapsedTime", this, &ScenarioManager::GetElapsedTime);
			script->RegisterMethod("time_GetRealTimeDelta", this, &ScenarioManager::GetRealTimeDelta);
			script->RegisterMethod("time_GetElapsedRealTime", this, &ScenarioManager::GetElapsedRealTime);
			script->RegisterMethod("scenario_SetMission", this, &ScenarioManager::SetMission);
			script->Register("stream_SetCellTriggerBoundingBox", SetCellTriggerBoundingBox);
			script->Register("stream_GetCellTriggerHigh", GetCellTriggerHigh);
			script->Register("stream_GetCellTriggerLow", GetCellTriggerLow);
			script->RegisterMethod("stream_PackageSwap", this, &ScenarioManager::PackageSwap);
			script->RegisterMethod("stream_ConfirmMissionPackageSlotGroupEmpty", this, &ScenarioManager::ConfirmMissionPackageSlotGroupEmpty);
			script->RegisterMethod("stream_CombineDynamicSlots", this, &ScenarioManager::CombineDynamicSlots);
			script->RegisterMethod("stream_RestoreDynamicSlots", this, &ScenarioManager::RestoreDynamicSlots);
			script->ClearOwner();
		}
	}
}

// The members of the queue's container that the engine keeps out of line
template container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::ArrayDynamicNew();
template container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::~ArrayDynamicNew();
template void container::ConstructAt<proto::scenario::DeferredDeactivation>(proto::scenario::DeferredDeactivation*, const proto::scenario::DeferredDeactivation&);
template void container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::Clear();
template bool container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::PushBack(const proto::scenario::DeferredDeactivation&);
template proto::scenario::DeferredDeactivation& container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::operator[](int);
template unsigned int container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::Capacity() const;
template bool container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::Create(unsigned int);
template void container::ArrayDynamicNew<proto::scenario::DeferredDeactivation>::Allocate(unsigned int);
template class container::ArrayFixed<proto::scenario::ScenarioTimer, 16>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104894A0
// FUNCTION: ENGINE 0x104894B0
// FUNCTION: ENGINE 0x104894C0
// FUNCTION: ENGINE 0x104894E0
// FUNCTION: ENGINE 0x10489510
// FUNCTION: ENGINE 0x10489530
// FUNCTION: ENGINE 0x10489580
// FUNCTION: ENGINE 0x10489600
// FUNCTION: ENGINE 0x10489B70
// FUNCTION: ENGINE 0x10489B80
// FUNCTION: ENGINE 0x10489BE0
// FUNCTION: ENGINE 0x1048A540
// FUNCTION: ENGINE 0x1048AEF0
