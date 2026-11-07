#include "code/proto/behaviours/missilebehaviour.h"
#include "code/core/refptr.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gTwo;
		// 0x10D95E48: 30.0f in the pooled constants (name guess)
		extern const float gThirty;
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
	// 0x10D977EC: 10.0f in the pooled constants (name guess)
	extern const float gTen;
	// 0x10DA3664: 50.0f (name guess)
	extern const float gFifty;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10467C20
	content::ClassInfo* MissileSpin::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileSpin";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10467C60
	content::ClassInfo* MissileProfile::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileProfile";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10467CA0
	content::ClassInfo* MissileBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10467CE0
	// EQUIVALENT: scheduling; the engine zeroes xmm0 before it loads the constants and stores the vftable after the member stores (75 %)
	MissileProfile::MissileProfile()
	{
		float thirty = engine::driving::gThirty;
		float ten = gTen;
		float minusOne = choreo::gMinusOne;
		acceleration = thirty;
		timeToLive = engine::driving::gTwo;
		float one = engine::driving::gOne;
		airFriction = ten;
		float fifty = gFifty;
		interpolateMaxTurningVelocity = false;
		useOriginatorToRequestToken = false;
		inheritSpawnerVelocity = false;
		useOriginatorToValidateCollision = false;
		startTrackingWhenHigher = false;
		perfectlyAccurateTracking = false;
		trackingPosition = 0;
		spin = 0;
		intersectionProperties = 0;
		initialVelocity = 0.0f;
		initialDeceleration = minusOne;
		gravity = 0.0f;
		maxTurningVelocity = one;
		airFrictionIncreaseRate = fifty;
		length = 0.0f;
		timeToLockon = 0.0f;
		performTracking = true;
		proximity = 0.0f;
		minDotBetweenHeadings = 0.0f;
		trackingDelay = 0.0f;
		changingAccuracySpeed = minusOne;
		effectScale = one;
		effectScaleX = one;
		effectScaleY = one;
		thickness = 0.0f;
	}

	// FUNCTION: ENGINE 0x1046D160
	// EQUIVALENT: scheduling; the engine loads the 1.0 earlier and keeps the address of the intersection properties in edi from their constructor call on (78 %)
	MissileBehaviour::MissileBehaviour(engine::GameObject* newOwner) : WeaponBehaviour(newOwner), unknownB0(0.0f),
		unknownBA(false), unknownBC(0.0f), unknownC0(0.0f), unknownC4(0.0f), unknownC8(0.0f),
		unknownCC(engine::driving::gOne), unknownD0(0.0f), unknownD4(gTen), unknownD8(0.0f), unknownDC(0.0f),
		unknownE0(true), unknownE1(true), unknownE3(false), unknownE4(0.0f), unknownE8(0.0f), unknownEC(0.0f),
		unknownFC(-1), unknown100(0.0f), ammoProfile(0)
	{
		Stop();
		Listen(0xf, true);
		Listen(3, true);
		Listen(2, true);
		Listen(0x14, true);
		Listen(0x22, true);
		Listen(0x1a, true);
		Listen(0x22, true);
	}

	// FUNCTION: ENGINE 0x10467E30
	void MissileBehaviour::Slot1()
	{
		WeaponBehaviour::Slot1();
		clipCount = 1;
	}

	// FUNCTION: ENGINE 0x10467E50
	AmmoProfileBase* MissileBehaviour::GetAmmoProfile()
	{
		return ammoProfile;
	}

	// FUNCTION: ENGINE 0x10468380
	// EQUIVALENT: scheduling; the engine stores the reference count between the two vftable stores, ours behind them (94 %)
	MissileSpin::MissileSpin() : axisX(math::kZeroVector), axisY(math::kZeroVector), minSpeedX(0.0f), minSpeedY(0.0f),
		maxSpeedX(0.0f), maxSpeedY(0.0f), initialOrientationRandom(false)
	{
	}

	// FUNCTION: ENGINE 0x10468460
	MissileProfile::~MissileProfile()
	{
		core::SafeRelease(intersectionProperties);
	}

	// FUNCTION: ENGINE 0x10468490
	MissileBehaviour::~MissileBehaviour()
	{
		core::SafeRelease(ammoProfile);
	}

	// FUNCTION: ENGINE 0x104684F0
	void MissileBehaviour::SetAmmoProfile(AmmoProfileBase* profile)
	{
		core::RefAssign(ammoProfile, static_cast<MissileProfile*>(profile));
		unknownD4 = ammoProfile->airFriction;
	}

	// FUNCTION: ENGINE 0x10469510
	content::MemberList* MissileSpin::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<MissileSpin, 0>("p"), 8, "axisX" },
			{ content::GetMemberVectorMetaType<MissileSpin, 1>("p"), 0x14, "axisY" },
			{ content::GetMemberPrimitiveMetaType<MissileSpin, float, 0>("p"),
				PROTO_OFFSET(MissileSpin, minSpeedX), "minSpeedX" },
			{ content::GetMemberPrimitiveMetaType<MissileSpin, float, 1>("p"),
				PROTO_OFFSET(MissileSpin, minSpeedY), "minSpeedY" },
			{ content::GetMemberPrimitiveMetaType<MissileSpin, float, 2>("p"),
				PROTO_OFFSET(MissileSpin, maxSpeedX), "maxSpeedX" },
			{ content::GetMemberPrimitiveMetaType<MissileSpin, float, 3>("p"),
				PROTO_OFFSET(MissileSpin, maxSpeedY), "maxSpeedY" },
			{ content::GetMemberPrimitiveMetaType<MissileSpin, bool, 0>("p"),
				PROTO_OFFSET(MissileSpin, initialOrientationRandom), "initialOrientationRandom" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104696D0
	content::MemberList* MissileBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<WeaponBehaviour>();
		static content::BaseClassCasterImpl<WeaponBehaviour, MissileBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1046B630
	content::MemberList* MissileProfile::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AmmoProfileBase>();
		static content::BaseClassCasterImpl<AmmoProfileBase, MissileProfile> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 0>("p"),
				PROTO_OFFSET(MissileProfile, initialVelocity), "initialVelocity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 1>("p"),
				PROTO_OFFSET(MissileProfile, initialDeceleration), "initialDeceleration" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 2>("p"),
				PROTO_OFFSET(MissileProfile, acceleration), "acceleration" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 3>("p"),
				PROTO_OFFSET(MissileProfile, gravity), "gravity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 4>("p"),
				PROTO_OFFSET(MissileProfile, timeToLive), "timeToLive" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 5>("p"),
				PROTO_OFFSET(MissileProfile, maxTurningVelocity), "maxTurningVelocity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 0>("p"),
				PROTO_OFFSET(MissileProfile, interpolateMaxTurningVelocity), "interpolateMaxTurningVelocity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 6>("p"),
				PROTO_OFFSET(MissileProfile, airFriction), "airFriction" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 7>("p"),
				PROTO_OFFSET(MissileProfile, airFrictionIncreaseRate), "airFrictionIncreaseRate" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 8>("p"),
				PROTO_OFFSET(MissileProfile, length), "length" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 9>("p"),
				PROTO_OFFSET(MissileProfile, timeToLockon), "timeToLockon" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 1>("p"),
				PROTO_OFFSET(MissileProfile, performTracking), "performTracking" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 2>("p"),
				PROTO_OFFSET(MissileProfile, perfectlyAccurateTracking), "perfectlyAccurateTracking" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 10>("p"),
				PROTO_OFFSET(MissileProfile, proximity), "proximity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 11>("p"),
				PROTO_OFFSET(MissileProfile, minDotBetweenHeadings), "minDotBetweenHeadings" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 3>("p"),
				PROTO_OFFSET(MissileProfile, inheritSpawnerVelocity), "inheritSpawnerVelocity" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 4>("p"),
				PROTO_OFFSET(MissileProfile, useOriginatorToValidateCollision), "useOriginatorToValidateCollision" },
			{ content::GetEnumMetaType<ShootLookAtPossibilities>(), 0xa0, "trackingPosition" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 12>("p"),
				PROTO_OFFSET(MissileProfile, trackingDelay), "trackingDelay" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 5>("p"),
				PROTO_OFFSET(MissileProfile, startTrackingWhenHigher), "startTrackingWhenHigher" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 13>("p"),
				PROTO_OFFSET(MissileProfile, changingAccuracySpeed), "changingAccuracySpeed" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 14>("p"),
				PROTO_OFFSET(MissileProfile, effectScale), "effectScale" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 15>("p"),
				PROTO_OFFSET(MissileProfile, effectScaleX), "effectScaleX" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 16>("p"),
				PROTO_OFFSET(MissileProfile, effectScaleY), "effectScaleY" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, float, 17>("p"),
				PROTO_OFFSET(MissileProfile, thickness), "thickness" },
			{ content::GetReferenceMetaType<MissileProfile, MissileSpin>("p"),
				PROTO_OFFSET(MissileProfile, spin), "spin" },
			{ content::GetMemberPrimitiveMetaType<MissileProfile, bool, 6>("p"),
				PROTO_OFFSET(MissileProfile, useOriginatorToRequestToken), "useOriginatorToRequestToken" },
			{ content::GetReferenceMetaType<MissileProfile, ravenphysics::IntersectionPropertiesLoader>("p"),
				PROTO_OFFSET(MissileProfile, intersectionProperties), "intersectionProperties" }
		};
		sList.members = sMembers;
		sList.count = 28;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10468180
// FUNCTION: ENGINE 0x104681C0
// FUNCTION: ENGINE 0x10468210
// FUNCTION: ENGINE 0x10468220
// FUNCTION: ENGINE 0x10468240
// FUNCTION: ENGINE 0x10468300
// FUNCTION: ENGINE 0x10468310
// FUNCTION: ENGINE 0x10468340
// FUNCTION: ENGINE 0x10468350
// FUNCTION: ENGINE 0x10468430
// FUNCTION: ENGINE 0x10468D50
// FUNCTION: ENGINE 0x10468D90
// FUNCTION: ENGINE 0x10468DD0
// FUNCTION: ENGINE 0x10468E10
// FUNCTION: ENGINE 0x10468E50
// FUNCTION: ENGINE 0x10468E90
// FUNCTION: ENGINE 0x10468ED0
// FUNCTION: ENGINE 0x10468F10
// FUNCTION: ENGINE 0x10468F50
// FUNCTION: ENGINE 0x10468F90
// FUNCTION: ENGINE 0x10468FD0
// FUNCTION: ENGINE 0x10469010
// FUNCTION: ENGINE 0x10469050
// FUNCTION: ENGINE 0x10469090
// FUNCTION: ENGINE 0x104690D0
// FUNCTION: ENGINE 0x10469110
// FUNCTION: ENGINE 0x10469150
// FUNCTION: ENGINE 0x10469190
// FUNCTION: ENGINE 0x104691D0
// FUNCTION: ENGINE 0x10469210
// FUNCTION: ENGINE 0x10469250
// FUNCTION: ENGINE 0x10469290
// FUNCTION: ENGINE 0x104692D0
// FUNCTION: ENGINE 0x10469310
// FUNCTION: ENGINE 0x10469350
// FUNCTION: ENGINE 0x10469390
// FUNCTION: ENGINE 0x104693D0
// FUNCTION: ENGINE 0x10469410
// FUNCTION: ENGINE 0x10469450
// FUNCTION: ENGINE 0x10469490
// FUNCTION: ENGINE 0x104694D0
// FUNCTION: ENGINE 0x104694E0
// FUNCTION: ENGINE 0x10469940
// FUNCTION: ENGINE 0x10469970
// FUNCTION: ENGINE 0x1046B570
// FUNCTION: ENGINE 0x1046B5D0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10468420
