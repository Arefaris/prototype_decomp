// proto::TestWalkBehaviour (RTTI and reflection names; base engine::Behaviour): a debugging behaviour that walks its
// object towards a point (message type 0x26: id 0 sets the point to walk to, 0x16 hands out the stored walk settings,
// 0x17 stores them). Reflected: speed. Unit 0x10402BB0 - 0x10403000 (no assert path; the file name is a guess). The
// reflected name is original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_TESTWALKBEHAVIOUR_H
#define PROTO_BEHAVIOURS_TESTWALKBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/math/vector.h"

namespace proto
{
	class TestWalkBehaviour : public engine::Behaviour
	{
	public:
		// The walk settings the messages 0x16 and 0x17 exchange (0x1C bytes; member names guessed)
		struct WalkSettings
		{
			math::Vector start;
			math::Vector end;
			int mode;
		};

		// 0x10402BF0
		explicit TestWalkBehaviour(engine::GameObject* newOwner);
		// 0x10402C90 (the deleting destructor is 0x10402D00)
		virtual ~TestWalkBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10402CB0)
		virtual void Slot1();
		// vftable slot 4 (0x10402DD0): walks towards the point
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10402D30)
		virtual void OnMessage(engine::Message* message);

		float targetX;  // +0xC
		float targetY;  // +0x10
		float targetZ;  // +0x14
		bool walking;  // +0x18
		bool settingsStored;  // +0x19
		float speed;  // +0x1C
		WalkSettings settings;  // +0x20
	};
}

#endif
