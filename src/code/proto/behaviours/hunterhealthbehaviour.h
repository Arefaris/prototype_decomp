// proto::HunterHealthBehaviour (RTTI and reflection names; base proto::AdvancedHealthBehaviour): the health of the hunter.
// A table gives the health an attack of each type cannot take the hunter below (minHealthOverride: the missile and the
// missile explosion are reflected), and a damage above damageOverrideThreshold leaves it damageOverrideMinHealth.
// Unit 0x102BF870 - 0x102BFF80 (no assert path; the file name is a guess). The reflected names are original, the rest
// is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_HUNTERHEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_HUNTERHEALTHBEHAVIOUR_H

#include "code/proto/behaviours/advancedhealthbehaviour.h"

namespace proto
{
	class HunterHealthBehaviour : public AdvancedHealthBehaviour
	{
	public:
		enum
		{
			ATTACK_TYPE_COUNT = 34
		};

		// The least health an attack of each type leaves (-1: no limit), in the order of proto::AttackType
		struct MinHealthOverride
		{
			// 0x102BF8F0
			MinHealthOverride();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float minHealth[ATTACK_TYPE_COUNT];  // +0x0
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		MinHealthOverride minHealthOverride;  // +0x1A4
		float damageOverrideThreshold;  // +0x22C
		float damageOverrideMinHealth;  // +0x230
	};
}

#endif
