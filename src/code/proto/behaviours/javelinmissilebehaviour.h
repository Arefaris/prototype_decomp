// proto::JavelinMissileBehaviour (RTTI and reflection names; base proto::MissileBehaviour): a missile that coasts for a
// while before its engine ignites and then falls and drags. Unit 0x10466E50 - 0x10467C00 (no assert path; the file
// name is a guess). The reflected names are original, the rest is guessed; the reflection, the construction and the
// destruction are reconstructed, the flight is left to the engine.
#ifndef PROTO_BEHAVIOURS_JAVELINMISSILEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_JAVELINMISSILEBEHAVIOUR_H

#include "code/proto/behaviours/missilebehaviour.h"

namespace proto
{
	class JavelinMissileBehaviour : public MissileBehaviour
	{
	public:
		// 0x10466F00
		explicit JavelinMissileBehaviour(engine::GameObject* newOwner);
		// 0x10466E90 (the deleting destructor is 0x10466FE0)
		virtual ~JavelinMissileBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10467500)
		virtual void Slot1();
		// vftable slot 6 (0x10467510) / 8 (0x10467580) / 14 (0x10467760), left to the engine
		virtual void OnMessage(engine::Message* message);
		virtual void Slot8(int a, int b, float c);
		virtual void Slot14(float dt);
		// vftable slot 16 (0x10466EB0)
		virtual void Slot16();

		float unknown108;
		float ignitionTime;  // +0x10C
		float unknown110;
		float dragForce;  // +0x114
		float verticalDragForce;  // +0x118
		float gravity;  // +0x11C
		math::Vector unknown120;
	};
}

#endif
