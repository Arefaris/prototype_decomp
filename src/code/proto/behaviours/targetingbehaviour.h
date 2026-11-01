// proto::TargetingBehaviour (RTTI and reflection names; base engine::Behaviour): keeps the object's current target and
// answers the target messages (type 0x20: the target is asked for with id 0 and set with id 2). The base of the
// automatic and the lock-on targeting behaviours. Unit 0x102B4500 - 0x102B4740 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_TARGETINGBEHAVIOUR_H
#define PROTO_BEHAVIOURS_TARGETINGBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"

namespace proto
{
	class GetTargetMessage;
	class SetTargetMessage;

	class TargetingBehaviour : public engine::Behaviour
	{
	public:
		// 0x102B4540
		explicit TargetingBehaviour(engine::GameObject* newOwner);
		// 0x102B4590 (the deleting destructor is 0x102B4640)
		virtual ~TargetingBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x102A83D0): nothing to advance
		virtual void Update(float dt, unsigned short mask)
		{
		}
		// vftable slot 6 (0x102B4670)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x102B45A0): no target
		virtual void ClearTarget();
		// vftable slot 9 (0x102B45C0)
		virtual void SetTarget(const engine::GameObjectHandle* newTarget);

		// 0x102B45D0: the message carries the target out
		void GetTarget(GetTargetMessage* message);
		// 0x102B45E0: sets the target the message names
		void OnSetTarget(SetTargetMessage* message);

		engine::GameObjectHandle target;  // +0xC
	};
}

#endif
