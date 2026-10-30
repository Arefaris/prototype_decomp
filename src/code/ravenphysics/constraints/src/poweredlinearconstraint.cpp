// The powered linear constraint and its shared properties (no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintPoweredLinearConstraint>;

	// FUNCTION: ENGINE 0x10693DF0
	content::ClassInfo* ConstraintPoweredLinearConstraint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintPoweredLinearConstraint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10693E30
	content::ClassInfo* PoweredLinearConstraintSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::PoweredLinearConstraintSharedProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10693E70
	ConstraintPoweredLinearConstraint::ConstraintPoweredLinearConstraint() :
		Constraint(16),
		maxLinearVelocity(0.0f),
		maxLinearForce(0.0f),
		alignmentRigidity(0.1f),
		flag(false)
	{
		pointA.z = 0.0f;
		pointA.y = 0.0f;
		pointA.x = 0.0f;
		pointB.z = 0.0f;
		pointB.y = 0.0f;
		pointB.x = 0.0f;
		unknown48 = 0.0f;
		unknown4C = 0.0f;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10693EF0
	ConstraintPoweredLinearConstraint::ConstraintPoweredLinearConstraint(const CollisionHandle* first,
		const CollisionHandle* second) :
		Constraint(first, second, 16),
		maxLinearVelocity(0.0f),
		maxLinearForce(0.0f),
		alignmentRigidity(0.1f),
		flag(false)
	{
		pointA.z = 0.0f;
		pointA.y = 0.0f;
		pointA.x = 0.0f;
		pointB.z = 0.0f;
		pointB.y = 0.0f;
		pointB.x = 0.0f;
		unknown48 = 0.0f;
		unknown4C = 0.0f;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10693F80
	ConstraintPoweredLinearConstraint::~ConstraintPoweredLinearConstraint()
	{
	}

	// FUNCTION: ENGINE 0x10693F90
	void ConstraintPoweredLinearConstraint::SetSharedProperties(const PoweredLinearConstraintSharedProperties* properties)
	{
		if (properties)
		{
			maxLinearVelocity = properties->maxLinearVelocity;
			maxLinearForce = properties->maxLinearForce;
		}
	}

	// FUNCTION: ENGINE 0x10693FB0
	bool ConstraintPoweredLinearConstraint::GetFlag() const
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x10693FC0
	void ConstraintPoweredLinearConstraint::SetFlag(bool value)
	{
		flag = value;
	}

	// FUNCTION: ENGINE 0x10693FD0
	unsigned short ConstraintPoweredLinearConstraint::GetKind(int unused)
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x10693FE0
	void ConstraintPoweredLinearConstraint::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x10694000
	void ConstraintPoweredLinearConstraint::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x10694020
	void ConstraintPoweredLinearConstraint::SetMaxLinearVelocity(float value)
	{
		maxLinearVelocity = value;
	}

	// FUNCTION: ENGINE 0x10694030
	void ConstraintPoweredLinearConstraint::SetMaxLinearForce(float value)
	{
		maxLinearForce = value;
	}

	// FUNCTION: ENGINE 0x10694040
	void ConstraintPoweredLinearConstraint::SetAlignmentRigidity(float value)
	{
		if (!(value >= 0.0f))
		{
			value = 0.0f;
		}
		if (value - 1.0f >= 0.0f)
		{
			alignmentRigidity = 1.0f;
		}
		else
		{
			alignmentRigidity = value;
		}
	}

	// FUNCTION: ENGINE 0x10694080
	// EQUIVALENT: the same stores; the engine stores the reference count and the first member ahead of the other members, 55.7 %
	PoweredLinearConstraintSharedProperties::PoweredLinearConstraintSharedProperties() :
		maxLinearVelocity(3.0f),
		maxLinearForce(30.0f),
		alignmentRigidity(0.1f)
	{
	}

	// FUNCTION: ENGINE 0x10694220
	content::MemberList* ConstraintPoweredLinearConstraint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintPoweredLinearConstraint> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// Kept copies: the casters, the deleting destructors of the reflection above
	// FUNCTION: ENGINE 0x106940C0
	// FUNCTION: ENGINE 0x106940D0
	// FUNCTION: ENGINE 0x106940E0
	// FUNCTION: ENGINE 0x10694110
	// FUNCTION: ENGINE 0x10694130
}
