// proto::VehicleBehaviourAICharacter (RTTI and reflection names; base proto::VehicleBehaviour): the vehicle a
// character drives. It stands for itself in the level-of-detail code through an AICharacterLODVehicle it holds. Unit
// 0x10444170 - 0x10445000 (no assert path; the file name is a guess); the construction, the destruction, the
// reflection and the small slots are reconstructed, the driving is left to the engine.
#ifndef PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAICHARACTER_H
#define PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAICHARACTER_H

#include "code/proto/ai/ambientmanager/behaviours/aicharacterlodvehicle.h"

namespace proto
{
	class VehicleBehaviourAICharacter : public VehicleBehaviour
	{
	public:
		// 0x10444EF0
		explicit VehicleBehaviourAICharacter(engine::GameObject* newOwner);
		// 0x10444D00 (the deleting destructor is 0x10444F50)
		virtual ~VehicleBehaviourAICharacter();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x104441B0) / 3 (0x10444200); 4 (0x10444420) and 6 (0x10444F80) are left to the engine
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		unsigned char unknownA8[0xB8 - 0xA8];
		AICharacterLODVehicle lod;  // +0xB8
		float unknownC8;
		float unknownCC;
	};
}

#endif
