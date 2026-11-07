// proto::WeaponBehaviour, proto::FreeAimingBehaviour (RTTI and reflection names; base engine::Behaviour) and the load
// objects around them: proto::AmmoProfileBase (the numbers every kind of ammunition shares: clip, fire rate, damage,
// speed, range and the bullet tracer), proto::WeaponUserProfile (how the one who holds the weapon aims: accuracy,
// angle limits and heat). Unit 0x1046FC30 - 0x10474810 (no assert path; the file name is a guess). The reflected
// names are original, the rest is guessed; the reflection, the construction, the destruction and the small accessors
// are reconstructed, the aiming and shooting code is left to the engine.
#ifndef PROTO_BEHAVIOURS_WEAPONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_WEAPONBEHAVIOUR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/unlockables.h"

namespace proto
{
	struct BulletTracerProfile;
	struct WeaponUserProfile;

	// The enumerations the profiles reflect (their values are not recovered here; the names come from the EnumInfo of
	// each: proto::DamageType, proto::AttackType and proto::ShootLookAtPossibilities, whose values are in the
	// weapon unit)
	enum DamageType
	{
		DAMAGETYPE_UNKNOWN = 0
	};
	enum AttackType
	{
		ATTACKTYPE_UNKNOWN = 0
	};
	enum ShootLookAtPossibilities
	{
		SHOOTLOOKAT_UNKNOWN = 0
	};

	// The table of the progress flags (the global at 0x112738B8; another unit)
	class UnlockTable
	{
	public:
		// 0x10579600: how many of the unlockables from first to last are unlocked
		int CountUnlocked(int first, int last);
	};
	extern UnlockTable* gUnlockTable;

	// What the ammunition of a weapon is made of (RTTI proto::AmmoProfileBase; 0x68 bytes)
	struct AmmoProfileBase : public content::MetaLoadObject
	{
		// 0x104707B0
		AmmoProfileBase();
		// 0x10470870 (the deleting destructor is 0x10471AF0)
		virtual ~AmmoProfileBase();
		// vftable slot 6 (0x104708A0)
		virtual void SetName(const content::ObjectName& newName);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1046FDA0: the clip capacity with the unlockables added
		int GetClipCapacity() const;
		// 0x1046FDE0: the damage multiplier the unlockables give
		float GetDamageMultiplier() const;
		// 0x1046FE60: the damage of a hit on the player (true) or on anybody else, with the unlockables
		float GetDamage(bool onPlayer) const;

		BulletTracerProfile* tracerParams;  // +8
		int unknownC;
		content::ObjectName name;  // +0x10
		int clipCapacity;  // +0x18
		int clipCapacityUnlockableAdd;  // +0x1C
		int clipCapacityUnlockableFirst;  // +0x20
		int clipCapacityUnlockableLast;  // +0x24
		float fireRate;  // +0x28
		float offCameraFireRateMultiplier;  // +0x2C
		float fireRateUnlockableMultiplier;  // +0x30
		int fireRateUnlockableFirst;  // +0x34
		int fireRateUnlockableLast;  // +0x38
		int damageType;  // +0x3C
		int attackType;  // +0x40
		float damageOnPlayer;  // +0x44
		float damageOnNPC;  // +0x48
		float damageUnlockableMultiplier;  // +0x4C
		int damageUnlockableFirst;  // +0x50
		int damageUnlockableLast;  // +0x54
		float friendlyFire;  // +0x58
		float impulse;  // +0x5C
		float speed;  // +0x60
		float distanceToLive;  // +0x64
	};

	// How the one who holds the weapon aims (RTTI proto::WeaponUserProfile; 0x88 bytes)
	struct WeaponUserProfile : public content::MetaLoadObject
	{
		// 0x104709D0
		WeaponUserProfile();
		// 0x10470AF0 (the deleting destructor is 0x10470B00)
		virtual ~WeaponUserProfile()
		{
		}
		// vftable slot 6 (0x10470B30)
		virtual void SetName(const content::ObjectName& newName);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1046FEB0: the best accuracy with the unlockables
		float GetAccuracyMin() const;
		// 0x10470B40: the accuracy after the weapon was held on target for time (full for the player's target, scaled
		// otherwise)
		float GetAccuracy(float time, bool playerTarget) const;

		// The four angle limits are kept in radians and shown in degrees
		float GetPitchMinAngle() const;
		void SetPitchMinAngle(float degrees);
		float GetPitchMaxAngle() const;
		void SetPitchMaxAngle(float degrees);
		float GetYawMinAngle() const;
		void SetYawMinAngle(float degrees);
		float GetYawMaxAngle() const;
		void SetYawMaxAngle(float degrees);

		content::ObjectName name;  // +8
		bool infiniteAmmo;  // +0x10
		float accuracyMin;  // +0x14
		float accuracyMax;  // +0x18
		float accuracyAngleMin;  // +0x1C
		float accuracyAngleMax;  // +0x20
		float accuracyGainTime;  // +0x24
		float accuracyMinWithSpeed;  // +0x28
		float accuracyMaxWithSpeed;  // +0x2C
		float speedForMinAccuracy;  // +0x30
		float accuracyNonPlayerTargetScalar;  // +0x34
		float accuracyMinUnlockableMultiplier;  // +0x38
		int accuracyMinUnlockableMultiplierConfig;  // +0x3C
		int accuracyUnlockableFirst;  // +0x40
		int accuracyUnlockableLast;  // +0x44
		bool sameDirConsecutiveShots;  // +0x48
		bool resetAccuracyWhenNotShooting;  // +0x49
		float pitchMinAngle;  // +0x4C
		float pitchMaxAngle;  // +0x50
		float yawMinAngle;  // +0x54
		float yawMaxAngle;  // +0x58
		int lookAt;  // +0x5C
		bool useIntentionWhenNoTarget;  // +0x60
		bool useFreeAimingWhenNoTarget;  // +0x61
		bool useDeadReckoning;  // +0x62
		bool useAutoTarget;  // +0x63
		int unknown64;
		content::ObjectName accuracyGainTimer;  // +0x68
		bool useGroundAccuracy;  // +0x70
		bool useRandomAccuracy;  // +0x71
		bool fixVerticalSign;  // +0x72
		float heatMax;  // +0x74
		float cooldownDelay;  // +0x78
		float cooldownRate;  // +0x7C
		float cooldownAmount;  // +0x80
		float heatPerShot;  // +0x84
	};

	// The base of the weapons that shoot (RTTI proto::WeaponBehaviour; 0x68 bytes): the ammunition it holds, the profile
	// of whoever uses it and the state of the current shot
	class WeaponBehaviour : public engine::Behaviour
	{
	public:
		// 0x10470060
		explicit WeaponBehaviour(engine::GameObject* newOwner);
		// 0x10470BF0 (the deleting destructor is 0x10471C30)
		virtual ~WeaponBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10470190)
		virtual void Slot1();
		// vftable slot 4 (0x104721D0) / 6 (0x10471C60), left to the engine
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x104701A0)
		virtual void OnPostedMessage(engine::Message* message);
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (pure; the guns shoot here)
		virtual void Slot8(int a, int b, float c) = 0;
		// vftable slot 9 (0x10470340): fills the clip to the capacity of the profile (the weapon's own when null)
		virtual void Slot9(AmmoProfileBase* profile);
		// vftable slot 10 (0x10470380): one shot less in the clip (the argument is not read)
		virtual void Slot10(int unused);
		// vftable slot 11 (0x104647B0)
		virtual void Slot11(int a);
		// vftable slot 12 / 13 (pure): the ammunition profile
		virtual AmmoProfileBase* GetAmmoProfile() = 0;
		virtual void SetAmmoProfile(AmmoProfileBase* profile) = 0;

		// 0x104701B0: no shot is left in the clip
		bool IsClipEmpty() const;
		// 0x10470220 / 0x10470CB0 (counts down to zero)
		void ResetUnknown28();
		void DecrementUnknown28();
		// 0x10470C20: takes the profile of whoever uses the weapon
		void SetUserProfile(WeaponUserProfile* profile);

		bool unknownC;
		bool unknownD;
		bool unknownE;
		float unknown10;
		float unknown14;
		engine::HandleBase unknown18;
		int clipCount;  // +0x1C
		float unknown20;
		WeaponUserProfile* userProfile;  // +0x24
		int unknown28;
		int unknown2C;
		engine::HandleBase unknown30;
		engine::HandleBase unknown34;
		engine::HandleBase unknown38;
		bool unknown3C;
		math::Vector unknown40;
		math::Vector unknown4C;
		bool unknown58;
		bool unknown59;
		bool unknown5A;
		int unknown5C;
		int unknown60;
		float unknown64;
	};

	class FreeAimingBehaviour : public engine::Behaviour
	{
	public:
		// 0x10470580
		explicit FreeAimingBehaviour(engine::GameObject* newOwner);
		// the compiler's destructor is 0x10470610 (the deleting destructor is 0x10470F20)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x10473610) / 6 (0x104735C0), left to the engine
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		float viewportOffsetX;  // +0xC
		float viewportOffsetY;  // +0x10
		math::Vector unknown14;
	};
}

namespace content
{
	// The shared copies of the enumerations' meta types (the engine keeps them in the units that first used them)
	template<> EnumMetaType* GetEnumMetaType<proto::Unlockable>();
	template<> EnumMetaType* GetEnumMetaType<proto::UnlockableMultiplierConfig>();
	template<> EnumMetaType* GetEnumMetaType<proto::DamageType>();
	template<> EnumMetaType* GetEnumMetaType<proto::AttackType>();
	template<> EnumMetaType* GetEnumMetaType<proto::ShootLookAtPossibilities>();
}

#endif
