// proto::BombBehaviour (RTTI and reflection names; base proto::MissileBehaviour): a missile that slows down after a
// while and falls straight down. Unit 0x10464760 - 0x10464EF0 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed; the reflection, the construction, the destruction and the small
// handlers are reconstructed, the flight is left to the engine.
#ifndef PROTO_BEHAVIOURS_BOMBBEHAVIOUR_H
#define PROTO_BEHAVIOURS_BOMBBEHAVIOUR_H

#include "code/proto/behaviours/missilebehaviour.h"

namespace proto
{
	class BombBehaviour : public MissileBehaviour
	{
	public:
		// 0x10464880
		explicit BombBehaviour(engine::GameObject* newOwner);
		// 0x104647A0 (the deleting destructor is 0x10464920)
		virtual ~BombBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10464950) / 17 (0x104649F0) / 14 (0x10464C40), left to the engine
		virtual void Slot1();
		virtual void Slot14(float dt);
		virtual void Slot17(int a);
		// vftable slot 6 (0x104647F0)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x10464820): the bomb starts straight down
		virtual void Slot8(int a, int b, float c);

		// 0x104647C0: stops the missile and forgets the direction
		void Reset();

		float timeToSlowDown;  // +0x108
		float slowDownScale;  // +0x10C
		float unknown110;
		float unknown114;
	};
}

#endif
