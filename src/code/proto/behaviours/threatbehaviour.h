// proto::ExpiryTimeBehaviour and proto::ThreatBehaviour (RTTI and reflection names; base engine::Behaviour): a
// behaviour that deactivates its object when its time has run out (reflected: expiryTime), and the threat that
// builds on it (message type 0x28: the threat is initialised from and reports to a message). Unit
// 0x10407440 - 0x10408070 (no assert path; the file name is a guess). The reflected names are original, the rest
// is guessed; only the construction, the reflection and the expiry are reconstructed.
#ifndef PROTO_BEHAVIOURS_THREATBEHAVIOUR_H
#define PROTO_BEHAVIOURS_THREATBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/fight/branch.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	class ExpiryTimeBehaviour : public engine::Behaviour
	{
	public:
		// 0x104075D0
		explicit ExpiryTimeBehaviour(engine::GameObject* newOwner);
		// 0x10407600 (the deleting destructor is 0x10407860)
		virtual ~ExpiryTimeBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10407610): starts the countdown
		virtual void Slot1();
		// vftable slot 3 (0x10407630): the countdown restarts when the behaviour becomes active
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x10407650): deactivates the object when the time has run out
		virtual void Update(float dt, unsigned short mask);

		float expiryTime;  // +0xC
		float timeLeft;  // +0x10
	};

	class ThreatBehaviour : public ExpiryTimeBehaviour
	{
	public:
		// 0x10407890
		explicit ThreatBehaviour(engine::GameObject* newOwner);
		// 0x10407900 (the deleting destructor is 0x10407C30)
		virtual ~ThreatBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x10407C60)
		virtual void OnMessage(engine::Message* message);

		int unknown14;  // +0x14
		core::Name<core::CaseSensitiveKey> unknown18;  // +0x18
		engine::HandleBase unknown20;  // +0x20
		engine::HandleBase unknown24;  // +0x24
		fight::BranchWatch branch;  // +0x28
		int unknown34;  // +0x34
	};
}

#endif
