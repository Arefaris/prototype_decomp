// proto::PowerWheelBehaviour (RTTI and reflection names; base engine::Behaviour): keeps whether the power wheel of the
// interface is open (the power wheel messages, type 0x36, set it) and follows the controller while it is. It reflects
// no members. Unit 0x104C0100 - 0x104C02F0 (no assert path; the file name is a guess). The member names are guessed.
#ifndef PROTO_BEHAVIOURS_POWERWHEELBEHAVIOUR_H
#define PROTO_BEHAVIOURS_POWERWHEELBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// Opens or closes the power wheel (message type 0x36, id 0; the flag at +0xC) and its siblings
	struct SetPowerWheelActiveMessage : public engine::IntrusiveMessage
	{
		SetPowerWheelActiveMessage(bool newActive) : engine::IntrusiveMessage(0x36, 0), active(newActive)
		{
		}

		bool active;  // +0xC
	};

	class PowerWheelBehaviour : public engine::Behaviour
	{
	public:
		// 0x104C0140
		explicit PowerWheelBehaviour(engine::GameObject* newOwner);
		// 0x104C0180 (deleting destructor 0x104C01F0)
		virtual ~PowerWheelBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1, 4 and 6 (0x104C0190, 0x104C0250, 0x104C0220)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x104C01A0
		void SetActive(SetPowerWheelActiveMessage* message);

		bool active;  // +0xC
	};
}

#endif
