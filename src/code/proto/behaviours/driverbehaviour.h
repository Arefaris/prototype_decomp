// proto::DriverBehaviour (RTTI and reflection names; base engine::Behaviour): who drives a vehicle (nobody, an AI
// driver in one of its states, the player) and the target class the vehicle gets while the player drives it. It tells
// the object's state machine the name of the driver state and the targeting what the vehicle is. Unit 0x103D6320 -
// 0x103D75D0 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; the
// update, the message handler, the destructor and the serialisation are left to the engine.
#ifndef PROTO_BEHAVIOURS_DRIVERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_DRIVERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	class DriverBehaviour : public engine::Behaviour
	{
	public:
		// The values the reflection lists are the first four
		enum DriverState
		{
			STATE_NO_DRIVER = 0,
			STATE_DRIVER_AI = 1,
			STATE_DRIVER_PLAYER = 2,
			STATE_DRIVER_AI_LANDED = 3,
			STATE_DRIVER_AI_LANDED_ENGINE_ON = 4,
			STATE_DRIVER_AI_TAKING_OFF = 5,
			STATE_DRIVER_AI_PLAYER_GUNNER = 6
		};

		// 0x103D6590
		explicit DriverBehaviour(engine::GameObject* newOwner);
		// 0x103D6E30 (deleting destructor 0x103D75D0)
		virtual ~DriverBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103D6C60), 3 (0x103D6CE0), 4 (0x103D6680) and 6 (0x103D6F80)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x103D6370: the states an AI drives in
		bool IsAiState(int state);
		// 0x103D63F0 (name guess)
		static bool IsNotPiloting(int state);
		// 0x103D68D0: the name of the driver state the state machine knows it by
		core::Name<core::CaseSensitiveKey> GetStateName(int state);
		// 0x103D69F0
		int GetStateFromName(core::Name<core::CaseSensitiveKey> name);
		// 0x103D6600: tells the targeting what the vehicle is (the class of the other driver kinds)
		void UpdateTargetClass();

		int state;  // +0xC
		core::Name<core::CaseSensitiveKey> stateName;  // +0x10
		int notDrivenByAITargetClass;  // +0x18
		bool unknown1C;
	};
}

#endif
