// proto::HelicopterIntentionBehaviour (RTTI and reflection names; base engine::Behaviour): the intention of a helicopter
// (driver, gunner and grab). It reflects no members. Unit 0x1006F8E0 - 0x10070B20 (no assert path; the file name is a
// guess). Only the reflection is reconstructed.
#ifndef PROTO_HELICOPTERINTENTIONBEHAVIOUR_H
#define PROTO_HELICOPTERINTENTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class HelicopterIntentionBehaviour : public engine::Behaviour
	{
	public:
		// 0x1006FAD0
		explicit HelicopterIntentionBehaviour(engine::GameObject* newOwner);
		// 0x1006FB50 (deleting destructor 0x1006FD30)
		virtual ~HelicopterIntentionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x1006FB60), 4 (0x100700D0) and 6 (0x1006FDE0)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		math::Vector unknownC;
		bool unknown18;
	};

}

#endif
