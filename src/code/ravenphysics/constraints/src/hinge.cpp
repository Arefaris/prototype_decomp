// The ball-in-socket, align-two-axes and hinge constraints and the reflection of them (the assert path of the unit is
// code/ravenphysics/constraints/src/constraints.cpp).
#include "code/content/vectormetatype.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintBallInSocket>;

	// FUNCTION: ENGINE 0x1065B9B0
	content::ClassInfo* ConstraintBallInSocket::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintBallInSocket";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1065B9F0
	ConstraintBallInSocket::ConstraintBallInSocket() :
		Constraint(1),
		pointA(0.0f, 0.0f, 0.0f),
		pointALocal(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		flag = false;
		unknown48 = 0.0f;
		unknown4C = 0.0f;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
	}

	// FUNCTION: ENGINE 0x1065BA70
	ConstraintBallInSocket::ConstraintBallInSocket(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 1),
		pointA(0.0f, 0.0f, 0.0f),
		pointALocal(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f)
	{
		flag = false;
		unknown48 = 0.0f;
		unknown4C = 0.0f;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
	}

	// FUNCTION: ENGINE 0x1065BAF0
	void ConstraintBallInSocket::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
		pointALocal.x = point->x;
		pointALocal.y = point->y;
		pointALocal.z = point->z;
	}

	// FUNCTION: ENGINE 0x1065BB20
	void ConstraintBallInSocket::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x1065BB40
	void ConstraintBallInSocket::Rotate(const math::Matrix* matrix)
	{
		matrix->Transform(pointALocal, pointA);
	}

	// FUNCTION: ENGINE 0x1065BB60
	unsigned short ConstraintBallInSocket::GetKind(int unused)
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x1065BB70
	bool ConstraintBallInSocket::GetFlag() const
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x1065BB80
	void ConstraintBallInSocket::ClearFlag()
	{
		flag = false;
	}

	// FUNCTION: ENGINE 0x1065BB90
	// EQUIVALENT: the same nine products; the engine loads each stored component and multiplies it by the held scale component, ours multiplies the held one by the stored, 15.8 %
	void ConstraintBallInSocket::ScaleBy(const math::Vector* scale)
	{
		Multiply(pointA, *scale);
		Multiply(pointALocal, *scale);
		Multiply(pointB, *scale);
	}

	// FUNCTION: ENGINE 0x1065B9A0
	const math::Vector* ConstraintBallInSocket::GetPointA() const
	{
		return &pointA;
	}

	// FUNCTION: ENGINE 0x1065BDE0
	content::MemberList* ConstraintBallInSocket::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintBallInSocket> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintBallInSocket, 0>(&ConstraintBallInSocket::GetPointA,
				&ConstraintBallInSocket::SetPointA, "p"), 0, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintBallInSocket, 1>("p"),
				(int)&((ConstraintBallInSocket*)0)->pointB, "pointB" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies: the destructor, the caster, the scalar deleting destructor and the meta type getters of the reflection
	// above
	// FUNCTION: ENGINE 0x1065BA60
	// FUNCTION: ENGINE 0x1065BC90
	// FUNCTION: ENGINE 0x1065BCD0
	// FUNCTION: ENGINE 0x1065BD00
	// FUNCTION: ENGINE 0x1065BD20
	// FUNCTION: ENGINE 0x1065BD40
	// FUNCTION: ENGINE 0x1065BD50
	// FUNCTION: ENGINE 0x1065BD70

	template struct content::BaseClassCasterImpl<Constraint, ConstraintAlign2Axes>;

	// FUNCTION: ENGINE 0x1065BEE0
	content::ClassInfo* ConstraintAlign2Axes::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintAlign2Axes";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1065BEC0
	const math::Vector* ConstraintAlign2Axes::GetAxisA() const
	{
		return &axisA;
	}

	// FUNCTION: ENGINE 0x1065BED0
	const math::Vector* ConstraintAlign2Axes::GetAxisB() const
	{
		return &axisB;
	}

	// FUNCTION: ENGINE 0x1065BF20
	void ConstraintAlign2Axes::SetAxisA(const math::Vector* axis)
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

	// FUNCTION: ENGINE 0x1065BF60
	void ConstraintAlign2Axes::SetAxisB(const math::Vector* axis)
	{
		math::Vector* target = &axisB;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
		perpendicular.Perpendicular(*target);
		perpendicular.NormalizeFast();
		cross.CrossProduct(*target, perpendicular);
		cross.NormalizeFast();
	}

	// FUNCTION: ENGINE 0x1065BFB0
	void ConstraintAlign2Axes::Rotate(const math::Matrix* matrix)
	{
		matrix->Rotate(axisALocal, axisA);
	}

	// FUNCTION: ENGINE 0x1065BFD0
	unsigned short ConstraintAlign2Axes::GetKind(int unused)
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x1065BFE0
	ConstraintAlign2Axes::ConstraintAlign2Axes() :
		Constraint(2)
	{
		math::Vector up(0.0f, 1.0f, 0.0f);
		SetAxisA(&up);
		math::Vector up2(0.0f, 1.0f, 0.0f);
		SetAxisB(&up2);
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
		unknown70 = 0.0f;
		unknown74 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1065C0E0
	ConstraintAlign2Axes::ConstraintAlign2Axes(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 2)
	{
		math::Vector up(0.0f, 1.0f, 0.0f);
		SetAxisA(&up);
		math::Vector up2(0.0f, 1.0f, 0.0f);
		SetAxisB(&up2);
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
		unknown70 = 0.0f;
		unknown74 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1065C2B0
	content::MemberList* ConstraintAlign2Axes::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintAlign2Axes> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintAlign2Axes, 0>(&ConstraintAlign2Axes::GetAxisA,
				&ConstraintAlign2Axes::SetAxisA, "p"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintAlign2Axes, 1>(&ConstraintAlign2Axes::GetAxisB,
				&ConstraintAlign2Axes::SetAxisB, "p"), 0, "axisB" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x1065C070
	// FUNCTION: ENGINE 0x1065C090
	// FUNCTION: ENGINE 0x1065C0C0
	// FUNCTION: ENGINE 0x1065C180
	// FUNCTION: ENGINE 0x1065C1A0
	// FUNCTION: ENGINE 0x1065C1B0
	// FUNCTION: ENGINE 0x1065C1D0
	// FUNCTION: ENGINE 0x1065C240

	template struct content::BaseClassCasterImpl<Constraint, ConstraintHinge>;

	// FUNCTION: ENGINE 0x1066B0A0
	content::ClassInfo* ConstraintHinge::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintHinge";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066B0E0
	ConstraintHinge::ConstraintHinge(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 10),
		ball(first, second),
		align(first, second)
	{
	}

	// FUNCTION: ENGINE 0x1066B140
	void ConstraintHinge::Rotate(const math::Matrix* matrix)
	{
		ball.Rotate(matrix);
		align.Rotate(matrix);
	}

	// FUNCTION: ENGINE 0x1066B170
	unsigned short ConstraintHinge::GetKind(int unused)
	{
		return 5;
	}

	// FUNCTION: ENGINE 0x1066B180
	bool ConstraintHinge::GetFlag() const
	{
		return ball.GetFlag();
	}

	// FUNCTION: ENGINE 0x1066B190
	void ConstraintHinge::ClearFlag()
	{
		ball.ClearFlag();
	}

	// FUNCTION: ENGINE 0x1066B1A0
	void ConstraintHinge::SetFirstObject(const CollisionHandle* handle)
	{
		Constraint::SetObject(0, handle);
		ball.SetObject(0, handle);
		align.SetObject(0, handle);
	}

	// FUNCTION: ENGINE 0x1066B1E0
	void ConstraintHinge::SetSecondObject(const CollisionHandle* handle)
	{
		Constraint::SetObject(1, handle);
		ball.SetObject(1, handle);
		align.SetObject(1, handle);
	}

	// FUNCTION: ENGINE 0x1066B220
	void ConstraintHinge::SetAxisA(const math::Vector* axis)
	{
		align.SetAxisA(axis);
	}

	// FUNCTION: ENGINE 0x1066B230
	void ConstraintHinge::SetAxisB(const math::Vector* axis)
	{
		align.SetAxisB(axis);
	}

	// FUNCTION: ENGINE 0x1066B240
	void ConstraintHinge::SetPointA(const math::Vector* point)
	{
		ball.SetPointA(point);
	}

	// FUNCTION: ENGINE 0x1066B250
	void ConstraintHinge::SetPointB(const math::Vector* point)
	{
		ball.SetPointB(point);
	}

	// FUNCTION: ENGINE 0x1066B260
	const math::Vector* ConstraintHinge::GetAxisA() const
	{
		return &align.axisA;
	}

	// FUNCTION: ENGINE 0x1066B270
	const math::Vector* ConstraintHinge::GetAxisB() const
	{
		return &align.axisB;
	}

	// FUNCTION: ENGINE 0x1066B280
	const math::Vector* ConstraintHinge::GetPointA() const
	{
		return &ball.pointA;
	}

	// FUNCTION: ENGINE 0x1066B290
	const math::Vector* ConstraintHinge::GetPointB() const
	{
		return &ball.pointB;
	}

	// FUNCTION: ENGINE 0x1066B2A0
	void ConstraintHinge::ScaleBy(const math::Vector* scale)
	{
		ball.ScaleBy(scale);
	}

	// FUNCTION: ENGINE 0x1066B2B0
	ConstraintHinge::ConstraintHinge() :
		Constraint(10)
	{
	}

	// FUNCTION: ENGINE 0x1066B570
	content::MemberList* ConstraintHinge::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintHinge> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintHinge, 0>(&ConstraintHinge::GetPointA,
				&ConstraintHinge::SetPointA, "p"), 0, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintHinge, 1>(&ConstraintHinge::GetPointB,
				&ConstraintHinge::SetPointB, "p"), 0, "pointB" },
			{ content::GetMemberVectorMetaType<ConstraintHinge, 2>(&ConstraintHinge::GetAxisA,
				&ConstraintHinge::SetAxisA, "p"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintHinge, 3>(&ConstraintHinge::GetAxisB,
				&ConstraintHinge::SetAxisB, "p"), 0, "axisB" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x1066B120
	// FUNCTION: ENGINE 0x1066B2F0
	// FUNCTION: ENGINE 0x1066B320
	// FUNCTION: ENGINE 0x1066B360
	// FUNCTION: ENGINE 0x1066B380
	// FUNCTION: ENGINE 0x1066B390
	// FUNCTION: ENGINE 0x1066B3B0
	// FUNCTION: ENGINE 0x1066B420
	// FUNCTION: ENGINE 0x1066B490
	// FUNCTION: ENGINE 0x1066B500
}

template class VectorMemberGetSetter<ravenphysics::ConstraintBallInSocket>;
template class VectorMemberGetSetter<ravenphysics::ConstraintAlign2Axes>;
template class VectorMemberGetSetter<ravenphysics::ConstraintHinge>;

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x1066B2E0
