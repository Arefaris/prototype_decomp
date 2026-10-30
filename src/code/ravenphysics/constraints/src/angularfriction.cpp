// The angular friction constraint and the reflection of it (the unit after the constraint base class's users; no assert path
// of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintAngularFriction>;

	// FUNCTION: ENGINE 0x10691F20
	content::ClassInfo* ConstraintAngularFriction::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintAngularFriction";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10691F60
	ConstraintAngularFriction::ConstraintAngularFriction() :
		Constraint(3),
		friction(0.2f)
	{
	}

	// FUNCTION: ENGINE 0x10691FA0
	ConstraintAngularFriction::ConstraintAngularFriction(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 3),
		friction(0.2f)
	{
	}

	// FUNCTION: ENGINE 0x10691FD0
	void ConstraintAngularFriction::SetFriction(float value)
	{
		friction = value;
	}

	// FUNCTION: ENGINE 0x10691FE0
	unsigned short ConstraintAngularFriction::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10692090
	content::MemberList* ConstraintAngularFriction::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintAngularFriction> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstraintAngularFriction, float, 0>("p"),
				content::MemberOffset(&((ConstraintAngularFriction*)0)->friction,
				(int)&((ConstraintAngularFriction*)0)->friction), "friction" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// Kept copies: the destructor, the caster, the deleting destructor and the meta type getter of the reflection above
	// FUNCTION: ENGINE 0x10691F90
	// FUNCTION: ENGINE 0x10691FF0
	// FUNCTION: ENGINE 0x10692000
	// FUNCTION: ENGINE 0x10692030
	// FUNCTION: ENGINE 0x10692050
}
