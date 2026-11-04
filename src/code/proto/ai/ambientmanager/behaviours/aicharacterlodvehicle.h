// proto::BaseLODVehicle and proto::AICharacterLODVehicle (RTTI names): the interface the level-of-detail code uses to
// drive a vehicle, and its form for the vehicles a character drives (a pointer to the ambient vehicle behaviour it
// stands for). Unit 0x10440A00 - 0x10441600 (no assert path; the file name is a guess); only the construction, the
// attachment and the small slots are reconstructed, the update is left to the engine.
#ifndef PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_AICHARACTERLODVEHICLE_H
#define PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_AICHARACTERLODVEHICLE_H

#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

namespace proto
{
	// The interface (RTTI proto::BaseLODVehicle; all eight slots are pure)
	class BaseLODVehicle
	{
	public:
		// 0x104409F0 (out of line in the engine, inline here)
		BaseLODVehicle()
		{
		}
		virtual void Slot0() = 0;
		virtual void Slot1(int a) = 0;
		virtual void Slot2(int a) = 0;
		virtual void Slot3() = 0;
		virtual bool Slot4() = 0;
		virtual bool Slot5() = 0;
		virtual void Slot6() = 0;
		virtual void Slot7() = 0;
	};

	class AICharacterLODVehicle : public BaseLODVehicle
	{
	public:
		// 0x10440B50
		AICharacterLODVehicle();
		// 0x10440B70
		~AICharacterLODVehicle();

		// vftable slots 0 (0x10440C10) and 1 (0x10441200), left to the engine
		virtual void Slot0();
		virtual void Slot1(int a);
		// vftable slots 2 - 7 (0x10440A30, 0x10440A40, 0x10440A50, 0x10440A60, 0x10440A70, 0x10440A80)
		virtual void Slot2(int a);
		virtual void Slot3();
		virtual bool Slot4();
		virtual bool Slot5();
		virtual void Slot6();
		virtual void Slot7();

		// 0x10440A00: stands for a vehicle; 0x10440A20: stands for none
		void Attach(VehicleBehaviourAmbient* newVehicle);
		void Detach();

		engine::GameObject* unknown4;  // the vehicle's owner
		VehicleBehaviourAmbient* vehicle;  // +8
		bool unknownC;
	};
}

#endif
