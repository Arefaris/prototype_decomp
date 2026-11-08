// proto::BaseHealthBehaviour (RTTI and reflection names; base proto::AdvancedHealthBehaviour): the advanced health with
// a damage scale for seven types of damage (the guns and the shells: the member names are original, the type each one
// scales is read off the damage switch of its message handler). Unit 0x102BA9F0 - 0x102BB1B0 (no assert path; the file
// name is a guess). Only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_BASEHEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_BASEHEALTHBEHAVIOUR_H

#include "code/proto/behaviours/advancedhealthbehaviour.h"

namespace proto
{
	class BaseHealthBehaviour : public AdvancedHealthBehaviour
	{
	public:
		// The damage scale of the seven types of damage the behaviour tells apart (all one by default)
		struct BaseAttackTypeConfiguration
		{
			// 0x102BAA70
			BaseAttackTypeConfiguration();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float damageScale25mm;  // +0x0
			float damageScale127mm;  // +0x4
			float damageScale120mm;  // +0x8 (scales the mortar shell)
			float damageScale30mm;  // +0xC
			float damageScale70mm;  // +0x10
			float damageScaleMissile;  // +0x14
			float damageScale50cal;  // +0x18
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		BaseAttackTypeConfiguration attackTypeDamageScale;  // +0x1A4
	};
}

#endif
