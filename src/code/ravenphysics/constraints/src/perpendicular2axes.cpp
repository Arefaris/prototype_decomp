// The perpendicular axes constraint and the reflection of it (no assert path of its own; the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintPerpendicular2Axes>;

	// FUNCTION: ENGINE 0x106707B0
	const math::Vector* ConstraintPerpendicular2Axes::GetAxisA() const
	{
		return &axisA;
	}

	// FUNCTION: ENGINE 0x106707C0
	const math::Vector* ConstraintPerpendicular2Axes::GetAxisB() const
	{
		return &axisB;
	}

	// FUNCTION: ENGINE 0x106707D0
	content::ClassInfo* ConstraintPerpendicular2Axes::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintPerpendicular2Axes";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10670810
	unsigned short ConstraintPerpendicular2Axes::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10670820
	void ConstraintPerpendicular2Axes::SetAxisA(const math::Vector* axis)
	{
		math::Vector* target = &axisA;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
		axisALocal.x = target->x;
		axisALocal.y = target->y;
		axisALocal.z = target->z;
	}

	// FUNCTION: ENGINE 0x10670860
	void ConstraintPerpendicular2Axes::SetAxisB(const math::Vector* axis)
	{
		math::Vector* target = &axisB;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x10670890
	void ConstraintPerpendicular2Axes::Rotate(const math::Matrix* matrix)
	{
		matrix->Rotate(axisALocal, axisA);
	}

	// FUNCTION: ENGINE 0x106708B0
	ConstraintPerpendicular2Axes::ConstraintPerpendicular2Axes() :
		Constraint(0xE)
	{
		math::Vector up(0.0f, 1.0f, 0.0f);
		SetAxisA(&up);
		math::Vector up2(0.0f, 1.0f, 0.0f);
		SetAxisB(&up2);
		unknown48 = 0.0f;
		unknown4C = 0.0f;
	}

	// FUNCTION: ENGINE 0x106709A0
	ConstraintPerpendicular2Axes::ConstraintPerpendicular2Axes(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 0xE)
	{
		math::Vector up(0.0f, 1.0f, 0.0f);
		SetAxisA(&up);
		math::Vector up2(0.0f, 1.0f, 0.0f);
		SetAxisB(&up2);
		unknown48 = 0.0f;
		unknown4C = 0.0f;
	}

	// FUNCTION: ENGINE 0x10670B60
	content::MemberList* ConstraintPerpendicular2Axes::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintPerpendicular2Axes> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintPerpendicular2Axes, 0>(&ConstraintPerpendicular2Axes::GetAxisA,
				&ConstraintPerpendicular2Axes::SetAxisA, "pn"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintPerpendicular2Axes, 1>(&ConstraintPerpendicular2Axes::GetAxisB,
				&ConstraintPerpendicular2Axes::SetAxisB, "pn"), 0, "axisB" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x10670930
	// FUNCTION: ENGINE 0x10670940
	// FUNCTION: ENGINE 0x10670950
	// FUNCTION: ENGINE 0x10670980
	// FUNCTION: ENGINE 0x10670A30
	// FUNCTION: ENGINE 0x10670A50
	// FUNCTION: ENGINE 0x10670A60
	// FUNCTION: ENGINE 0x10670A80
	// FUNCTION: ENGINE 0x10670AF0
}

template class VectorMemberGetSetter<ravenphysics::ConstraintPerpendicular2Axes>;
