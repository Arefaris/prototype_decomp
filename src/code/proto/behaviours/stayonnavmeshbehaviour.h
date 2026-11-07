// proto::StayOnNavmeshBehaviour (RTTI and reflection names; base engine::Behaviour): keeps the object on the navigation
// mesh of the city while it moves. Unit 0x103FA8F0 - 0x103FAFC0 (no assert path; the file name is a guess). Only the
// construction, the reflection and the small slots are reconstructed; the update that walks the mesh edges is left to the
// engine.
#ifndef PROTO_BEHAVIOURS_STAYONNAVMESHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_STAYONNAVMESHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	// The movement message (type 0x26, id 0x59) that switches the behaviour on or off (name guessed)
	struct StayOnNavmeshEnableMessage : public engine::Message
	{
		bool enabled;  // +0xC
	};

	class StayOnNavmeshBehaviour : public engine::Behaviour
	{
	public:
		// 0x103FA930
		explicit StayOnNavmeshBehaviour(engine::GameObject* newOwner);
		// 0x103FA980 (deleting destructor 0x103FAAC0)
		virtual ~StayOnNavmeshBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103FA990), 4 (0x103FAAF0, left to the engine) and 6 (0x103FA9B0)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		int unknownC;
		int unknown10;
		int unknown14;
		bool unknown18;
		bool enabled;  // +0x19
		float unknown1C;
		int unknown20;
	};
}

#endif
