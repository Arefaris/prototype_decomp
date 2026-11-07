#include "code/proto/ai/ambientmanager/behaviours/pedalertreaction.h"
#include <math.h>

namespace engine
{
	namespace camera
	{
		// 0x10D95F28: 3.0f in the pooled constants (name guess)
		extern const float gThree;
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

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

#define PROTO_REACTION_OFFSET(index) \
	content::MemberOffset(&((PedAlertReactionTable*)0)->reactions[index], \
		(int)&((PedAlertReactionTable*)0)->reactions[index])

	// FUNCTION: ENGINE 0x10432F90
	content::ClassInfo* PedAlertReaction::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PedAlertReaction";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10432FD0
	content::ClassInfo* PedAlertReactionTable::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PedAlertReactionTable";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10433180
	// NONMATCHING: the engine loads the constants for the first and last statements ahead of the stores (best 67 %)
#ifdef NONMATCHING
	PedAlertReaction::PedAlertReaction()
	{
		alertLength = engine::camera::gThree;
		alertRadius = gTen;
		createPedestrianAlert = false;
		chanceToIgnore = 0.0f;
		panic = false;
		target = true;
		targetChoice = ALERT_TARGET_CHOICE_CLOSEST;
		priority = 0;
		overridesEqualPriority = false;
		rubberneckDistance = choreo::gMinusOne;
		rubberneckTime = 0.0f;
		rubberneckPanicChance = 0.0f;
		maxAngleCosine = (float)cos(1.5708);
	}
#endif

	// FUNCTION: ENGINE 0x10433200
	void PedAlertReaction::SetMaxAngleForReaction(float degrees)
	{
		maxAngleCosine = cosf(degrees * 0.017453292f);
	}

	// FUNCTION: ENGINE 0x10433220
	float PedAlertReaction::GetMaxAngleForReaction() const
	{
		return acosf(maxAngleCosine) * 57.295776f;
	}

	// FUNCTION: ENGINE 0x10433240
	float PedAlertReaction::GetMaxAngleCosine() const
	{
		return maxAngleCosine;
	}

	// FUNCTION: ENGINE 0x10433250
	// NONMATCHING: the engine calls the constructor of the reactions knowing which registers it leaves alone; it is
	// not compiled here
#ifdef NONMATCHING
	PedAlertReactionTable::PedAlertReactionTable()
	{
	}
#endif

	// FUNCTION: ENGINE 0x1043B1F0
	content::MemberList* PedAlertReaction::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, bool, 0>("p"),
				PROTO_OFFSET(PedAlertReaction, createPedestrianAlert), "createPedestrianAlert" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 0>("p"),
				PROTO_OFFSET(PedAlertReaction, alertLength), "alertLength" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 1>("p"),
				PROTO_OFFSET(PedAlertReaction, alertRadius), "alertRadius" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 2>("p"),
				PROTO_OFFSET(PedAlertReaction, chanceToIgnore), "chanceToIgnore" },
			{ content::GetMemberMetaType<PedAlertReaction, float, 0>(&PedAlertReaction::GetMaxAngleForReaction,
				&PedAlertReaction::SetMaxAngleForReaction, "p"), 0, "maxAngleForReaction" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, bool, 1>("p"),
				PROTO_OFFSET(PedAlertReaction, panic), "panic" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, bool, 2>("p"),
				PROTO_OFFSET(PedAlertReaction, target), "target" },
			{ content::GetEnumMetaType<AlertTargetChoice>(), 0x18, "targetChoice" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, int, 0>("p"),
				PROTO_OFFSET(PedAlertReaction, priority), "priority" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, bool, 3>("p"),
				PROTO_OFFSET(PedAlertReaction, overridesEqualPriority), "overridesEqualPriority" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 3>("p"),
				PROTO_OFFSET(PedAlertReaction, rubberneckDistance), "rubberneckDistance" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 4>("p"),
				PROTO_OFFSET(PedAlertReaction, rubberneckTime), "rubberneckTime" },
			{ content::GetMemberPrimitiveMetaType<PedAlertReaction, float, 5>("p"),
				PROTO_OFFSET(PedAlertReaction, rubberneckPanicChance), "rubberneckPanicChance" }
		};
		sList.members = sMembers;
		sList.count = 13;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1043EC40
	content::MemberList* PedAlertReactionTable::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(0), "alertType_None" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(1), "alertType_Explosion" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(2), "alertType_Throw" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(3), "alertType_Shapeshift" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(4), "alertType_Gunfire" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(5), "alertType_Grab" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(6), "alertType_Hit" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(7), "alertType_Shove" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(8),
				"alertType_ExtremeLocomotion" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(9), "alertType_Landing" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(10), "alertType_Consume" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(11), "alertType_Death" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(12), "alertType_BulletHit" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(13), "alertType_ScatterPeds" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(14), "alertType_MissileFire" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(15),
				"alertType_PanicingPedestrian" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(16), "alertType_DeadBody" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(17), "alertType_GrabScream" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(18), "alertType_FlyingObject" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(19), "alertType_ThrowLand" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(20), "alertType_EnterVehicle" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(21),
				"alertType_GenerateDiversion" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(22),
				"alertType_BurningVehicle" },
			{ content::GetClassMetaType<PedAlertReaction>(), PROTO_REACTION_OFFSET(23), "alertType_CarAccident" }
		};
		sList.members = sMembers;
		sList.count = 24;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10433B60
// FUNCTION: ENGINE 0x10433DD0
// FUNCTION: ENGINE 0x10438290
// FUNCTION: ENGINE 0x104382D0
// FUNCTION: ENGINE 0x10438310
// FUNCTION: ENGINE 0x10438350
// FUNCTION: ENGINE 0x10438390
// FUNCTION: ENGINE 0x104383D0
// FUNCTION: ENGINE 0x10438410
// FUNCTION: ENGINE 0x10438450
// FUNCTION: ENGINE 0x10438490
// FUNCTION: ENGINE 0x104384D0
// FUNCTION: ENGINE 0x10438510
// FUNCTION: ENGINE 0x10438740
// FUNCTION: ENGINE 0x10438760
// FUNCTION: ENGINE 0x10438780
// FUNCTION: ENGINE 0x1043AD50
// FUNCTION: ENGINE 0x1043E660
