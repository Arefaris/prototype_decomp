// proto::scenario::ScenarioManager (RTTI name; no vftable): the manager of the scenario scripts' clocks and timers,
// the package swaps of the streaming and the objects the scripts deactivate. The script natives it registers
// (0x1048B3B0) are sm_StartTimer, sm_CancelTimer, time_Get*, scenario_SetMission and the stream_* functions. Unit
// 0x10488E10 - 0x1048B3B0 (the assert path code\proto\scenario\scenariomanager.cpp names it). The instance is the
// global 0x1126B8A8. Member names are guesses from the natives.
#ifndef PROTO_SCENARIO_SCENARIOMANAGER_H
#define PROTO_SCENARIO_SCENARIOMANAGER_H

#include "code/container/arraydynamicnew.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/system/streampackage.h"

namespace choreo
{
	// 0x10D94FF8
	extern const float gMinusOne;
}

namespace proto
{
	namespace scenario
	{
		// A timer of the scripts: its time left (negative: free), the script that runs when it is over and its number
		struct ScenarioTimer
		{
			ScenarioTimer()
			{
				time = choreo::gMinusOne;
				message[0] = 0;
				id = -1;
			}

			float time;
			char message[0x100];
			int id;
		};

		// An object waiting for its deactivation to be completed: the handle and the frame it was deactivated in
		struct DeferredDeactivation
		{
			engine::GameObjectHandle handle;
			int frame;
		};

		class ScenarioManager
		{
		public:
			ScenarioManager();
			~ScenarioManager();

			// 0x1048B3B0: registers the natives
			void RegisterScript();
			// 0x1048A930: the per frame step (the simulation's delta)
			void Update(float delta);
			// 0x10488F80: the real time clocks advance
			void AdvanceRealTime(float delta);
			// 0x10488FB0 (sm_StartTimer): the timer's number, -1 when there is none free or the script is too long
			int StartTimer(float time, const char* message);
			// 0x10489080 (sm_CancelTimer)
			void CancelTimer(int id);
			// 0x104890E0 / 0x104890F0 / 0x10489110 / 0x10489100 (time_GetElapsedTime, time_GetSimulationDelta,
			// time_GetRealTimeDelta, time_GetElapsedRealTime)
			float GetElapsedTime();
			float GetSimulationDelta();
			float GetRealTimeDelta();
			float GetElapsedRealTime();
			// 0x10489120: runs the scripts of the timers that are over
			void UpdateTimers(float delta);
			// 0x104891D0: frees every timer
			void ClearTimers();
			// 0x10489230 (scenario_SetMission) / 0x10489250
			void SetMission(unsigned int first, unsigned int second);
			void GetMission(unsigned int* first, unsigned int* second);
			// 0x104892D0 (stream_ConfirmMissionPackageSlotGroupEmpty)
			bool ConfirmMissionPackageSlotGroupEmpty();
			// 0x10489370 (stream_RestoreDynamicSlots) / 0x10489A20 (stream_CombineDynamicSlots)
			bool RestoreDynamicSlots();
			bool CombineDynamicSlots();
			// 0x10489410: loads the package a swap took out when the package that replaces it is ready
			void UpdatePackageSwap();
			// 0x10489980 (stream_PackageSwap)
			void PackageSwap(const char* oldName, const char* newName);
			// 0x1048A390: deactivates the object and queues the rest of its deactivation for the next frame
			void DeactivateObject(engine::GameObjectHandle handle);
			// 0x1048A320: the rest of an object's deactivation
			void FinishDeactivation(engine::GameObjectHandle handle);
			// 0x1048A490: finishes the queued deactivations of the earlier frames (all of them when asked)
			void FlushDeferred(bool all);

			ScenarioTimer timers[16];
			int nextTimerId;  // +0x1080
			float elapsedTime;  // +0x1084
			float simulationDelta;  // +0x1088
			float elapsedRealTime;  // +0x108C
			float realTimeDelta;  // +0x1090
			float heartbeatTime;  // +0x1094
			unsigned int missionFirst;  // +0x1098
			unsigned int missionSecond;  // +0x109C
			// The package swap: the package that is loaded when the one taken out is unloaded (+0x10A0) and the one
			// taken out (+0x10A4)
			engine::StreamPackage* swapIn;  // +0x10A0
			engine::StreamPackage* swapOut;  // +0x10A4
			// The dynamic slot group and what it was before the scripts combined its slots
			engine::StreamSlotGroup* dynamicGroup;  // +0x10A8
			int unknown10AC;
			core::Name<core::CaseSensitiveKey> savedGroupName;  // +0x10B0
			unsigned short savedPriority;  // +0x10B8
			bool savedShared;  // +0x10BA
			bool savedUnknown67;  // +0x10BB
			unsigned int savedSlotCount;  // +0x10BC
			int savedConfig[3];  // +0x10C0: the three words GetSlotHeapConfig answers
			bool slotsCombined;  // +0x10CC
			container::ArrayDynamicNew<DeferredDeactivation> deferred;  // +0x10D0
			int unknown10DC;
			int deferredHead;  // +0x10E0
			int deferredTail;  // +0x10E4
			int deferredCount;  // +0x10E8
		};

		// The instance (0x1126B8A8)
		extern ScenarioManager* gScenarioManager;
	}
}

#endif
