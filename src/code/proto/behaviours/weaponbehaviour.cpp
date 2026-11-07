#include "code/proto/behaviours/weaponbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/unlockables.h"
#include <math.h>

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace choreo
{
	extern const float gMinusOne;
	extern const float gZero;
}

namespace proto
{
	// 0x10D977EC: 10.0f in the pooled constants (name guess)
	extern const float gTen;
	// 0x10E06DB0: 175.0f (name guess)
	extern const float gHundredSeventyFive;
	// 0x10DFE194 / 0x10DA3660: minus and plus 0.7f (name guesses)
	extern const float gMinusSevenTenths;
	extern const float gSevenTenths;
}

namespace content
{
	static const EnumValue sShootLookAtValues[] =
	{
		{ "None", 5 },
		{ "Target", 0 },
		{ "Intention", 1 },
		{ "TargetFeet", 2 },
		{ "TemporaryTarget", 3 },
		{ "FreeAim", 4 }
	};

	// FUNCTION: ENGINE 0x1046FC60
	template<> void EnumInfo<proto::ShootLookAtPossibilities>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::ShootLookAtPossibilities";
		*code = "pn";
		*values = sShootLookAtValues;
		*count = 6;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	struct BulletTracerProfile : public content::MetaLoadObject
	{
		virtual ~BulletTracerProfile();
	};

	// FUNCTION: ENGINE 0x1046FCA0
	content::ClassInfo* AmmoProfileBase::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AmmoProfileBase";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046FCE0
	content::ClassInfo* WeaponUserProfile::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponUserProfile";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046FD60
	content::ClassInfo* FreeAimingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FreeAimingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046FDA0
	int AmmoProfileBase::GetClipCapacity() const
	{
		int capacity = clipCapacity;
		int unlocked = gUnlockTable->CountUnlocked(clipCapacityUnlockableFirst, clipCapacityUnlockableLast);
		if (0 < unlocked)
		{
			capacity += clipCapacityUnlockableAdd * unlocked;
		}
		return capacity;
	}

	// FUNCTION: ENGINE 0x1046FDE0
	float AmmoProfileBase::GetDamageMultiplier() const
	{
		float multiplier = engine::driving::gOne;
		int unlocked = gUnlockTable->CountUnlocked(damageUnlockableFirst, damageUnlockableLast);
		if (0 < unlocked)
		{
			multiplier = ((float)unlocked / (float)((damageUnlockableLast - damageUnlockableFirst) + 1)) *
				(damageUnlockableMultiplier - engine::driving::gOne) + engine::driving::gOne;
		}
		return multiplier;
	}

	// FUNCTION: ENGINE 0x1046FE60
	float AmmoProfileBase::GetDamage(bool onPlayer) const
	{
		float damage;
		if (onPlayer)
		{
			damage = damageOnPlayer;
		}
		else
		{
			damage = damageOnNPC;
		}
		return GetDamageMultiplier() * damage;
	}

	// FUNCTION: ENGINE 0x1046FEB0
	float WeaponUserProfile::GetAccuracyMin() const
	{
		float result = accuracyMin;
		int unlocked = gUnlockTable->CountUnlocked(accuracyUnlockableFirst, accuracyUnlockableLast);
		if (0 < unlocked)
		{
			int total = (accuracyUnlockableLast - accuracyUnlockableFirst) + 1;
			if (accuracyMinUnlockableMultiplierConfig == 1)
			{
				unlocked = (int)ceil((double)((float)unlocked * engine::driving::gHalf));
				total = (int)ceil((double)((float)total * engine::driving::gHalf));
			}
			result = (((float)unlocked / (float)total) * (accuracyMinUnlockableMultiplier - engine::driving::gOne) +
				engine::driving::gOne) * result;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1046FFA0
	void WeaponUserProfile::SetPitchMinAngle(float degrees)
	{
		pitchMinAngle = degrees * 0.01745329238474369f;
	}

	// FUNCTION: ENGINE 0x1046FFC0
	float WeaponUserProfile::GetPitchMinAngle() const
	{
		return pitchMinAngle * 57.2957763671875f;
	}

	// FUNCTION: ENGINE 0x1046FFD0
	void WeaponUserProfile::SetPitchMaxAngle(float degrees)
	{
		pitchMaxAngle = degrees * 0.01745329238474369f;
	}

	// FUNCTION: ENGINE 0x1046FFF0
	float WeaponUserProfile::GetPitchMaxAngle() const
	{
		return pitchMaxAngle * 57.2957763671875f;
	}

	// FUNCTION: ENGINE 0x10470000
	void WeaponUserProfile::SetYawMinAngle(float degrees)
	{
		yawMinAngle = degrees * 0.01745329238474369f;
	}

	// FUNCTION: ENGINE 0x10470020
	float WeaponUserProfile::GetYawMinAngle() const
	{
		return yawMinAngle * 57.2957763671875f;
	}

	// FUNCTION: ENGINE 0x10470030
	void WeaponUserProfile::SetYawMaxAngle(float degrees)
	{
		yawMaxAngle = degrees * 0.01745329238474369f;
	}

	// FUNCTION: ENGINE 0x10470050
	float WeaponUserProfile::GetYawMaxAngle() const
	{
		return yawMaxAngle * 57.2957763671875f;
	}

	// FUNCTION: ENGINE 0x10470580
	FreeAimingBehaviour::FreeAimingBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		viewportOffsetX(0.0f), viewportOffsetY(0.0f), unknown14(math::kZeroVector)
	{
		Listen(0x22, true);
		Listen(0x2f, true);
		Listen2(0x10, true);
	}

	// FUNCTION: ENGINE 0x104707B0
	// EQUIVALENT: scheduling; the engine loads the constants before the integer stores and stores the 1.0 values between them (32 %)
	AmmoProfileBase::AmmoProfileBase() : tracerParams(0), clipCapacityUnlockableAdd(0), clipCapacityUnlockableFirst(0),
		clipCapacityUnlockableLast(0), fireRateUnlockableFirst(0), fireRateUnlockableLast(0), damageType(0), attackType(0),
		damageUnlockableFirst(0), damageUnlockableLast(0)
	{
		float one = engine::driving::gOne;
		float ten = gTen;
		fireRate = one;
		offCameraFireRateMultiplier = one;
		friendlyFire = one;
		clipCapacity = 0x1e;
		fireRateUnlockableMultiplier = 0.0f;
		damageOnPlayer = ten;
		damageOnNPC = ten;
		damageUnlockableMultiplier = 0.0f;
		impulse = 0.0f;
		speed = ten;
		distanceToLive = gHundredSeventyFive;
	}

	// FUNCTION: ENGINE 0x10470870
	AmmoProfileBase::~AmmoProfileBase()
	{
		core::SafeRelease(tracerParams);
	}

	// FUNCTION: ENGINE 0x104708A0
	void AmmoProfileBase::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x104709D0
	// EQUIVALENT: scheduling; the engine loads the four constants before the first store and keeps the stores in declaration order after them (70 %)
	WeaponUserProfile::WeaponUserProfile() : infiniteAmmo(true), accuracyMin(0.0f), accuracyMax(0.0f),
		accuracyAngleMin(gMinusSevenTenths), accuracyAngleMax(gSevenTenths), accuracyGainTime(0.0f),
		accuracyMinWithSpeed(0.0f), accuracyMaxWithSpeed(0.0f), speedForMinAccuracy(choreo::gMinusOne),
		accuracyNonPlayerTargetScalar(engine::driving::gOne), accuracyMinUnlockableMultiplier(0.0f),
		accuracyMinUnlockableMultiplierConfig(0), accuracyUnlockableFirst(0), accuracyUnlockableLast(0),
		sameDirConsecutiveShots(true), resetAccuracyWhenNotShooting(false), pitchMinAngle(0.0f), pitchMaxAngle(0.0f),
		yawMinAngle(0.0f), yawMaxAngle(0.0f), lookAt(0), useIntentionWhenNoTarget(false),
		useFreeAimingWhenNoTarget(false), useDeadReckoning(false), useAutoTarget(false), useGroundAccuracy(false),
		useRandomAccuracy(false), fixVerticalSign(true), heatMax(0.0f), cooldownDelay(0.0f), cooldownRate(0.0f),
		cooldownAmount(0.0f), heatPerShot(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10470B30
	void WeaponUserProfile::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1046FD20
	content::ClassInfo* WeaponBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10470060
	// EQUIVALENT: scheduling and register choice; the engine keeps the address of the third handle in edi and stores the vftable after the zeroing float (33 %)
	WeaponBehaviour::WeaponBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), unknownC(false),
		unknownD(false), unknownE(false), unknown10(0), unknown14(0), clipCount(0), unknown20(0), userProfile(0),
		unknown28(0), unknown2C(0), unknown3C(false), unknown40(math::kZeroVector), unknown4C(math::kZeroVector),
		unknown58(false), unknown59(false), unknown5A(false), unknown5C(0), unknown60(0), unknown64(-3.4028234663852886e+38f)
	{
		Listen(0x22, true);
	}

	// FUNCTION: ENGINE 0x10470190
	void WeaponBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x104701A0
	void WeaponBehaviour::OnPostedMessage(engine::Message* message)
	{
	}

	// FUNCTION: ENGINE 0x104701B0
	// EQUIVALENT: the engine leaves the upper bytes of eax alone where ours zeroes them first; its callers read al only (0 %)
	bool WeaponBehaviour::IsClipEmpty() const
	{
		return !(clipCount > 0);
	}

	// FUNCTION: ENGINE 0x10470220
	void WeaponBehaviour::ResetUnknown28()
	{
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x10470340
	// EQUIVALENT: register choice; the engine reads the profile argument into ecx and restores this before the first virtual call (24 %)
	void WeaponBehaviour::Slot9(AmmoProfileBase* profile)
	{
		if (profile == 0)
		{
			if (GetAmmoProfile() == 0)
			{
				return;
			}
			profile = GetAmmoProfile();
		}
		clipCount = profile->GetClipCapacity();
	}

	// FUNCTION: ENGINE 0x10470380
	void WeaponBehaviour::Slot10(int unused)
	{
		clipCount--;
	}

	// FUNCTION: ENGINE 0x10470B40
	// NONMATCHING: the engine keeps the scale and the clamped fraction in other registers and lays the test for a zero gain time out in front (53 %)
#ifdef NONMATCHING
	float WeaponUserProfile::GetAccuracy(float time, bool playerTarget) const
	{
		float one = engine::driving::gOne;
		float scale = playerTarget ? one : accuracyNonPlayerTargetScalar;
		if (accuracyGainTime != choreo::gZero)
		{
			time = time / accuracyGainTime;
			if (one < time)
			{
				time = one;
			}
			float range = accuracyMax - GetAccuracyMin();
			return (range * time + GetAccuracyMin()) * scale;
		}
		return accuracyMax * scale;
	}
#endif

	// FUNCTION: ENGINE 0x10470C20
	void WeaponBehaviour::SetUserProfile(WeaponUserProfile* profile)
	{
		core::RefAssign(userProfile, profile);
	}

	// FUNCTION: ENGINE 0x10470CB0
	// EQUIVALENT: register choice; the engine masks in eax and stores it, ours masks in edx (91 %)
	void WeaponBehaviour::DecrementUnknown28()
	{
		int count = unknown28 - 1;
		unknown28 = count & ((count < 0) - 1);
	}

	// FUNCTION: ENGINE 0x10470BF0
	WeaponBehaviour::~WeaponBehaviour()
	{
		core::SafeRelease(userProfile);
	}

	// FUNCTION: ENGINE 0x10473C30
	content::MemberList* AmmoProfileBase::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, int, 0>("p"),
				PROTO_OFFSET(AmmoProfileBase, clipCapacity), "clipCapacity" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, int, 1>("p"),
				PROTO_OFFSET(AmmoProfileBase, clipCapacityUnlockableAdd), "clipCapacityUnlockableAdd" },
			{ content::GetEnumMetaType<Unlockable>(), 0x20, "clipCapacityUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x24, "clipCapacityUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 0>("p"),
				PROTO_OFFSET(AmmoProfileBase, fireRate), "fireRate" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 1>("p"),
				PROTO_OFFSET(AmmoProfileBase, offCameraFireRateMultiplier), "offCameraFireRateMultiplier" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 2>("p"),
				PROTO_OFFSET(AmmoProfileBase, fireRateUnlockableMultiplier), "fireRateUnlockableMultiplier" },
			{ content::GetEnumMetaType<Unlockable>(), 0x34, "fireRateUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x38, "fireRateUnlockableLast" },
			{ content::GetEnumMetaType<DamageType>(), 0x3c, "damageType" },
			{ content::GetEnumMetaType<AttackType>(), 0x40, "attackType" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 3>("p"),
				PROTO_OFFSET(AmmoProfileBase, damageOnPlayer), "damageOnPlayer" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 4>("p"),
				PROTO_OFFSET(AmmoProfileBase, damageOnNPC), "damageOnNPC" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 5>("p"),
				PROTO_OFFSET(AmmoProfileBase, damageUnlockableMultiplier), "damageUnlockableMultiplier" },
			{ content::GetEnumMetaType<Unlockable>(), 0x50, "damageUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x54, "damageUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 6>("p"),
				PROTO_OFFSET(AmmoProfileBase, friendlyFire), "friendlyFire" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 7>("p"),
				PROTO_OFFSET(AmmoProfileBase, impulse), "impulse" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 8>("p"),
				PROTO_OFFSET(AmmoProfileBase, speed), "speed" },
			{ content::GetMemberPrimitiveMetaType<AmmoProfileBase, float, 9>("p"),
				PROTO_OFFSET(AmmoProfileBase, distanceToLive), "distanceToLive" },
			{ content::GetReferenceMetaType<AmmoProfileBase, BulletTracerProfile>("p"),
				PROTO_OFFSET(AmmoProfileBase, tracerParams), "tracerParams" }
		};
		sList.members = sMembers;
		sList.count = 21;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10474050
	content::MemberList* WeaponUserProfile::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 0>("p"),
				PROTO_OFFSET(WeaponUserProfile, infiniteAmmo), "infiniteAmmo" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 0>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyMin), "accuracyMin" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 1>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyMax), "accuracyMax" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 2>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyAngleMin), "accuracyAngleMin" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 3>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyAngleMax), "accuracyAngleMax" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 4>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyGainTime), "accuracyGainTime" },
			{ content::GetNameMetaType<WeaponUserProfile>(true, true, "p"),
				PROTO_NAME_OFFSET(WeaponUserProfile, accuracyGainTimer), "accuracyGainTimer" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 5>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyMinWithSpeed), "accuracyMinWithSpeed" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 6>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyMaxWithSpeed), "accuracyMaxWithSpeed" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 7>("p"),
				PROTO_OFFSET(WeaponUserProfile, speedForMinAccuracy), "speedForMinAccuracy" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 8>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyNonPlayerTargetScalar), "accuracyNonPlayerTargetScalar" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 9>("p"),
				PROTO_OFFSET(WeaponUserProfile, accuracyMinUnlockableMultiplier), "accuracyMinUnlockableMultiplier" },
			{ content::GetEnumMetaType<UnlockableMultiplierConfig>(), 0x3c, "accuracyMinUnlockableMultiplierConfig" },
			{ content::GetEnumMetaType<Unlockable>(), 0x40, "accuracyUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x44, "accuracyUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 1>("p"),
				PROTO_OFFSET(WeaponUserProfile, sameDirConsecutiveShots), "sameDirConsecutiveShots" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 2>("p"),
				PROTO_OFFSET(WeaponUserProfile, resetAccuracyWhenNotShooting), "resetAccuracyWhenNotShooting" },
			{ content::GetMemberMetaType<WeaponUserProfile, float, 0>(&WeaponUserProfile::GetPitchMinAngle,
				&WeaponUserProfile::SetPitchMinAngle, "p"), 0, "pitchMinAngle" },
			{ content::GetMemberMetaType<WeaponUserProfile, float, 1>(&WeaponUserProfile::GetPitchMaxAngle,
				&WeaponUserProfile::SetPitchMaxAngle, "p"), 0, "pitchMaxAngle" },
			{ content::GetMemberMetaType<WeaponUserProfile, float, 2>(&WeaponUserProfile::GetYawMinAngle,
				&WeaponUserProfile::SetYawMinAngle, "p"), 0, "yawMinAngle" },
			{ content::GetMemberMetaType<WeaponUserProfile, float, 3>(&WeaponUserProfile::GetYawMaxAngle,
				&WeaponUserProfile::SetYawMaxAngle, "p"), 0, "yawMaxAngle" },
			{ content::GetEnumMetaType<ShootLookAtPossibilities>(), 0x5c, "lookAt" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 3>("p"),
				PROTO_OFFSET(WeaponUserProfile, useIntentionWhenNoTarget), "useIntentionWhenNoTarget" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 4>("p"),
				PROTO_OFFSET(WeaponUserProfile, useFreeAimingWhenNoTarget), "useFreeAimingWhenNoTarget" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 5>("p"),
				PROTO_OFFSET(WeaponUserProfile, useDeadReckoning), "useDeadReckoning" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 6>("p"),
				PROTO_OFFSET(WeaponUserProfile, useAutoTarget), "useAutoTarget" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 7>("p"),
				PROTO_OFFSET(WeaponUserProfile, useGroundAccuracy), "useGroundAccuracy" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 8>("p"),
				PROTO_OFFSET(WeaponUserProfile, useRandomAccuracy), "useRandomAccuracy" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, bool, 9>("p"),
				PROTO_OFFSET(WeaponUserProfile, fixVerticalSign), "fixVerticalSign" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 10>("p"),
				PROTO_OFFSET(WeaponUserProfile, heatMax), "heatMax" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 11>("p"),
				PROTO_OFFSET(WeaponUserProfile, cooldownDelay), "cooldownDelay" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 12>("p"),
				PROTO_OFFSET(WeaponUserProfile, cooldownRate), "cooldownRate" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 13>("p"),
				PROTO_OFFSET(WeaponUserProfile, cooldownAmount), "cooldownAmount" },
			{ content::GetMemberPrimitiveMetaType<WeaponUserProfile, float, 14>("p"),
				PROTO_OFFSET(WeaponUserProfile, heatPerShot), "heatPerShot" }
		};
		sList.members = sMembers;
		sList.count = 34;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10474740
	content::MemberList* WeaponBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, WeaponBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<WeaponBehaviour, WeaponUserProfile>("p"),
				PROTO_OFFSET(WeaponBehaviour, userProfile), "userProfile" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104719E0
	content::MemberList* FreeAimingBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FreeAimingBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<FreeAimingBehaviour, float, 0>("p"),
				PROTO_OFFSET(FreeAimingBehaviour, viewportOffsetX), "viewportOffsetX" },
			{ content::GetMemberPrimitiveMetaType<FreeAimingBehaviour, float, 1>("p"),
				PROTO_OFFSET(FreeAimingBehaviour, viewportOffsetY), "viewportOffsetY" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10470610
// FUNCTION: ENGINE 0x10470660
// FUNCTION: ENGINE 0x10470670
// FUNCTION: ENGINE 0x104706B0
// FUNCTION: ENGINE 0x104706D0
// FUNCTION: ENGINE 0x10470730
// FUNCTION: ENGINE 0x10470740
// FUNCTION: ENGINE 0x10470770
// FUNCTION: ENGINE 0x10470780
// FUNCTION: ENGINE 0x10470B00
// FUNCTION: ENGINE 0x10470F20
// FUNCTION: ENGINE 0x10470F80
// FUNCTION: ENGINE 0x10470FC0
// FUNCTION: ENGINE 0x10471000
// FUNCTION: ENGINE 0x10471040
// FUNCTION: ENGINE 0x10471080
// FUNCTION: ENGINE 0x104710C0
// FUNCTION: ENGINE 0x10471100
// FUNCTION: ENGINE 0x10471140
// FUNCTION: ENGINE 0x10471180
// FUNCTION: ENGINE 0x104711C0
// FUNCTION: ENGINE 0x10471200
// FUNCTION: ENGINE 0x10471240
// FUNCTION: ENGINE 0x10471280
// FUNCTION: ENGINE 0x104712C0
// FUNCTION: ENGINE 0x10471300
// FUNCTION: ENGINE 0x10471340
// FUNCTION: ENGINE 0x10471380
// FUNCTION: ENGINE 0x104713C0
// FUNCTION: ENGINE 0x10471400
// FUNCTION: ENGINE 0x10471440
// FUNCTION: ENGINE 0x10471480
// FUNCTION: ENGINE 0x104714C0
// FUNCTION: ENGINE 0x10471500
// FUNCTION: ENGINE 0x10471540
// FUNCTION: ENGINE 0x10471580
// FUNCTION: ENGINE 0x104715C0
// FUNCTION: ENGINE 0x10471600
// FUNCTION: ENGINE 0x10471640
// FUNCTION: ENGINE 0x10471680
// FUNCTION: ENGINE 0x104716C0
// FUNCTION: ENGINE 0x10471700
// FUNCTION: ENGINE 0x10471740
// FUNCTION: ENGINE 0x10471780
// FUNCTION: ENGINE 0x104717C0
// FUNCTION: ENGINE 0x10471800
// FUNCTION: ENGINE 0x10471840
// FUNCTION: ENGINE 0x10471880
// FUNCTION: ENGINE 0x104718C0
// FUNCTION: ENGINE 0x10471900
// FUNCTION: ENGINE 0x10471940
// FUNCTION: ENGINE 0x10471950
// FUNCTION: ENGINE 0x10471980
// FUNCTION: ENGINE 0x104719A0
// FUNCTION: ENGINE 0x104719C0
// FUNCTION: ENGINE 0x10471AF0
// FUNCTION: ENGINE 0x10471C30
// FUNCTION: ENGINE 0x10473970
// FUNCTION: ENGINE 0x104739D0
// FUNCTION: ENGINE 0x10473A50
// FUNCTION: ENGINE 0x10473AD0
// FUNCTION: ENGINE 0x10473B50
// FUNCTION: ENGINE 0x10473BD0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10470AF0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104706F0
