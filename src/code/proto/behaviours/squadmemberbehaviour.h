// proto::SquadMemberBehaviour (RTTI and reflection names; base engine::Behaviour): the part of an object that belongs
// to a squad, the handle of its commander. Unit 0x103F9DD0 - 0x103FA3D0 (no assert path; the file name is a guess).
// The reflected class has no members; the message handler is left to the engine.
#ifndef PROTO_BEHAVIOURS_SQUADMEMBERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SQUADMEMBERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"

namespace proto
{
	class SquadMemberBehaviour : public engine::Behaviour
	{
	public:
		// 0x103F9E10
		explicit SquadMemberBehaviour(engine::GameObject* newOwner);
		// 0x103F9E80 (deleting destructor 0x103F9F90)
		virtual ~SquadMemberBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103F9E90), 4 (0x103F9EA0) and 6 (0x103FA1C0, left to the engine)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		engine::GameObjectHandle commander;  // +0xC
	};
}

#endif
