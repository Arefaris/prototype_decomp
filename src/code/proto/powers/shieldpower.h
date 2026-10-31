// proto::ShieldPower (RTTI and reflection names; base proto::Power): the shield Alex holds in front of him: a state
// machine (deploying, deployed, retracting, broken, healing) with a health that heals after a while and a game
// object (the shield) that follows it. Unit 0x1008AF10 - 0x1008C670 (no assert path; directory and file name are
// guesses). The reflected names are original, the rest is guessed.
#ifndef PROTO_POWERS_SHIELDPOWER_H
#define PROTO_POWERS_SHIELDPOWER_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/powers/power.h"

namespace proto
{
	class ShieldPower : public Power
	{
	public:
		// 0x1008B320
		ShieldPower();
		// 0x1008B400
		ShieldPower(const ShieldPower& other);
		// 0x1008B4D0
		virtual ~ShieldPower();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 7 (0x1008B500), 8 (0x1008AFB0), 9 (0x1008C380), 10 (0x1008BDA0), 11 (0x1008C240), 12 (0x1008B0D0),
		// 13 (0x1008B040) and 14 (0x1008B0B0)
		virtual Power* Clone();
		virtual void Slot8();
		virtual void Slot9(float unknown);
		virtual void Slot10(float dt);
		virtual void Slot11(engine::Message* message);
		virtual float Slot12();
		virtual void Slot13();
		virtual bool GetMessageMask(unsigned int* mask);

		int state;  // +0xC
		core::Name<core::CaseSensitiveKey> shieldJoint;  // +0x10
		int jointIndex;  // +0x18
		float unknown1C;  // +0x1C
		float deployedScale;  // +0x20
		float deploySpeed;  // +0x24
		float retractSpeed;  // +0x28
		float health;  // +0x2C
		float currentHealth;  // +0x30
		float healingTime;  // +0x34
		float unknown38;  // +0x38
		float unknown3C;  // +0x3C
		float undamagedTimeBeforeHealing;  // +0x40
		float unknown44;  // +0x44
		float autoHealFromBrokenTime;  // +0x48
		int unknown4C;  // +0x4C
		core::Name<core::CaseSensitiveKey> gameObjectTemplate;  // +0x50
		core::Name<core::CaseSensitiveKey> grabSlot;  // +0x58
		engine::GameObject* shieldObject;  // +0x60
		engine::GameObjectHandle shieldHandle;  // +0x64
	};
}

#endif
