// The spring constraint and the reflection of it (no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintSpring>;

	// FUNCTION: ENGINE 0x106946C0
	content::ClassInfo* ConstraintSpring::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintSpring";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10694700
	ConstraintSpring::ConstraintSpring() :
		Constraint(20),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		stableDistance(1.0f),
		springConstant(1.0f),
		dampingConstant(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x10694760
	ConstraintSpring::ConstraintSpring(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 20),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		stableDistance(1.0f),
		springConstant(1.0f),
		dampingConstant(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x106947C0
	unsigned short ConstraintSpring::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x106947D0
	// EQUIVALENT: the same products in the same order; the engine multiplies each loaded component by the held one, ours folds the loads into the products and stores them later, 30.5 %
	void ConstraintSpring::ScaleBy(const math::Vector* scale)
	{
		ScaleComponents(pointA, *scale);
		ScaleComponents(pointB, *scale);
	}

	// FUNCTION: ENGINE 0x10694840
	void ConstraintSpring::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x10694860
	void ConstraintSpring::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x10694880
	void ConstraintSpring::SetStableDistance(float value)
	{
		stableDistance = value;
	}

	// FUNCTION: ENGINE 0x10694890
	void ConstraintSpring::SetSpringConstant(float value)
	{
		springConstant = value;
	}

	// FUNCTION: ENGINE 0x106948A0
	void ConstraintSpring::SetDampingConstant(float value)
	{
		dampingConstant = value;
	}

	// FUNCTION: ENGINE 0x10694A30
	content::MemberList* ConstraintSpring::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintSpring> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintSpring, 0>("p"),
				(int)&((ConstraintSpring*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintSpring, 1>("p"),
				(int)&((ConstraintSpring*)0)->pointB, "pointB" },
			{ content::GetMemberPrimitiveMetaType<ConstraintSpring, float, 0>("n"),
				content::MemberOffset(&((ConstraintSpring*)0)->springConstant,
				(int)&((ConstraintSpring*)0)->springConstant), "springConstant" },
			{ content::GetMemberPrimitiveMetaType<ConstraintSpring, float, 1>("p"),
				content::MemberOffset(&((ConstraintSpring*)0)->dampingConstant,
				(int)&((ConstraintSpring*)0)->dampingConstant), "dampingConstant" },
			{ content::GetMemberPrimitiveMetaType<ConstraintSpring, float, 2>("p"),
				content::MemberOffset(&((ConstraintSpring*)0)->stableDistance,
				(int)&((ConstraintSpring*)0)->stableDistance), "stableDistance" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the deleting destructor and the meta type getters of the reflection above
	// FUNCTION: ENGINE 0x10694750
	// FUNCTION: ENGINE 0x106948B0
	// FUNCTION: ENGINE 0x106948E0
	// FUNCTION: ENGINE 0x10694910
	// FUNCTION: ENGINE 0x10694920
	// FUNCTION: ENGINE 0x10694950
	// FUNCTION: ENGINE 0x10694970
	// FUNCTION: ENGINE 0x106949B0
	// FUNCTION: ENGINE 0x106949F0
}
