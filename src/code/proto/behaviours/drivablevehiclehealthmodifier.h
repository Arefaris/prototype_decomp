// proto::DrivableVehicleHealthModifierBehaviour (RTTI and reflection names; base engine::Behaviour) and its data classes
// (RTTI and reflection names): the damage the player takes in each state of a vehicle, the parameters of the modifier and
// the mapping of a weapon profile. The behaviour scales the damage a vehicle takes by what the player has unlocked
// while the player drives it, and makes the vehicle undamageable for a time. Unit 0x102BB200 - 0x102BD600 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_DRIVABLEVEHICLEHEALTHMODIFIER_H
#define PROTO_BEHAVIOURS_DRIVABLEVEHICLEHEALTHMODIFIER_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/proto/unlockables.h"

namespace proto
{
	struct AmmoProfileBase;
	struct WeaponUserProfile;

	// The damage the player takes while the vehicle is in a state (RTTI proto::DamageToPlayerPerState; 0x10 bytes)
	struct __declspec(align(8)) DamageToPlayerPerState
	{
		// 0x102BB760
		DamageToPlayerPerState();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> state;  // +0x0
		float damage;  // +0x8
	};

	// RTTI proto::WeaponProfileMapping (0x10 bytes): the profiles a weapon of the player maps to
	struct __declspec(align(8)) WeaponProfileMapping
	{
		// 0x102BB7C0
		WeaponProfileMapping();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> weapon;  // +0x0
		WeaponUserProfile* userProfile;  // +0x8
		AmmoProfileBase* ammoProfile;  // +0xC
	};

	// RTTI proto::DrivableVehicleHealthModifierParams (0x38 bytes)
	struct __declspec(align(8)) DrivableVehicleHealthModifierParams
	{
		typedef container::ArrayDynamic<DamageToPlayerPerState, container::AllocatorNew> StateArray;

		// 0x102BD220
		DrivableVehicleHealthModifierParams();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool immuneWhilePlayerAttached;  // +0x0
		float timeImmuneWithPlayerDriver;  // +0x4
		float minHealthWithPlayerDriver;  // +0x8
		bool giveMinHealthEachEntrance;  // +0xC
		core::Name<core::CaseSensitiveKey> driverGrabslotName;  // +0x10
		Unlockable playerDamageScaleUnlockableFirst;  // +0x18
		Unlockable playerDamageScaleUnlockableLast;  // +0x1C
		float playerDamageScaleMin;  // +0x20
		float playerDamageScaleMax;  // +0x24
		StateArray damageToPlayerPerState;  // +0x28
		int unknown34;  // behind the array: its allocator word
	};

	class DrivableVehicleHealthModifierBehaviour : public engine::Behaviour
	{
	public:
		// 0x102BD480 (the destructor is 0x102BD290, the deleting destructor 0x102BD500)
		explicit DrivableVehicleHealthModifierBehaviour(engine::GameObject* newOwner);
		virtual ~DrivableVehicleHealthModifierBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 4 and 6 (0x102BB3B0, 0x102BD2D0)
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x102BB300: tells the vehicle how much damage it takes (by the number of unlockables the player has)
		void UpdateDamageScale();
		// 0x102BBE60 / 0x102BCE10 (not reconstructed; names guessed): the messages of type 0xB with id 3 and of type 0x1F
		// with id 0xE
		void OnFightEvent(engine::Message* message);
		void OnGrabbedSlot(engine::Message* message);

		bool unknownC;  // +0xC
		float unknown10;  // +0x10
		bool unknown14;  // +0x14
		bool playerDriving;  // +0x15
		int unlockedCount;  // +0x18
		DrivableVehicleHealthModifierParams params;  // +0x20
		container::ArrayCDynamic<WeaponProfileMapping, 6> playerWeaponProfiles;  // +0x58
	};
}

#endif
