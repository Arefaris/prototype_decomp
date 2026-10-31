// proto::TendrilBehaviour (RTTI and reflection names; base engine::Behaviour): a tendril of the infection. It reflects no
// members. Unit 0x10078480 - 0x10078A70 (no assert path; the file name is a guess). Only the reflection is reconstructed.
#ifndef PROTO_TENDRILBEHAVIOUR_H
#define PROTO_TENDRILBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class TendrilBehaviour : public engine::Behaviour
	{
	public:
		// 0x100784C0
		explicit TendrilBehaviour(engine::GameObject* newOwner);
		// 0x10078940 (deleting destructor 0x100789C0)
		virtual ~TendrilBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 4 (0x10078540) and 6 (0x10078870)
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		void* firstAction;  // +0xC
	};

}

#endif
