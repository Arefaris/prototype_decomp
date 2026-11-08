// proto::ButtonHintBehaviour (RTTI and reflection names; base engine::Behaviour): shows the button hints of its object
// through the interface (a flash image). It reflects no members. Unit 0x10061AA0 - 0x10063270 (no assert path; the file
// name is a guess). Only the reflection is reconstructed.
#ifndef PROTO_BUTTONHINTBEHAVIOUR_H
#define PROTO_BUTTONHINTBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/fightitems/motion/motionactionmessages.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	class ButtonHintBehaviour : public engine::Behaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x10063020)
		virtual void OnMessage(engine::Message* message);

		// The handlers of the messages (names guessed): 0x100628E0 forgets the hints, 0x10062940 adds one, 0x10062FB0
		// removes the hint of a scenario message, 0x100626D0 turns the hints on or off, 0x10062160 answers whether a hint
		// is showing
		void Reset();
		void AddHint(AddButtonHintMessage* message);
		void RemoveHint(const core::Name<core::CaseSensitiveKey>& scenarioMessage);
		void EnableHints(bool enable);
		void IsHintShowing(IsButtonHintShowingMessasge* message);
	};

}

#endif
