// proto::AIFlyingPatrolBehaviour (RTTI and reflection names; base engine::Behaviour): a flying patrol that steers its
// object between points (message type 0x26). Reflected: radius, startVelocity and brakeAtGoal. Unit
// 0x1042D3B0 - 0x1042E250 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed; only the construction and the reflection are reconstructed.
#ifndef PROTO_BEHAVIOURS_AIFLYINGPATROLBEHAVIOUR_H
#define PROTO_BEHAVIOURS_AIFLYINGPATROLBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace proto
{
	struct ActivateVehicleMovementBehaviourMessage;

	class AIFlyingPatrolBehaviour : public engine::Behaviour
	{
	public:
		// 0x1042D3F0
		explicit AIFlyingPatrolBehaviour(engine::GameObject* newOwner);
		// 0x1042D470 (the deleting destructor is 0x1042D640)
		virtual ~AIFlyingPatrolBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1042E1F0)
		virtual void Slot1();
		// vftable slot 4 (0x1042E080)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1042E250)
		virtual void OnMessage(engine::Message* message);

		// 0x1042D670 / 0x1042DC30: the two forms of the update (steering with and without a goal; names guessed)
		void UpdateWithGoal(float dt);
		void UpdateWithoutGoal(float dt);
		// 0x1042E0D0: lets the patrol stop where it is
		void Stop();
		// 0x1042D480: whether the object has reached its destination (the form depends on the level of detail)
		bool HasArrived();
		// 0x1042E210: starts or stops the patrol on the message that activates the movement
		void OnActivate(ActivateVehicleMovementBehaviourMessage* message);

		bool active;  // +0xC
		unsigned char unknownD[3];
		float unknown10;  // +0x10
		bool unknown14;  // +0x14
		float radius;  // +0x18
		float startVelocity;  // +0x1C
		bool brakeAtGoal;  // +0x20
		unsigned char unknown21[0x2C - 0x21];
		float unknown2C;  // +0x2C
		float unknown30;  // +0x30
		float unknown34;  // +0x34
		int unknown38;  // +0x38
		bool unknown3C;  // +0x3C
	};
}

#endif
