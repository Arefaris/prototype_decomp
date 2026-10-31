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

namespace proto
{
	class ButtonHintBehaviour : public engine::Behaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

	};

}

#endif
