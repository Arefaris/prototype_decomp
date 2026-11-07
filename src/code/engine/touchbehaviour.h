// engine::TouchBehaviour (RTTI and reflection name; base engine::Behaviour): a trigger volume that follows its owner
// ("volume"). Slot 0 makes a small sphere volume when the object carries none, slot 1 sets the volume up (the owner is
// what it tests against, it follows the transform and belongs to the owner), the volume is added to and removed from
// the world with the behaviour's activity, and its transform follows the owner's. Unit 0x10929FF0 - 0x1092A440 (no
// assert path; the directory and file name are guesses). The reflected name is original; the rest is guessed.
#ifndef ENGINE_TOUCHBEHAVIOUR_H
#define ENGINE_TOUCHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/trigger/volume.h"

namespace engine
{
	class TouchBehaviour : public Behaviour
	{
	public:
		// 0x1092A030
		explicit TouchBehaviour(GameObject* newOwner);
		// 0x1092A2F0 (deleting destructor 0x1092A420)
		virtual ~TouchBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 0 (0x1092A070): makes the volume when the object has none
		virtual void Slot0();
		// vftable slot 1 (0x1092A140): sets the volume up
		virtual void Slot1();
		// vftable slot 3 (0x1092A1A0): adds the volume to the world or removes it
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x1092A230): moves the volume to the owner's transform
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1092A250)
		virtual void OnMessage(Message* message);

		trigger::Volume* volume;  // +0xC
	};
}

#endif
