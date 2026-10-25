// The constraints of ravenphysics and the reflection of them (the assert path of the unit is
// code/ravenphysics/constraints/src/constraints.cpp).
#include "code/content/vectormetatype.h"
#include "code/math/sincos.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1065E3E0
	// EQUIVALENT: the same stores in the same order; the engine keeps the kind in cx and minus one in edx, ours the other way round, 46.8 %
	Constraint::Constraint(int newKind)
	{
		handle.value = 0xffffffff;
		kind = (unsigned short)newKind;
		unknownC = 0;
		first.value = 0xffffffff;
		second.value = 0xffffffff;
		detector = 0;
		firstObject = 0;
		secondObject = 0;
	}

	// FUNCTION: ENGINE 0x1065CD80
	Constraint::~Constraint()
	{
		if (handle.IsValid())
		{
			gCollisionObjectTable->Remove(&handle);
		}
	}

	// The reflection of the bases' casters, kept as out-of-line instances
	template struct content::BaseClassCasterImpl<Constraint, ConstraintInsideOfSphere>;

	// FUNCTION: ENGINE 0x10661540
	content::ClassInfo* ConstraintInsideOfSphere::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintInsideOfSphere";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10661580
	ConstraintInsideOfSphere::ConstraintInsideOfSphere() :
		Constraint(12),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		sphereRadius(1.0f),
		unknown40(1e12f),
		unknown44(1e12f)
	{
	}

	// FUNCTION: ENGINE 0x106615F0
	ConstraintInsideOfSphere::ConstraintInsideOfSphere(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 12),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		sphereRadius(1.0f),
		unknown40(1e12f),
		unknown44(1e12f)
	{
	}

	// FUNCTION: ENGINE 0x10661660
	void ConstraintInsideOfSphere::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x10661680
	void ConstraintInsideOfSphere::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x106616A0
	void ConstraintInsideOfSphere::SetSphereRadius(float value)
	{
		sphereRadius = value;
	}

	// FUNCTION: ENGINE 0x106616B0
	void ConstraintInsideOfSphere::SetUnknown40(float value)
	{
		unknown40 = value;
	}

	// FUNCTION: ENGINE 0x106616C0
	void ConstraintInsideOfSphere::SetUnknown44(float value)
	{
		unknown44 = value;
	}

	// FUNCTION: ENGINE 0x106616D0
	unsigned short ConstraintInsideOfSphere::GetKind(int unused)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106616E0
	// EQUIVALENT: the same products; the engine loads the stored value ahead of the scale component for y and z, ours the scale first, 30.5 %
	void ConstraintInsideOfSphere::ScaleBy(const math::Vector* scale)
	{
		Multiply(pointA, *scale);
		Multiply(pointB, *scale);
	}

#define CONSTRAINT_VECTOR_MEMBER(Class, index, member) \
	{ content::GetMemberVectorMetaType<Class, index>("p"), (int)&((Class*)0)->member, #member }
#define CONSTRAINT_FLOAT_MEMBER(Class, index, member) \
	{ content::GetMemberPrimitiveMetaType<Class, float, index>("p"), \
		content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member), #member }

	// FUNCTION: ENGINE 0x10661850
	content::MemberList* ConstraintInsideOfSphere::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintInsideOfSphere> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			CONSTRAINT_VECTOR_MEMBER(ConstraintInsideOfSphere, 0, pointA),
			CONSTRAINT_VECTOR_MEMBER(ConstraintInsideOfSphere, 1, pointB),
			CONSTRAINT_FLOAT_MEMBER(ConstraintInsideOfSphere, 2, sphereRadius)
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	template struct content::BaseClassCasterImpl<Constraint, ConstraintInsideOfCone>;

	// FUNCTION: ENGINE 0x1066AB00
	content::ClassInfo* ConstraintInsideOfCone::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintInsideOfCone";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066AB40
	ConstraintInsideOfCone::ConstraintInsideOfCone() :
		Constraint(11),
		axisA(0.0f, 1.0f, 0.0f),
		axisALocal(0.0f, 1.0f, 0.0f),
		axisB(0.0f, 1.0f, 0.0f),
		sine(1.0f),
		cosine(0.0f)
	{
		flag = false;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1066ABC0
	ConstraintInsideOfCone::ConstraintInsideOfCone(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 11),
		axisA(0.0f, 1.0f, 0.0f),
		axisALocal(0.0f, 1.0f, 0.0f),
		axisB(0.0f, 1.0f, 0.0f),
		sine(1.0f),
		cosine(0.0f)
	{
		flag = false;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1066AC40
	void ConstraintInsideOfCone::Rotate(const math::Matrix* matrix)
	{
		matrix->Rotate(axisALocal, axisA);
	}

	// FUNCTION: ENGINE 0x1066AC60
	unsigned short ConstraintInsideOfCone::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1066AC70
	bool ConstraintInsideOfCone::GetFlag() const
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x1066AC80
	void ConstraintInsideOfCone::ClearFlag()
	{
		flag = false;
	}

	// FUNCTION: ENGINE 0x1066AC90
	void ConstraintInsideOfCone::SetConeAngle(float angle)
	{
		math::SinCos(angle, &sine, &cosine);
	}

	// FUNCTION: ENGINE 0x1066AAD0
	__declspec(naked) float ConstraintInsideOfCone::GetConeAngle() const
	{
		__asm
		{
			fld dword ptr [ecx]ConstraintInsideOfCone.sine
			fld dword ptr [ecx]ConstraintInsideOfCone.cosine
			fpatan
			ret
		}
	}

	// FUNCTION: ENGINE 0x1066AAE0
	const math::Vector* ConstraintInsideOfCone::GetAxisA() const
	{
		return &axisA;
	}

	// FUNCTION: ENGINE 0x1066AAF0
	const math::Vector* ConstraintInsideOfCone::GetAxisB() const
	{
		return &axisB;
	}

	// FUNCTION: ENGINE 0x1066ACC0
	void ConstraintInsideOfCone::SetAxisA(const math::Vector* axis)
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

	// FUNCTION: ENGINE 0x1066AD00
	void ConstraintInsideOfCone::SetAxisB(const math::Vector* axis)
	{
		math::Vector* target = &axisB;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x1066AF80
	content::MemberList* ConstraintInsideOfCone::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintInsideOfCone> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType(&ConstraintInsideOfCone::GetConeAngle, &ConstraintInsideOfCone::SetConeAngle,
				"p"), 0, "coneAngle" },
			{ content::GetMemberVectorMetaType<ConstraintInsideOfCone, 0>(&ConstraintInsideOfCone::GetAxisA, &ConstraintInsideOfCone::SetAxisA,
				"p"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintInsideOfCone, 1>(&ConstraintInsideOfCone::GetAxisB, &ConstraintInsideOfCone::SetAxisB,
				"p"), 0, "axisB" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// Kept copies: the destructor, the casters and meta type getters of the reflection above, and the scalar deleting
	// destructor
	// FUNCTION: ENGINE 0x106615E0
	// FUNCTION: ENGINE 0x10661750
	// FUNCTION: ENGINE 0x10661780
	// FUNCTION: ENGINE 0x106617C0
	// FUNCTION: ENGINE 0x106617F0
	// FUNCTION: ENGINE 0x10661810

	// FUNCTION: ENGINE 0x1066ABB0
	// FUNCTION: ENGINE 0x1066AD40
	// FUNCTION: ENGINE 0x1066AD70
	// FUNCTION: ENGINE 0x1066AD90
	// FUNCTION: ENGINE 0x1066ADB0
	// FUNCTION: ENGINE 0x1066ADC0
	// FUNCTION: ENGINE 0x1066ADE0
	// FUNCTION: ENGINE 0x1066AE00
	// FUNCTION: ENGINE 0x1066AE10
	// FUNCTION: ENGINE 0x1066AE30
	// FUNCTION: ENGINE 0x1066AEA0
	// FUNCTION: ENGINE 0x1066AF10
}

// The getter / setter helpers of the cone's reflection, kept as out-of-line instances
template class PrimitiveMemberGetSetter<ravenphysics::ConstraintInsideOfCone, float>;
template class VectorMemberGetSetter<ravenphysics::ConstraintInsideOfCone>;

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x106617B0
// FUNCTION: ENGINE 0x1066AD30
