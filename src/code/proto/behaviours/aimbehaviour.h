// proto::AimBehaviour (RTTI and reflection names; base engine::Behaviour) and its two kinds proto::TankAimBehaviour
// and proto::HelicopterAimBehaviour: keep the aim of an object, the primary and secondary target with the point and
// direction each one aims at, and hand the point to the movement of the object (it turns its turret or its nose).
// Unit 0x103C65A0 - 0x103C78D0 (no assert path; the file name is a guess). Only the reflection, the construction and
// the small slots are reconstructed; the slots that build a direction from the target are left to the engine.
#ifndef PROTO_BEHAVIOURS_AIMBEHAVIOUR_H
#define PROTO_BEHAVIOURS_AIMBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"

namespace proto
{
	// What the object aims at (0x24 bytes; the guessed names follow the users)
	struct AimInfo
	{
		AimInfo() : unknown0(0), unknown4(0), unknown8(math::kZeroVector), flag(false), unknown18(math::kZeroVector)
		{
		}

		int unknown0;
		int unknown4;
		math::Vector unknown8;
		bool flag;  // +0x14
		math::Vector unknown18;
	};

	// The query / reset messages the behaviour answers (type 0x26 id 0x57 / 0x58, type 0x2F id 2)
	struct AimSlotMessage : public engine::Message
	{
		AimInfo* slot;  // +0xC
		bool secondary;  // +0x10
	};

	struct AimEnableMessage : public engine::Message
	{
		bool enabled;  // +0xC
	};

	class AimBehaviour : public engine::Behaviour
	{
	public:
		// 0x103C6670
		explicit AimBehaviour(engine::GameObject* newOwner);
		// 0x103C67A0 (deleting destructor 0x103C7030)
		virtual ~AimBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C67B0), 4 (0x103C7850) and 6 (0x103C67C0)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);
		// vftable slots 8 - 15 (0x103C68A0, 0x103C6960, 0x103C7060, 0x103C7120, 0x103C69A0, 0x103C69E0, 0x103C6AB0,
		// 0x103C6AD0): the aim at a target; the ones that take the target apart are left to the engine
		virtual void Slot8(int a, int b, int c);
		virtual void Slot9(AimInfo* info, int flags);
		// 10 and 11: aim at the position of the target object plus the offset of the info
		virtual void Slot10(AimInfo* info, engine::GameObject* target, int unused);
		virtual void Slot11(AimInfo* info, engine::GameObject* target, int unused);
		virtual void Slot12(AimInfo* info, int flags);
		virtual void Slot13(AimInfo* info, int flags);
		virtual void Slot14(AimInfo* info, int flags);
		virtual void Slot15(AimInfo* info, int flags, math::Vector* point);

		// 0x103C76C0: the aim without a message (called by Update)
		void Unknown103C76C0(float dt);

		bool unknownC;
		AimInfo primary;  // +0x10
		AimInfo secondary;  // +0x34
	};

	class TankAimBehaviour : public AimBehaviour
	{
	public:
		// 0x103C6AF0
		explicit TankAimBehaviour(engine::GameObject* newOwner);
		// 0x103C6B10 (deleting destructor 0x103C71E0)
		virtual ~TankAimBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C6B20), 8 (0x103C7210), 9 (0x103C6B30), 13 (0x103C6BA0), 14 (0x103C6C90), 15 (0x103C6CF0)
		virtual void Slot1();
		virtual void Slot8(int a, int b, int c);
		virtual void Slot9(AimInfo* info, int flags);
		virtual void Slot13(AimInfo* info, int flags);
		virtual void Slot14(AimInfo* info, int flags);
		virtual void Slot15(AimInfo* info, int flags, math::Vector* point);
	};

	class HelicopterAimBehaviour : public AimBehaviour
	{
	public:
		// 0x103C6D40
		explicit HelicopterAimBehaviour(engine::GameObject* newOwner);
		// 0x103C6D60 (deleting destructor 0x103C7370)
		virtual ~HelicopterAimBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C6D70), 8 (0x103C6D80), 9 (0x103C6E40), 13 (0x103C6E50), 14 (0x103C6F50), 15 (0x103C6F70)
		virtual void Slot1();
		virtual void Slot8(int a, int b, int c);
		virtual void Slot9(AimInfo* info, int flags);
		virtual void Slot13(AimInfo* info, int flags);
		virtual void Slot14(AimInfo* info, int flags);
		virtual void Slot15(AimInfo* info, int flags, math::Vector* point);
	};
}

#endif
