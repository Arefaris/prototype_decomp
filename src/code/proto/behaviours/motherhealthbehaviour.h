// proto::MotherHealthBehaviour (RTTI and reflection names; base proto::AdvancedHealthBehaviour): the health of the mother,
// which hands part of the damage it takes on (redirectMultiplier) and may keep the damage for itself (alwaysDoOwn). Unit
// 0x102BFF80 - 0x102C0B20 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed; only the member reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_MOTHERHEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_MOTHERHEALTHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/proto/behaviours/advancedhealthbehaviour.h"

namespace proto
{
	class MotherHealthBehaviour : public AdvancedHealthBehaviour
	{
	public:
		// 0x102BFF80
		static content::ClassInfo* GetClassInfo();
		// 0x102C02F0
		static content::MemberList* GetMembers();

		unsigned char unknown1A4[0x1B4 - 0x1A4];
		float redirectMultiplier;  // +0x1B4
		bool alwaysDoOwn;  // +0x1B8
	};
}

#endif
