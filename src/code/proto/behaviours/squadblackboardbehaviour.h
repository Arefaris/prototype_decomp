// proto::SquadBlackboardBehaviour (RTTI and reflection names; base engine::Behaviour): the shared memory of a squad,
// a list of 25 points and the object they belong to. Unit 0x103F83B0 - 0x103F8A60 (no assert path; the file name is a
// guess). The reflected class has no members; only the construction, the reflection and the small slots are
// reconstructed.
#ifndef PROTO_BEHAVIOURS_SQUADBLACKBOARDBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SQUADBLACKBOARDBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	// A list of up to 25 points kept in the object (0x12C bytes of points and the end of the list)
	struct PointList25
	{
		PointList25() : end(points)
		{
		}
		~PointList25()
		{
			Clear();
		}
		void Clear()
		{
			end = points;
		}

		math::Vector points[25];
		math::Vector* end;
	};

	class SquadBlackboardBehaviour : public engine::Behaviour
	{
	public:
		// 0x103F86E0
		explicit SquadBlackboardBehaviour(engine::GameObject* newOwner);
		// 0x103F8790 (deleting destructor 0x103F8920)
		virtual ~SquadBlackboardBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103F87B0), 4 (0x103F83F0) and 6 (0x103F8950, left to the engine)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x103F85D0: forgets the points and the object
		void Reset();

		PointList25 points;  // +0xC
		math::Vector unknown13C;
		engine::GameObjectHandle unknown148;
		float unknown14C;
		int unknown150;
	};
}

#endif
