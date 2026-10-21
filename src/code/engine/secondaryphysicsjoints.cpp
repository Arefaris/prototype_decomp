#include "code/engine/secondaryphysicsjoints.h"
#include "code/math/random.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// The constraint creators the drivers' handle slots use (0x1065B6E0 makes a ball-in-socket constraint between
	// two untouched handles, the other two make the constraints of the powered joint; names guessed)
	CollisionHandle CreateBallInSocketConstraint();
	CollisionHandle CreateMotorConstraint();
	CollisionHandle CreateLimitConstraint();
}

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10915FD0
	content::ClassInfo* SecondaryPhysicsAmbientWind::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsAmbientWind";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10916040
	SecondaryPhysicsAmbientWind::~SecondaryPhysicsAmbientWind()
	{
	}

	// FUNCTION: ENGINE 0x10916050
	// NONMATCHING: the arithmetic is right; the engine keeps the last random number on the x87 stack up to the shared
	// tail (z = random * z there) and multiplies y by the second number, ours spills it and multiplies in SSE, best
	// 58.0 %
#ifdef NONMATCHING
	void SecondaryPhysicsAmbientWind::Slot5(ravenphysics::CollisionShape* shape, const math::Matrix* matrix)
	{
		math::Vector wind;
		matrix->Rotate(windForceScale, wind);
		float z;
		if (constantDirection)
		{
			float random = math::gRandom->Range(0.0f, 1.0f);
			wind.x = wind.x * random;
			wind.y = wind.y * random;
			z = random;
		}
		else
		{
			float randomX = math::gRandom->Range(0.0f, 1.0f);
			float randomY = math::gRandom->Range(0.0f, 1.0f);
			float randomZ = math::gRandom->Range(0.0f, 1.0f);
			wind.x = randomX * wind.x;
			wind.y = wind.y * randomY;
			z = randomZ;
		}
		wind.z = z * wind.z;
		if (wind.z * wind.z + wind.y * wind.y + wind.x * wind.x > 0.00001f)
		{
			float scale = shape->unknown88;
			math::Vector velocity;
			velocity.x = wind.x * scale;
			velocity.y = wind.y * scale;
			velocity.z = wind.z * scale;
			shape->AddVelocity(velocity, 1);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10916290
	content::MemberList* SecondaryPhysicsAmbientWind::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<SecondaryPhysicsJointDriver>();
		static content::BaseClassCasterImpl<SecondaryPhysicsJointDriver, SecondaryPhysicsAmbientWind> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<SecondaryPhysicsAmbientWind, 0>("pn"), 4, "windForceScale" },
			{ content::GetMemberPrimitiveMetaType<SecondaryPhysicsAmbientWind, bool, 0>("pn"),
				ENGINE_OFFSET(SecondaryPhysicsAmbientWind, constantDirection), "constantDirection" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109161C0
	SecondaryPhysicsAmbientWind::SecondaryPhysicsAmbientWind()
	{
		windForceScale.x = 1.0f;
		windForceScale.y = 1.0f;
		windForceScale.z = 1.0f;
		constantDirection = false;
	}

	// FUNCTION: ENGINE 0x10916360
	content::ClassInfo* SecondaryPhysicsPinJoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsPinJoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109163A0
	SecondaryPhysicsPinJoint::~SecondaryPhysicsPinJoint()
	{
	}

	// FUNCTION: ENGINE 0x109163B0
	int SecondaryPhysicsPinJoint::GetHandleCount()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10916480
	void SecondaryPhysicsPinJoint::Slot2(SecondaryPhysicsHandleRange* range)
	{
		ravenphysics::CollisionHandle* handle = range->begin;
		*handle = ravenphysics::CreateBallInSocketConstraint();
	}

	// FUNCTION: ENGINE 0x10916400
	SecondaryPhysicsPinJoint::SecondaryPhysicsPinJoint()
	{
		constraintPointOffset.x = 0.0f;
		constraintPointOffset.y = 0.0f;
		constraintPointOffset.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x109166E0
	content::MemberList* SecondaryPhysicsPinJoint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<SecondaryPhysicsJointDriver>();
		static content::BaseClassCasterImpl<SecondaryPhysicsJointDriver, SecondaryPhysicsPinJoint> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<SecondaryPhysicsPinJoint, 0>("pn"), 4, "constraintPointOffset" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10916790
	content::ClassInfo* SecondaryPhysicsPoweredJoint::ForceCurvePoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsPoweredJoint::ForceCurvePoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109167D0
	content::ClassInfo* SecondaryPhysicsPoweredJoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsPoweredJoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10916830
	float SecondaryPhysicsPoweredJoint::ForceCurvePoint::GetAngleDegrees() const
	{
		return angle * 57.2957764f;
	}

	// FUNCTION: ENGINE 0x10916840
	void SecondaryPhysicsPoweredJoint::ForceCurvePoint::SetAngleDegrees(float degrees)
	{
		angle = degrees * 0.0174532924f;
	}

	// FUNCTION: ENGINE 0x10916860
	int SecondaryPhysicsPoweredJoint::GetHandleCount()
	{
		if (dampingConstant > 0.00001f)
		{
			return 4;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10916970
	float SecondaryPhysicsPoweredJoint::GetMaxAngularVelocityDegrees() const
	{
		return maxAngularVelocity * 57.2957764f;
	}

	// FUNCTION: ENGINE 0x10916980
	void SecondaryPhysicsPoweredJoint::SetMaxAngularVelocityDegrees(float degrees)
	{
		maxAngularVelocity = degrees * 0.0174532924f;
	}

	// FUNCTION: ENGINE 0x10916AA0
	void SecondaryPhysicsPoweredJoint::Slot2(SecondaryPhysicsHandleRange* range)
	{
		int count = GetHandleCount();
		ravenphysics::CollisionHandle* handle = range->begin;
		*handle = ravenphysics::CreateMotorConstraint();
		if (count == 4)
		{
			handle = range->begin + 1;
			*handle = ravenphysics::CreateLimitConstraint();
			handle = range->begin + 2;
			*handle = ravenphysics::CreateLimitConstraint();
			handle = range->begin + 3;
			*handle = ravenphysics::CreateLimitConstraint();
		}
	}

	// FUNCTION: ENGINE 0x10916B90
	// EQUIVALENT: the engine keeps the previous point in esi and ours in ecx (so its frame and the loop entry differ), the
	// operations are the same, 21.9 %
	float SecondaryPhysicsPoweredJoint::EvaluateForceCurve(float angle) const
	{
		ForceCurvePoint* last = forceCurve.end;
		ForceCurvePoint* point = forceCurve.begin;
		float result = 0.0f;
		ForceCurvePoint* previous = last;
		if (point != last)
		{
			do
			{
				if (point->angle >= angle)
				{
					if (previous != last)
					{
						float previousAngle = previous->angle;
						float span = point->angle - previousAngle;
						if (span > 0.0001f)
						{
							float previousForce = previous->maxOrientationForce;
							result = ((angle - previousAngle) / span) * (point->maxOrientationForce - previousForce)
								+ previousForce;
							break;
						}
					}
					result = point->maxOrientationForce;
					break;
				}
				result = point->maxOrientationForce;
				previous = point;
				point++;
			}
			while (point != last);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10917530
	content::MemberList* SecondaryPhysicsPoweredJoint::ForceCurvePoint::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType(&ForceCurvePoint::GetAngleDegrees, &ForceCurvePoint::SetAngleDegrees, "pn"),
				0, "angleDegrees" },
			{ content::GetMemberPrimitiveMetaType<ForceCurvePoint, float, 0>("pn"),
				ENGINE_OFFSET(ForceCurvePoint, maxOrientationForce), "maxOrientationForce" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10917770
	content::MemberList* SecondaryPhysicsPoweredJoint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<SecondaryPhysicsJointDriver>();
		static content::BaseClassCasterImpl<SecondaryPhysicsJointDriver, SecondaryPhysicsPoweredJoint> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<SecondaryPhysicsPoweredJoint, ForceCurveArray>(
				content::GetClassMetaType<ForceCurvePoint>(), "pn"),
				ENGINE_OFFSET(SecondaryPhysicsPoweredJoint, forceCurve), "forceCurve" },
			{ content::GetMemberPrimitiveMetaType<SecondaryPhysicsPoweredJoint, float, 0>("pn"),
				ENGINE_OFFSET(SecondaryPhysicsPoweredJoint, dampingConstant), "dampingConstant" },
			{ content::GetMemberMetaType(&SecondaryPhysicsPoweredJoint::GetMaxAngularVelocityDegrees,
				&SecondaryPhysicsPoweredJoint::SetMaxAngularVelocityDegrees, "pn"), 0, "maxAngularVelocityDegrees" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10917900
	SecondaryPhysicsPoweredJoint::SecondaryPhysicsPoweredJoint()
	{
		dampingConstant = 0.0f;
		maxAngularVelocity = 0.0f;
	}

	// FUNCTION: ENGINE 0x10917930
	SecondaryPhysicsPoweredJoint::~SecondaryPhysicsPoweredJoint()
	{
	}
}

namespace container
{
	template class ArrayDynamic<engine::SecondaryPhysicsPoweredJoint::ForceCurvePoint, AllocatorNew>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10916010
// FUNCTION: ENGINE 0x10916190
// FUNCTION: ENGINE 0x109161F0
// FUNCTION: ENGINE 0x10916200
// FUNCTION: ENGINE 0x10916250
// FUNCTION: ENGINE 0x109163D0
// FUNCTION: ENGINE 0x10916420
// FUNCTION: ENGINE 0x10916430
// FUNCTION: ENGINE 0x10916810
// FUNCTION: ENGINE 0x109169C0
// FUNCTION: ENGINE 0x10916A60
// FUNCTION: ENGINE 0x10916A70
// FUNCTION: ENGINE 0x10916C40
// FUNCTION: ENGINE 0x10916C50
// FUNCTION: ENGINE 0x10916C90
// FUNCTION: ENGINE 0x10916CD0
// FUNCTION: ENGINE 0x10916CE0
// FUNCTION: ENGINE 0x10916D30
// FUNCTION: ENGINE 0x10916D50
// FUNCTION: ENGINE 0x10916D60
// FUNCTION: ENGINE 0x10916D70
// FUNCTION: ENGINE 0x10916D80
// FUNCTION: ENGINE 0x10916DD0
// FUNCTION: ENGINE 0x10916E00
// FUNCTION: ENGINE 0x10916E20
// FUNCTION: ENGINE 0x10916E30
// FUNCTION: ENGINE 0x10916E50
// FUNCTION: ENGINE 0x10916E60
// FUNCTION: ENGINE 0x10916E70
// FUNCTION: ENGINE 0x10916E80
// FUNCTION: ENGINE 0x10916E90
// FUNCTION: ENGINE 0x10916EB0
// FUNCTION: ENGINE 0x10916EC0
// FUNCTION: ENGINE 0x10917350
// FUNCTION: ENGINE 0x109173C0
// FUNCTION: ENGINE 0x10917410
// FUNCTION: ENGINE 0x10917490
// FUNCTION: ENGINE 0x109174D0
// FUNCTION: ENGINE 0x10917500
// FUNCTION: ENGINE 0x109175E0
// FUNCTION: ENGINE 0x10917630
// FUNCTION: ENGINE 0x10917680
// FUNCTION: ENGINE 0x109178A0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10916A30
