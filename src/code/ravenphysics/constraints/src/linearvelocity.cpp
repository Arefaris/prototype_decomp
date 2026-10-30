// The linear velocity constraint and the reflection of it (no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintLinearVelocity>;

	// FUNCTION: ENGINE 0x10693600
	content::ClassInfo* ConstraintLinearVelocity::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintLinearVelocity";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10693640
	ConstraintLinearVelocity::ConstraintLinearVelocity() :
		Constraint(13),
		axis(0.0f, 1.0f, 0.0f),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		linearVelocity(0.0f),
		maxForce(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x106936B0
	ConstraintLinearVelocity::ConstraintLinearVelocity(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 13),
		axis(0.0f, 1.0f, 0.0f),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		linearVelocity(0.0f),
		maxForce(1000.0f)
	{
	}

	// FUNCTION: ENGINE 0x10693720
	unsigned short ConstraintLinearVelocity::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10693730
	void ConstraintLinearVelocity::SetLinearVelocity(float value)
	{
		linearVelocity = value;
	}

	// FUNCTION: ENGINE 0x10693740
	void ConstraintLinearVelocity::SetMaxForce(float value)
	{
		maxForce = value;
	}

	// FUNCTION: ENGINE 0x10693750
	void ConstraintLinearVelocity::SetAxis(const math::Vector* newAxis)
	{
		math::Vector* target = &axis;
		target->x = newAxis->x;
		target->y = newAxis->y;
		target->z = newAxis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x10693780
	void ConstraintLinearVelocity::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x106937A0
	void ConstraintLinearVelocity::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x106938B0
	content::MemberList* ConstraintLinearVelocity::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintLinearVelocity> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintLinearVelocity, 0>("p"),
				(int)&((ConstraintLinearVelocity*)0)->axis, "axisB" },
			{ content::GetMemberVectorMetaType<ConstraintLinearVelocity, 1>("p"),
				(int)&((ConstraintLinearVelocity*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintLinearVelocity, 2>("p"),
				(int)&((ConstraintLinearVelocity*)0)->pointB, "pointB" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the deleting destructor and the meta type getters of the reflection above
	// FUNCTION: ENGINE 0x106936A0
	// FUNCTION: ENGINE 0x106937C0
	// FUNCTION: ENGINE 0x106937F0
	// FUNCTION: ENGINE 0x10693820
	// FUNCTION: ENGINE 0x10693850
	// FUNCTION: ENGINE 0x10693860
	// FUNCTION: ENGINE 0x10693890
}
