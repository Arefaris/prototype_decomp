// The powered orientation constraint, its shared properties and the reflection of them (no assert path of its own, so the
// file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintPoweredConstraint>;

	// FUNCTION: ENGINE 0x106939A0
	content::ClassInfo* ConstraintPoweredConstraint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintPoweredConstraint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x106939E0
	content::ClassInfo* PoweredConstraintSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::PoweredConstraintSharedProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10693A20
	ConstraintPoweredConstraint::ConstraintPoweredConstraint() :
		Constraint(15),
		maxAngularVelocity(0.0f),
		maxOrientationForce(0.0f)
	{
		matrix.Identity();
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
		unknown70 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10693A80
	ConstraintPoweredConstraint::ConstraintPoweredConstraint(const CollisionHandle* first,
		const CollisionHandle* second) :
		Constraint(first, second, 15),
		maxAngularVelocity(0.0f),
		maxOrientationForce(0.0f)
	{
		matrix.Identity();
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
		unknown70 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10693AF0
	ConstraintPoweredConstraint::~ConstraintPoweredConstraint()
	{
	}

	// FUNCTION: ENGINE 0x10693B00
	void ConstraintPoweredConstraint::SetSharedProperties(const PoweredConstraintSharedProperties* properties)
	{
		if (properties)
		{
			maxAngularVelocity = properties->maxAngularVelocity;
			maxOrientationForce = properties->maxOrientationForce;
		}
	}

	// FUNCTION: ENGINE 0x10693B20
	unsigned short ConstraintPoweredConstraint::GetKind(int unused)
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x10693B30
	void ConstraintPoweredConstraint::SetMatrix(const math::Matrix3* newMatrix)
	{
		matrix.m[0][0] = newMatrix->m[0][0];
		matrix.m[0][1] = newMatrix->m[0][1];
		matrix.m[0][2] = newMatrix->m[0][2];
		matrix.m[1][0] = newMatrix->m[1][0];
		matrix.m[1][1] = newMatrix->m[1][1];
		matrix.m[1][2] = newMatrix->m[1][2];
		matrix.m[2][0] = newMatrix->m[2][0];
		matrix.m[2][1] = newMatrix->m[2][1];
		matrix.m[2][2] = newMatrix->m[2][2];
	}

	// FUNCTION: ENGINE 0x10693B70
	void ConstraintPoweredConstraint::SetMaxAngularVelocity(float value)
	{
		maxAngularVelocity = value;
	}

	// FUNCTION: ENGINE 0x10693B80
	void ConstraintPoweredConstraint::SetMaxOrientationForce(float value)
	{
		maxOrientationForce = value;
	}

	// FUNCTION: ENGINE 0x10693B90
	// EQUIVALENT: the same stores; the engine stores the reference count and the first member ahead of the other member, 66.7 %
	PoweredConstraintSharedProperties::PoweredConstraintSharedProperties() :
		maxAngularVelocity(3.0f),
		maxOrientationForce(30.0f)
	{
	}

	// FUNCTION: ENGINE 0x10693CE0
	content::MemberList* ConstraintPoweredConstraint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintPoweredConstraint> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10693D40
	content::MemberList* PoweredConstraintSharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PoweredConstraintSharedProperties, float, 0>("pn"),
				content::MemberOffset(&((PoweredConstraintSharedProperties*)0)->maxAngularVelocity,
				(int)&((PoweredConstraintSharedProperties*)0)->maxAngularVelocity), "maxAngularVelocity" },
			{ content::GetMemberPrimitiveMetaType<PoweredConstraintSharedProperties, float, 1>("pn"),
				content::MemberOffset(&((PoweredConstraintSharedProperties*)0)->maxOrientationForce,
				(int)&((PoweredConstraintSharedProperties*)0)->maxOrientationForce), "maxOrientationForce" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies: the casters, the deleting destructors and the meta type getters of the reflection above
	// FUNCTION: ENGINE 0x10693BD0
	// FUNCTION: ENGINE 0x10693BE0
	// FUNCTION: ENGINE 0x10693C10
	// FUNCTION: ENGINE 0x10693C30
	// FUNCTION: ENGINE 0x10693C60
	// FUNCTION: ENGINE 0x10693CA0
}
