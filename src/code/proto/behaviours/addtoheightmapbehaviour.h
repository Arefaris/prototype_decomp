// proto::AddToHeightmapBehaviour (RTTI and reflection names; base engine::Behaviour): puts a box around its object
// into the world's heightmap while the object stands still (updateRequired) and takes it out again when the object
// moves or goes away. Unit 0x103C5D80 - 0x103C6540 (no assert path; the file name is a guess). The reflected names are
// original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_ADDTOHEIGHTMAPBEHAVIOUR_H
#define PROTO_BEHAVIOURS_ADDTOHEIGHTMAPBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class AddToHeightmapBehaviour : public engine::Behaviour
	{
	public:
		// 0x103C5DC0
		explicit AddToHeightmapBehaviour(engine::GameObject* newOwner);
		// 0x103C62E0 (deleting destructor 0x103C64F0)
		virtual ~AddToHeightmapBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C5E00), 4 (0x103C5F90) and 6 (0x103C6300)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x103C5EC0: takes the box out of the heightmap again
		void Remove();

		math::Vector localCenter;  // +0xC
		float width;  // +0x18
		float length;  // +0x1C
		float height;  // +0x20
		bool updateRequired;  // +0x24
		bool registered;  // +0x25
	};
}

#endif
