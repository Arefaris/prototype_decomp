#include "code/proto/behaviours/consumablebehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/driving/carattributes.h"
#include "code/proto/reflectedstubs.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// 0x11283550 / 0x11283540 (symbols.txt)
	extern content::ObjectName gPhysicsObjectAttributeName;
	extern core::Name<core::CaseSensitiveKey> gAttachmentState;
}

namespace ravenphysics
{
	// 0x10D977E4 (symbols.txt): 1000.0f in the pooled constants (name guess)
	extern const float gDefaultMaxForce;
}

namespace proto
{
	extern content::ObjectName gDrawableAttributeName;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1007A210
	content::ClassInfo* ConsumableProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ConsumableProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1007A250
	content::ClassInfo* ConsumableBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConsumableBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1007AD70
	// NONMATCHING: the engine loads the three constants before the base constructor's stores and delays its own vftable
	// store behind half of the members (31.7 %)
#ifdef NONMATCHING
	ConsumableProperties::ConsumableProperties() : initialAbsorbSpeed(engine::driving::gOne), absorbAcceleration(0.0f),
		maxAbsorbSpeed(gTen), delayBeforeAcceleration(0.0f), jointScaleRate(engine::driving::gOne),
		angularDampingY(engine::driving::gOne), angularDampingXZ(engine::driving::gOne), maxConstraintDistance(4.0f),
		constraintDelay(0.0f), maxConstraintForce(ravenphysics::gDefaultMaxForce), maxConstraintErrorCorrectionForce(100.0f),
		ragdollIntersectionProperties(0)
	{
	}
#endif

	// FUNCTION: ENGINE 0x1007AE10
	ConsumableProperties::~ConsumableProperties()
	{
		core::SafeRelease(ragdollIntersectionProperties);
	}

	// FUNCTION: ENGINE 0x1007C4A0
	content::MemberList* ConsumableProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 0>("pn"),
				PROTO_OFFSET(ConsumableProperties, initialAbsorbSpeed), "initialAbsorbSpeed" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 1>("pn"),
				PROTO_OFFSET(ConsumableProperties, absorbAcceleration), "absorbAcceleration" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 2>("pn"),
				PROTO_OFFSET(ConsumableProperties, maxAbsorbSpeed), "maxAbsorbSpeed" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 3>("pn"),
				PROTO_OFFSET(ConsumableProperties, delayBeforeAcceleration), "delayBeforeAcceleration" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 4>("pn"),
				PROTO_OFFSET(ConsumableProperties, jointScaleRate), "jointScaleRate" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 5>("pn"),
				PROTO_OFFSET(ConsumableProperties, angularDampingY), "angularDampingY" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 6>("pn"),
				PROTO_OFFSET(ConsumableProperties, angularDampingXZ), "angularDampingXZ" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 7>("pn"),
				PROTO_OFFSET(ConsumableProperties, maxConstraintDistance), "maxConstraintDistance" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 8>("pn"),
				PROTO_OFFSET(ConsumableProperties, constraintDelay), "constraintDelay" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 9>("pn"),
				PROTO_OFFSET(ConsumableProperties, maxConstraintForce), "maxConstraintForce" },
			{ content::GetMemberPrimitiveMetaType<ConsumableProperties, float, 10>("pn"),
				PROTO_OFFSET(ConsumableProperties, maxConstraintErrorCorrectionForce), "maxConstraintErrorCorrectionForce" },
			{ content::GetReferenceMetaType<ConsumableProperties, ravenphysics::IntersectionPropertiesLoader>("pn"),
				PROTO_OFFSET(ConsumableProperties, ragdollIntersectionProperties), "ragdollIntersectionProperties" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1007C760
	content::MemberList* ConsumableBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ConsumableBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ConsumableBehaviour, TransformationDescription>("pn"),
				PROTO_OFFSET(ConsumableBehaviour, description), "description" },
			{ content::GetReferenceMetaType<ConsumableBehaviour, ConsumableProperties>("pn"),
				PROTO_OFFSET(ConsumableBehaviour, consumableProperties), "consumableProperties" },
			{ content::GetMemberPrimitiveMetaType<ConsumableBehaviour, float, 0>("p"),
				PROTO_OFFSET(ConsumableBehaviour, healthGained), "healthGained" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1007D560
	// NONMATCHING: the engine loads gOne once, right after the name constructor, and stores the flag byte behind the zeros
	// (70.3 %)
#ifdef NONMATCHING
	ConsumableBehaviour::ConsumableBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), description(0),
		unknown10(0), consumableProperties(0), healthGained(0.0f), unknown34(0), unknown38(0), unknown3C(0), unknown40(0),
		unknown48(0), unknown4C(0), unknown50(0), handle(-1), unknown60(true), unknown64(engine::driving::gOne, engine::driving::gOne),
		unknown6C(0.0f, 0.0f), unknown74(0.01f), unknown78(0)
	{
		unknown7C.Clear();
		Listen(0x1e, true);
		Listen(0x3c, true);
		Listen(0xf, true);
		Listen(2, true);
		Listen(3, true);
		Listen(0x21, true);
		Listen(0x17, true);
		unknown58 = unknown38;
	}
#endif

	// FUNCTION: ENGINE 0x1007B930
	void ConsumableBehaviour::Slot1()
	{
		drawableAttribute = owner->FindAttribute(gDrawableAttributeName);
		physicsObjectAttribute = owner->FindAttribute(engine::gPhysicsObjectAttributeName);
		attachmentStateAttribute = owner->FindAttribute(engine::gAttachmentState);
	}

	// FUNCTION: ENGINE 0x1007D740
	void ConsumableBehaviour::Update(float dt, unsigned short mask)
	{
		if (mask == 0x10)
		{
			UpdateRagdoll(dt);
		}
		else
		{
			UpdateOther(dt);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1007B1D0
// FUNCTION: ENGINE 0x1007B210
// FUNCTION: ENGINE 0x1007B250
// FUNCTION: ENGINE 0x1007B290
// FUNCTION: ENGINE 0x1007B2D0
// FUNCTION: ENGINE 0x1007B310
// FUNCTION: ENGINE 0x1007B350
// FUNCTION: ENGINE 0x1007B390
// FUNCTION: ENGINE 0x1007B3D0
// FUNCTION: ENGINE 0x1007B410
// FUNCTION: ENGINE 0x1007B450
// FUNCTION: ENGINE 0x1007B490
// FUNCTION: ENGINE 0x1007C140
// FUNCTION: ENGINE 0x1007C1A0
// FUNCTION: ENGINE 0x1007C200
// FUNCTION: ENGINE 0x1007A750
// FUNCTION: ENGINE 0x1007A760
// FUNCTION: ENGINE 0x1007A770
// FUNCTION: ENGINE 0x1007A780
// FUNCTION: ENGINE 0x1007B560
// FUNCTION: ENGINE 0x1007B570
// FUNCTION: ENGINE 0x1007B5A0
// FUNCTION: ENGINE 0x1007B5B0
// FUNCTION: ENGINE 0x1007B5E0
// FUNCTION: ENGINE 0x1007B5F0
// FUNCTION: ENGINE 0x1007AD30
// FUNCTION: ENGINE 0x1007AD40
