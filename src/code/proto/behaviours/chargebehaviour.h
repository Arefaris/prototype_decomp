// proto::ChargeBehaviour (RTTI and reflection names; base engine::Behaviour): the charge of a game object, a value
// that the charge messages (type 0x1C) add to, set, read and eat. It remembers the type of the charge (1 and 2 are
// the two the smart hints know) and tells the fight system of its owner when the charge crosses full or empty.
// Unit 0x10064370 - 0x10064A60 (no assert path; the file name is a guess). The reflected member name is original,
// the rest is guessed.
#ifndef PROTO_BEHAVIOURS_CHARGEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_CHARGEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	class ChargeMessage;

	class ChargeBehaviour : public engine::Behaviour
	{
	public:
		// 0x10064420
		explicit ChargeBehaviour(engine::GameObject* newOwner);
		// 0x10064470 (deleting destructor 0x100646C0)
		virtual ~ChargeBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x10064770)
		virtual void OnMessage(engine::Message* message);

		// 0x10064630: the charge starts again
		void Reset();
		// 0x10064480 (id 0) / 0x100646F0 (id 1) / 0x10064580 (id 2) / 0x100645B0 (id 3)
		void Add(ChargeMessage* message);
		void Eat(ChargeMessage* message);
		void Get(ChargeMessage* message);
		void Set(ChargeMessage* message);

		float charge;  // +0xC
		int chargeType;  // +0x10
	};
}

#endif
