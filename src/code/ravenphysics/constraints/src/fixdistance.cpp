// The fixed distance constraint and the reflection of it (no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintFixDistance>;

	// FUNCTION: ENGINE 0x10693250
	content::ClassInfo* ConstraintFixDistance::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintFixDistance";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10693290
	ConstraintFixDistance::ConstraintFixDistance() :
		Constraint(8),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		distance(0.0f),
		unknown40(1e12f),
		unknown44(1e12f)
	{
	}

	// FUNCTION: ENGINE 0x106932F0
	ConstraintFixDistance::ConstraintFixDistance(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 8)
	{
	}

	// FUNCTION: ENGINE 0x10693320
	void ConstraintFixDistance::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x10693340
	void ConstraintFixDistance::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x10693360
	void ConstraintFixDistance::SetDistance(float value)
	{
		distance = value;
	}

	// FUNCTION: ENGINE 0x10693370
	void ConstraintFixDistance::SetUnknown40(float value)
	{
		unknown40 = value;
	}

	// FUNCTION: ENGINE 0x10693380
	void ConstraintFixDistance::SetUnknown44(float value)
	{
		unknown44 = value;
	}

	// FUNCTION: ENGINE 0x10693390
	unsigned short ConstraintFixDistance::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x106933A0
	// EQUIVALENT: the same products in the same order; the engine multiplies each loaded component by the held one, ours folds the loads into the products and stores them later, 30.5 %
	void ConstraintFixDistance::ScaleBy(const math::Vector* scale)
	{
		ScaleComponents(pointA, *scale);
		ScaleComponents(pointB, *scale);
	}

	// FUNCTION: ENGINE 0x10693510
	content::MemberList* ConstraintFixDistance::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintFixDistance> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintFixDistance, 0>("p"),
				(int)&((ConstraintFixDistance*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintFixDistance, 1>("p"),
				(int)&((ConstraintFixDistance*)0)->pointB, "pointB" },
			{ content::GetMemberPrimitiveMetaType<ConstraintFixDistance, float, 0>("p"),
				content::MemberOffset(&((ConstraintFixDistance*)0)->distance,
				(int)&((ConstraintFixDistance*)0)->distance), "distance" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the deleting destructor and the meta type getters of the reflection above
	// FUNCTION: ENGINE 0x106932E0
	// FUNCTION: ENGINE 0x10693410
	// FUNCTION: ENGINE 0x10693440
	// FUNCTION: ENGINE 0x10693470
	// FUNCTION: ENGINE 0x10693480
	// FUNCTION: ENGINE 0x106934B0
	// FUNCTION: ENGINE 0x106934D0
}
