// The universal joint constraint (a ball in a socket and two perpendicular axes) and the reflection of it (no assert path of
// its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintUniversalJoint>;

	// FUNCTION: ENGINE 0x10694B70
	const math::Vector* ConstraintUniversalJoint::GetAxisA() const
	{
		return &perp.axisA;
	}

	// FUNCTION: ENGINE 0x10694B80
	const math::Vector* ConstraintUniversalJoint::GetAxisB() const
	{
		return &perp.axisB;
	}

	// FUNCTION: ENGINE 0x10694B90
	const math::Vector* ConstraintUniversalJoint::GetPointA() const
	{
		return &ball.pointA;
	}

	// FUNCTION: ENGINE 0x10694BA0
	const math::Vector* ConstraintUniversalJoint::GetPointB() const
	{
		return &ball.pointB;
	}

	// FUNCTION: ENGINE 0x10694BB0
	content::ClassInfo* ConstraintUniversalJoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintUniversalJoint";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10694BF0
	ConstraintUniversalJoint::ConstraintUniversalJoint(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 21),
		ball(first, second),
		perp(first, second)
	{
	}

	// FUNCTION: ENGINE 0x10694C50
	unsigned short ConstraintUniversalJoint::GetKind(int unused)
	{
		return 4;
	}

	// FUNCTION: ENGINE 0x10694C60
	void ConstraintUniversalJoint::ScaleBy(const math::Vector* scale)
	{
		static_cast<Constraint&>(ball).ScaleBy(scale);
		static_cast<Constraint&>(perp).ScaleBy(scale);
	}

	// FUNCTION: ENGINE 0x10694C90
	void ConstraintUniversalJoint::SetAxisA(const math::Vector* axis)
	{
		perp.SetAxisA(axis);
	}

	// FUNCTION: ENGINE 0x10694CA0
	void ConstraintUniversalJoint::SetAxisB(const math::Vector* axis)
	{
		perp.SetAxisB(axis);
	}

	// FUNCTION: ENGINE 0x10694CB0
	void ConstraintUniversalJoint::Rotate(const math::Matrix* matrix)
	{
		static_cast<Constraint&>(ball).Rotate(matrix);
		static_cast<Constraint&>(perp).Rotate(matrix);
	}

	// FUNCTION: ENGINE 0x10694CE0
	void ConstraintUniversalJoint::SetPointA(const math::Vector* point)
	{
		ball.SetPointA(point);
	}

	// FUNCTION: ENGINE 0x10694CF0
	void ConstraintUniversalJoint::SetPointB(const math::Vector* point)
	{
		ball.SetPointB(point);
	}

	// FUNCTION: ENGINE 0x10694D00
	ConstraintUniversalJoint::ConstraintUniversalJoint() :
		Constraint(21)
	{
	}

	// FUNCTION: ENGINE 0x10694FC0
	content::MemberList* ConstraintUniversalJoint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintUniversalJoint> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintUniversalJoint, 0>(&ConstraintUniversalJoint::GetPointA,
				&ConstraintUniversalJoint::SetPointA, "p"), 0, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintUniversalJoint, 1>(&ConstraintUniversalJoint::GetAxisA,
				&ConstraintUniversalJoint::SetAxisA, "p"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintUniversalJoint, 2>(&ConstraintUniversalJoint::GetPointB,
				&ConstraintUniversalJoint::SetPointB, "p"), 0, "pointB" },
			{ content::GetMemberVectorMetaType<ConstraintUniversalJoint, 3>(&ConstraintUniversalJoint::GetAxisB,
				&ConstraintUniversalJoint::SetAxisB, "p"), 0, "axisB" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the deleting destructor and the reflection helpers of the reflection above
	// FUNCTION: ENGINE 0x10694C30
	// FUNCTION: ENGINE 0x10694D30
	// FUNCTION: ENGINE 0x10694D40
	// FUNCTION: ENGINE 0x10694D70
	// FUNCTION: ENGINE 0x10694DB0
	// FUNCTION: ENGINE 0x10694DD0
	// FUNCTION: ENGINE 0x10694DE0
	// FUNCTION: ENGINE 0x10694E00
	// FUNCTION: ENGINE 0x10694E70
	// FUNCTION: ENGINE 0x10694EE0
	// FUNCTION: ENGINE 0x10694F50
}

template class VectorMemberGetSetter<ravenphysics::ConstraintUniversalJoint>;
