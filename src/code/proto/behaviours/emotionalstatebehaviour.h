// proto::EmotionalStateBehaviour (RTTI and reflection names; base engine::Behaviour): remembers the emotional state
// of a character (the name of the state, "Idle" until the fight items set another one) and answers the messages that
// read or write it. Unit 0x103D7600 - 0x103D7870 (no assert path; the file name is a guess). The reflected name is
// original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_EMOTIONALSTATEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_EMOTIONALSTATEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	// The message of type 0x28 that reads (id 0, the behaviour's state goes into the message) or writes (id 1) the state
	struct EmotionalStateMessage : public engine::Message
	{
		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};

	class EmotionalStateBehaviour : public engine::Behaviour
	{
	public:
		// 0x103D76A0
		explicit EmotionalStateBehaviour(engine::GameObject* newOwner);
		// 0x103D7700 (deleting destructor 0x103D77C0)
		virtual ~EmotionalStateBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103D7640), 4 (0x103D7710) and 6 (0x103D77F0)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x103D7720: back to the idle state
		void Reset();

		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};
}

#endif
