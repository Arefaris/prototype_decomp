// proto::RandomDeadPedBehaviour (RTTI and reflection names; base engine::Behaviour): dresses a dead pedestrian's
// object with a randomly picked drawable of the ambient manager. No members of its own. Unit
// 0x10432ED0 - 0x10438940, scattered (no assert path; the file name is a guess). The reflected name is original, the
// rest is guessed; only the construction and the reflection are reconstructed.
#ifndef PROTO_BEHAVIOURS_RANDOMDEADPEDBEHAVIOUR_H
#define PROTO_BEHAVIOURS_RANDOMDEADPEDBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace proto
{
	class RandomDeadPedBehaviour : public engine::Behaviour
	{
	public:
		// 0x10433150
		explicit RandomDeadPedBehaviour(engine::GameObject* newOwner);
		// 0x10433170 (the deleting destructor is 0x10434330)
		virtual ~RandomDeadPedBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1043B4E0): picks the drawable
		virtual void Slot1();
	};
}

#endif
