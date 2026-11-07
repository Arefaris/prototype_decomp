// proto::PrototypeHealthBehaviour (RTTI and reflection names; base proto::AdvancedHealthBehaviour, and engine::DBObserver
// at +0x1A4): the health of the player: the health gained from unlockables, the regeneration and its unlockable limits,
// the adrenaline surge and the critical mass. Unit 0x102C2830 - 0x102C4890 (no assert path; the file name is a guess).
// The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_PROTOTYPEHEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_PROTOTYPEHEALTHBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/proto/behaviours/advancedhealthbehaviour.h"
#include "code/proto/unlockables.h"

namespace proto
{
	class PrototypeHealthBehaviour : public AdvancedHealthBehaviour
	{
	public:
		// The health an unlockable adds (RTTI proto::PrototypeHealthBehaviour::HealthBehaviourUnlockable)
		struct HealthBehaviourUnlockable
		{
			// 0x102C2830
			static content::ClassInfo* GetClassInfo();
			// 0x102C3AA0
			static content::MemberList* GetMembers();

			// 0x102C28B0
			HealthBehaviourUnlockable();

			Unlockable unlockable;  // +0
			float healthAdded;  // +4
			float criticalMassHealthAdded;  // +8
		};

		typedef container::ArrayDynamic<HealthBehaviourUnlockable, container::AllocatorNew> UnlockableArray;

		// 0x102C2870
		static content::ClassInfo* GetClassInfo();
		// 0x102C4030
		static content::MemberList* GetMembers();

		int unknown1A4;  // the engine::DBObserver subobject's vftable
		UnlockableArray unlockables;  // +0x1A8
		int unknown1B4;
		float devastatorHealthCost;  // +0x1B8
		unsigned char unknown1BC[0x1CC - 0x1BC];
		float regenRateMax;  // +0x1CC
		Unlockable regenRateUnlockableFirst;  // +0x1D0
		Unlockable regenRateUnlockableLast;  // +0x1D4
		float regenTimeWithNoDamageMax;  // +0x1D8
		Unlockable regenTimeWithNoDamageUnlockableFirst;  // +0x1DC
		Unlockable regenTimeWithNoDamageUnlockableLast;  // +0x1E0
		float consumeHealthMultiplier;  // +0x1E4
		Unlockable consumeHealthMultiplierUnlockableFirst;  // +0x1E8
		Unlockable consumeHealthMultiplierUnlockableLast;  // +0x1EC
		unsigned char unknown1F0[0x1F4 - 0x1F0];
		float adrenalineSurgeThresholdHealth;  // +0x1F4
		float adrenalineSurgeHealthOnEntry;  // +0x1F8
		float adrenalineSurgeUndamageableTime;  // +0x1FC
		unsigned char unknown200[0x208 - 0x200];
		float minTimeBetweenAdrenalineDevastators;  // +0x208
		float lowHealthThreshold;  // +0x20C
		Unlockable adrenalineSurgeUnlockable;  // +0x210
		unsigned char unknown214[0x218 - 0x214];
		float defaultHealthPercentage;  // +0x218
		float criticalMassHealthGainFactor;  // +0x21C
		float criticalMassExitHealthLoss;  // +0x220
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::PrototypeHealthBehaviour::HealthBehaviourUnlockable>
	{
		enum
		{
			value = 3
		};
	};
}

#endif
