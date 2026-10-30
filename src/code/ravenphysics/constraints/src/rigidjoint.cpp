// The rigid joint constraint and the reflection of it (no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintRigidJoint>;

	// FUNCTION: ENGINE 0x10694350
	content::ClassInfo* ConstraintRigidJoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintRigidJoint";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10694390
	ConstraintRigidJoint::ConstraintRigidJoint() :
		Constraint(17),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		basis.Identity();
	}

	// FUNCTION: ENGINE 0x106943E0
	ConstraintRigidJoint::ConstraintRigidJoint(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 17),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		basis.Identity();
	}

	// FUNCTION: ENGINE 0x10694430
	unsigned short ConstraintRigidJoint::GetKind(int unused)
	{
		return 6;
	}

	// FUNCTION: ENGINE 0x10694440
	// EQUIVALENT: the same products in the same order; the engine multiplies each loaded component by the held one, ours folds the loads into the products and stores them later, 30.5 %
	void ConstraintRigidJoint::ScaleBy(const math::Vector* scale)
	{
		ScaleComponents(pointA, *scale);
		ScaleComponents(pointB, *scale);
	}

	// FUNCTION: ENGINE 0x106944B0
	void ConstraintRigidJoint::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x106944D0
	void ConstraintRigidJoint::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x106944F0
	void ConstraintRigidJoint::SetBasis(const math::Matrix3* newBasis)
	{
		basis.m[0][0] = newBasis->m[0][0];
		basis.m[0][1] = newBasis->m[0][1];
		basis.m[0][2] = newBasis->m[0][2];
		basis.m[1][0] = newBasis->m[1][0];
		basis.m[1][1] = newBasis->m[1][1];
		basis.m[1][2] = newBasis->m[1][2];
		basis.m[2][0] = newBasis->m[2][0];
		basis.m[2][1] = newBasis->m[2][1];
		basis.m[2][2] = newBasis->m[2][2];
	}

	// FUNCTION: ENGINE 0x106945F0
	content::MemberList* ConstraintRigidJoint::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintRigidJoint> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintRigidJoint, 0>("p"),
				(int)&((ConstraintRigidJoint*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintRigidJoint, 1>("p"),
				(int)&((ConstraintRigidJoint*)0)->pointB, "pointB" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the deleting destructor and the meta type getters of the reflection above
	// FUNCTION: ENGINE 0x106943D0
	// FUNCTION: ENGINE 0x10694530
	// FUNCTION: ENGINE 0x10694560
	// FUNCTION: ENGINE 0x10694590
	// FUNCTION: ENGINE 0x106945A0
	// FUNCTION: ENGINE 0x106945D0
}
