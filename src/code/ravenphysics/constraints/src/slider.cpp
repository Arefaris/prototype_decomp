// The slider constraint and the reflection of it (no assert path of its own; the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraint.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintSlider>;

	// FUNCTION: ENGINE 0x1066F5C0
	const math::Vector* ConstraintSlider::GetAxisA() const
	{
		return &axisA;
	}

	// FUNCTION: ENGINE 0x1066F5D0
	const math::Vector* ConstraintSlider::GetPointA() const
	{
		return &pointA;
	}

	// FUNCTION: ENGINE 0x1066F5E0
	content::ClassInfo* ConstraintSlider::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintSlider";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066F620
	unsigned short ConstraintSlider::GetKind(int unused)
	{
		return 2;
	}

	// A scaled component by component by b, the stored value first
	static inline void ScaleVector(math::Vector& a, const math::Vector* b)
	{
		float y = b->y;
		float z = b->z;
		float x = b->x;
		a.x = a.x * x;
		a.y = a.y * y;
		a.z = a.z * z;
	}

	// FUNCTION: ENGINE 0x1066F630
	// EQUIVALENT: the same products; the engine multiplies the x of the second and third vector with the scale in the other operand order, 96.4 %
	void ConstraintSlider::ScaleBy(const math::Vector* scale)
	{
		ScaleVector(pointA, scale);
		ScaleVector(pointALocal, scale);
		ScaleVector(pointB, scale);
	}

	// FUNCTION: ENGINE 0x1066F6E0
	void ConstraintSlider::UpdatePerpendicular()
	{
		const math::Vector* axis = &axisA;
		math::Vector* target = &perpendicular;
		target->Perpendicular(*axis);
		target->Normalize();
		cross.CrossProduct(*axis, *target);
		cross.Normalize();
	}

	// FUNCTION: ENGINE 0x1066F720
	void ConstraintSlider::SetAxisA(const math::Vector* axis)
	{
		math::Vector* target = &axisA;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
		axisALocal.x = target->x;
		axisALocal.y = target->y;
		axisALocal.z = target->z;
		UpdatePerpendicular();
	}

	// FUNCTION: ENGINE 0x1066F770
	void ConstraintSlider::SetExtent(float value)
	{
		extent = value;
	}

	// FUNCTION: ENGINE 0x1066F790
	void ConstraintSlider::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
		pointALocal.x = point->x;
		pointALocal.y = point->y;
		pointALocal.z = point->z;
	}

	// FUNCTION: ENGINE 0x1066F7C0
	void ConstraintSlider::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x1066F810
	ConstraintSlider::ConstraintSlider() :
		Constraint(0x12),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		float one = 1.0f;
		extent = one;
		math::Vector up(0.0f, one, 0.0f);
		SetAxisA(&up);
	}

	// FUNCTION: ENGINE 0x1066F8F0
	ConstraintSlider::ConstraintSlider(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 0x12),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		float one = 1.0f;
		extent = one;
		math::Vector up(0.0f, one, 0.0f);
		SetAxisA(&up);
	}

	// FUNCTION: ENGINE 0x1066F970
	void ConstraintSlider::Rotate(const math::Matrix* matrix)
	{
		matrix->Transform(pointALocal, pointA);
		matrix->Rotate(axisALocal, axisA);
		UpdatePerpendicular();
	}

	// FUNCTION: ENGINE 0x1066FB20
	content::MemberList* ConstraintSlider::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintSlider> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintSlider, 0>(&ConstraintSlider::GetPointA,
				&ConstraintSlider::SetPointA, "p"), 0, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintSlider, 1>(&ConstraintSlider::GetAxisA,
				&ConstraintSlider::SetAxisA, "p"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintSlider, 2>("p"), (int)&((ConstraintSlider*)0)->pointB,
				"pointB" },
			{ content::GetMemberPrimitiveMetaType<ConstraintSlider, float, 0>("p"),
				content::MemberOffset(&((ConstraintSlider*)0)->extent, (int)&((ConstraintSlider*)0)->extent), "extent" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x1066F880
	// FUNCTION: ENGINE 0x1066F890
	// FUNCTION: ENGINE 0x1066F8A0
	// FUNCTION: ENGINE 0x1066F8D0
	// FUNCTION: ENGINE 0x1066F7E0
	// FUNCTION: ENGINE 0x1066F9B0
	// FUNCTION: ENGINE 0x1066F9F0
	// FUNCTION: ENGINE 0x1066FA10
	// FUNCTION: ENGINE 0x1066FA20
	// FUNCTION: ENGINE 0x1066FA40
	// FUNCTION: ENGINE 0x1066FAB0
}

template class VectorMemberGetSetter<ravenphysics::ConstraintSlider>;
