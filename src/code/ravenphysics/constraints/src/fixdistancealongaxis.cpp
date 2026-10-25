// The constraint that keeps a distance along an axis and the reflection of it (assert path
// ..\..\..\code\ravenphysics\constraints\src\fixdistancealongaxis.cpp).
#include <math.h>
#include "code/content/vectormetatype.h"
#include "code/core/debug.h"
#include "code/math/mathconstants.h"
#include "code/ravenphysics/constraints/constraints.h"

#define FIXDISTANCEALONGAXIS_FILE "..\\..\\..\\code\\ravenphysics\\constraints\\src\\fixdistancealongaxis.cpp"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintFixDistanceAlongAxis>;

	// FUNCTION: ENGINE 0x106783A0
	content::ClassInfo* ConstraintFixDistanceAlongAxis::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstraintFixDistanceAlongAxis";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x106783E0
	// EQUIVALENT: the same stores; the engine loads the two constants one after the other around the first store, 81.2 %
	ConstraintFixDistanceAlongAxis::ConstraintFixDistanceAlongAxis() :
		Constraint(9)
	{
		distanceCorrectionScale = 1.0f;
		distance = 0.0f;
		maxDistanceCorrectionForce = 1e12f;
		unknown54 = 0.0f;
		unknown5C = 0.0f;
		unknown58 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10678440
	// EQUIVALENT: the same stores; the engine loads the two constants one after the other around the first store, 84.3 %
	ConstraintFixDistanceAlongAxis::ConstraintFixDistanceAlongAxis(const CollisionHandle* first,
		const CollisionHandle* second) :
		Constraint(first, second, 9)
	{
		distanceCorrectionScale = 1.0f;
		distance = 0.0f;
		maxDistanceCorrectionForce = 1e12f;
		unknown54 = 0.0f;
		unknown5C = 0.0f;
		unknown58 = 0.0f;
	}

	// FUNCTION: ENGINE 0x106784A0
	void ConstraintFixDistanceAlongAxis::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x106784C0
	void ConstraintFixDistanceAlongAxis::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x106784E0
	void ConstraintFixDistanceAlongAxis::SetAxis(const math::Vector* newAxis)
	{
		math::Vector* target = &axis;
		target->x = newAxis->x;
		target->y = newAxis->y;
		target->z = newAxis->z;
		float length = target->Normalize();
		OLD_ASSERT_AT(FIXDISTANCEALONGAXIS_FILE, 0x56, length > math::EPSILON_SMALL, "l > math::EPSILON_FLOAT",
			"Axis must be of non-zero length.");
	}

	// FUNCTION: ENGINE 0x10678550
	void ConstraintFixDistanceAlongAxis::SetDistance(float value)
	{
		distance = value;
	}

	// FUNCTION: ENGINE 0x10678560
	void ConstraintFixDistanceAlongAxis::SetDistanceCorrectionScale(float value)
	{
		distanceCorrectionScale = value;
	}

	// FUNCTION: ENGINE 0x10678570
	void ConstraintFixDistanceAlongAxis::SetMaxDistanceCorrectionForce(float value)
	{
		maxDistanceCorrectionForce = value;
	}

	// FUNCTION: ENGINE 0x10678580
	unsigned short ConstraintFixDistanceAlongAxis::GetKind(int unused)
	{
		return 1;
	}

	// A scaled component by component by b, the stored value first
	static inline void ScaleVector(math::Vector& a, const math::Vector* b)
	{
		float y = b->y;
		float x = b->x;
		float z = b->z;
		a.x = a.x * x;
		a.y = a.y * y;
		a.z = a.z * z;
	}

	// FUNCTION: ENGINE 0x10678680
	// EQUIVALENT: the same products ((distance * scale) * axis) and sums; the engine stores the axis ahead of the squares and reads it back, ours keeps the products in registers, 7.5 %
	void ConstraintFixDistanceAlongAxis::ScaleBy(const math::Vector* scale)
	{
		ScaleVector(pointA, scale);
		ScaleVector(pointB, scale);
		float oldDistance = distance;
		math::Vector* target = &axis;
		float scaledY = oldDistance * scale->y;
		float scaledZ = oldDistance * scale->z;
		float scaledX = oldDistance * scale->x;
		target->x = scaledX * target->x;
		target->y = scaledY * target->y;
		target->z = scaledZ * target->z;
		distance = (float)sqrt((double)(target->x * target->x + target->y * target->y + target->z * target->z));
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x10678810
	content::MemberList* ConstraintFixDistanceAlongAxis::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintFixDistanceAlongAxis> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintFixDistanceAlongAxis, 0>("p"),
				(int)&((ConstraintFixDistanceAlongAxis*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintFixDistanceAlongAxis, 1>("p"),
				(int)&((ConstraintFixDistanceAlongAxis*)0)->pointB, "pointB" },
			{ content::GetMemberVectorMetaType<ConstraintFixDistanceAlongAxis, 2>("p"),
				(int)&((ConstraintFixDistanceAlongAxis*)0)->axis, "axisB" },
			{ content::GetMemberPrimitiveMetaType<ConstraintFixDistanceAlongAxis, float, 0>("p"),
				content::MemberOffset(&((ConstraintFixDistanceAlongAxis*)0)->distance,
				(int)&((ConstraintFixDistanceAlongAxis*)0)->distance), "distance" },
			{ content::GetMemberPrimitiveMetaType<ConstraintFixDistanceAlongAxis, float, 1>("p"),
				content::MemberOffset(&((ConstraintFixDistanceAlongAxis*)0)->distanceCorrectionScale,
				(int)&((ConstraintFixDistanceAlongAxis*)0)->distanceCorrectionScale), "distanceCorrectionScale" },
			{ content::GetMemberPrimitiveMetaType<ConstraintFixDistanceAlongAxis, float, 2>("p"),
				content::MemberOffset(&((ConstraintFixDistanceAlongAxis*)0)->maxDistanceCorrectionForce,
				(int)&((ConstraintFixDistanceAlongAxis*)0)->maxDistanceCorrectionForce),
				"maxDistanceCorrectionForce" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// Kept copies: the destructor, the casters, the meta type getters and the deleting destructor
	// FUNCTION: ENGINE 0x10678430
	// FUNCTION: ENGINE 0x10678590
	// FUNCTION: ENGINE 0x106785C0
	// FUNCTION: ENGINE 0x106785F0
	// FUNCTION: ENGINE 0x10678620
	// FUNCTION: ENGINE 0x10678630
	// FUNCTION: ENGINE 0x10678660
	// FUNCTION: ENGINE 0x10678750
	// FUNCTION: ENGINE 0x10678790
	// FUNCTION: ENGINE 0x106787D0
}
