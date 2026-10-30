// The deformable constraint that keeps a distance along an axis, its shared properties and the reflection of them (assert
// path ..\..\..\code\ravenphysics\constraints\src\deformablefixdistancealongaxis.cpp).
#include <math.h>
#include "code/content/vectormetatype.h"
#include "code/core/debug.h"
#include "code/core/refptr.h"
#include "code/math/mathconstants.h"
#include "code/ravenphysics/constraints/constraints.h"

#define DEFORMABLEFIXDISTANCEALONGAXIS_FILE "..\\..\\..\\code\\ravenphysics\\constraints\\src\\deformablefixdistancealongaxis.cpp"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintDeformableFixDistanceAlongAxis>;

	// FUNCTION: ENGINE 0x10692140
	content::ClassInfo* ConstraintDeformableFixDistanceAlongAxis::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintDeformableFixDistanceAlongAxis";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10692180
	content::ClassInfo* DeformableSliderConstraintSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::DeformableSliderConstraintSharedProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x106921C0
	ConstraintDeformableFixDistanceAlongAxis::ConstraintDeformableFixDistanceAlongAxis() :
		Constraint(6),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		axis(0.0f, 1.0f, 0.0f),
		distance(0.0f),
		distanceCorrectionScale(1.0f),
		maxDistanceCorrectionForce(1e12f),
		maximumStaticForce(1e12f),
		maximumDynamicForce(1e12f),
		flag(false),
		sharedProperties(0)
	{
		unknown60 = 0.0f;
		unknown68 = 0.0f;
		unknown64 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10692250
	ConstraintDeformableFixDistanceAlongAxis::ConstraintDeformableFixDistanceAlongAxis(const CollisionHandle* first,
		const CollisionHandle* second) :
		Constraint(first, second, 6),
		pointA(0.0f, 0.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		axis(0.0f, 1.0f, 0.0f),
		distance(0.0f),
		distanceCorrectionScale(1.0f),
		maxDistanceCorrectionForce(1e12f),
		maximumStaticForce(1e12f),
		maximumDynamicForce(1e12f),
		flag(false),
		sharedProperties(0)
	{
		unknown60 = 0.0f;
		unknown68 = 0.0f;
		unknown64 = 0.0f;
	}

	// FUNCTION: ENGINE 0x106922F0
	ConstraintDeformableFixDistanceAlongAxis::ConstraintDeformableFixDistanceAlongAxis(
		const ConstraintDeformableFixDistanceAlongAxis& other) :
		Constraint(other)
	{
		pointA.x = other.pointA.x;
		pointA.y = other.pointA.y;
		pointA.z = other.pointA.z;
		pointB.x = other.pointB.x;
		pointB.y = other.pointB.y;
		pointB.z = other.pointB.z;
		axis.x = other.axis.x;
		axis.y = other.axis.y;
		axis.z = other.axis.z;
		distance = other.distance;
		distanceCorrectionScale = other.distanceCorrectionScale;
		maxDistanceCorrectionForce = other.maxDistanceCorrectionForce;
		maximumStaticForce = other.maximumStaticForce;
		maximumDynamicForce = other.maximumDynamicForce;
		flag = other.flag;
		sharedProperties = other.sharedProperties;
		unknown60 = other.unknown60;
		unknown68 = other.unknown68;
		unknown64 = other.unknown64;
		if (sharedProperties)
		{
			sharedProperties->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x10692390
	DeformableSliderConstraintSharedProperties* ConstraintDeformableFixDistanceAlongAxis::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x106923A0
	void ConstraintDeformableFixDistanceAlongAxis::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x106923C0
	void ConstraintDeformableFixDistanceAlongAxis::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x106923E0
	void ConstraintDeformableFixDistanceAlongAxis::SetAxis(const math::Vector* newAxis)
	{
		math::Vector* target = &axis;
		target->x = newAxis->x;
		target->y = newAxis->y;
		target->z = newAxis->z;
		float length = target->Normalize();
		OLD_ASSERT_AT(DEFORMABLEFIXDISTANCEALONGAXIS_FILE, 0xD1, length > math::EPSILON_SMALL, "l > math::EPSILON_FLOAT",
			"Axis must be of non-zero length.");
	}

	// FUNCTION: ENGINE 0x10692450
	void ConstraintDeformableFixDistanceAlongAxis::SetDistance(float value)
	{
		distance = value;
	}

	// FUNCTION: ENGINE 0x10692460
	void ConstraintDeformableFixDistanceAlongAxis::SetDistanceCorrectionScale(float value)
	{
		distanceCorrectionScale = value;
	}

	// FUNCTION: ENGINE 0x10692470
	void ConstraintDeformableFixDistanceAlongAxis::SetMaxDistanceCorrectionForce(float value)
	{
		maxDistanceCorrectionForce = value;
	}

	// FUNCTION: ENGINE 0x10692480
	unsigned short ConstraintDeformableFixDistanceAlongAxis::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10692490
	void ConstraintDeformableFixDistanceAlongAxis::SetMaximumStaticForce(float value)
	{
		maximumStaticForce = value;
	}

	// FUNCTION: ENGINE 0x106924A0
	void ConstraintDeformableFixDistanceAlongAxis::SetMaximumDynamicForce(float value)
	{
		maximumDynamicForce = value;
	}

	// FUNCTION: ENGINE 0x10692590
	// EQUIVALENT: the same stores; the engine stores the reference count ahead of the first member, 72.4 %
	DeformableSliderConstraintSharedProperties::DeformableSliderConstraintSharedProperties() :
		distanceCorrectionScale(1.0f)
	{
		maxDistanceCorrectionForce = 1e12f;
		maximumStaticForce = 1e12f;
		maximumDynamicForce = 1e12f;
	}

	// FUNCTION: ENGINE 0x10692640
	ConstraintDeformableFixDistanceAlongAxis::~ConstraintDeformableFixDistanceAlongAxis()
	{
		core::SafeRelease(sharedProperties);
	}

	// FUNCTION: ENGINE 0x10692660
	void ConstraintDeformableFixDistanceAlongAxis::SetSharedProperties(
		DeformableSliderConstraintSharedProperties* properties)
	{
		core::RefAssign(sharedProperties, properties);
		if (sharedProperties)
		{
			distanceCorrectionScale = sharedProperties->distanceCorrectionScale;
			maxDistanceCorrectionForce = sharedProperties->maxDistanceCorrectionForce;
			maximumStaticForce = sharedProperties->maximumStaticForce;
			maximumDynamicForce = sharedProperties->maximumDynamicForce;
		}
	}

	// FUNCTION: ENGINE 0x106926A0
	// EQUIVALENT: the same products ((distance * scale) * axis) and sums; the engine stores the axis ahead of the squares and reads it back, ours schedules the products ahead of the stores, 16.1 %
	void ConstraintDeformableFixDistanceAlongAxis::ScaleBy(const math::Vector* scale)
	{
		Multiply(pointA, *scale);
		Multiply(pointB, *scale);
		float oldDistance = distance;
		math::Vector* target = &axis;
		target->x = oldDistance * scale->x * target->x;
		target->y = oldDistance * scale->y * target->y;
		target->z = oldDistance * scale->z * target->z;
		distance = (float)sqrt((double)(target->x * target->x + target->y * target->y + target->z * target->z));
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x10692930
	content::MemberList* DeformableSliderConstraintSharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DeformableSliderConstraintSharedProperties, float, 0>("p"),
				content::MemberOffset(&((DeformableSliderConstraintSharedProperties*)0)->distanceCorrectionScale,
				(int)&((DeformableSliderConstraintSharedProperties*)0)->distanceCorrectionScale),
				"distanceCorrectionScale" },
			{ content::GetMemberPrimitiveMetaType<DeformableSliderConstraintSharedProperties, float, 1>("p"),
				content::MemberOffset(&((DeformableSliderConstraintSharedProperties*)0)->maxDistanceCorrectionForce,
				(int)&((DeformableSliderConstraintSharedProperties*)0)->maxDistanceCorrectionForce),
				"maxDistanceCorrectionForce" },
			{ content::GetMemberPrimitiveMetaType<DeformableSliderConstraintSharedProperties, float, 2>("p"),
				content::MemberOffset(&((DeformableSliderConstraintSharedProperties*)0)->maximumStaticForce,
				(int)&((DeformableSliderConstraintSharedProperties*)0)->maximumStaticForce), "maximumStaticForce" },
			{ content::GetMemberPrimitiveMetaType<DeformableSliderConstraintSharedProperties, float, 3>("p"),
				content::MemberOffset(&((DeformableSliderConstraintSharedProperties*)0)->maximumDynamicForce,
				(int)&((DeformableSliderConstraintSharedProperties*)0)->maximumDynamicForce), "maximumDynamicForce" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10692AC0
	content::MemberList* ConstraintDeformableFixDistanceAlongAxis::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintDeformableFixDistanceAlongAxis> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintDeformableFixDistanceAlongAxis, 0>("pn"),
				(int)&((ConstraintDeformableFixDistanceAlongAxis*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintDeformableFixDistanceAlongAxis, 1>("pn"),
				(int)&((ConstraintDeformableFixDistanceAlongAxis*)0)->pointB, "pointB" },
			{ content::GetMemberVectorMetaType<ConstraintDeformableFixDistanceAlongAxis, 2>("pn"),
				(int)&((ConstraintDeformableFixDistanceAlongAxis*)0)->axis, "axisA" },
			{ content::GetMemberPrimitiveMetaType<ConstraintDeformableFixDistanceAlongAxis, float, 0>("pn"),
				content::MemberOffset(&((ConstraintDeformableFixDistanceAlongAxis*)0)->distance,
				(int)&((ConstraintDeformableFixDistanceAlongAxis*)0)->distance), "distance" },
			{ content::GetReferenceMemberMetaType(&ConstraintDeformableFixDistanceAlongAxis::GetSharedProperties,
				&ConstraintDeformableFixDistanceAlongAxis::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// Kept copies: the vector and float meta type getters, the casters, the deleting destructors and the reference helpers
	// of the reflection above
	// FUNCTION: ENGINE 0x106924B0
	// FUNCTION: ENGINE 0x106924E0
	// FUNCTION: ENGINE 0x10692510
	// FUNCTION: ENGINE 0x10692540
	// FUNCTION: ENGINE 0x10692560
	// FUNCTION: ENGINE 0x106925D0
	// FUNCTION: ENGINE 0x106925E0
	// FUNCTION: ENGINE 0x106925F0
	// FUNCTION: ENGINE 0x10692620
	// FUNCTION: ENGINE 0x10692770
	// FUNCTION: ENGINE 0x106927B0
	// FUNCTION: ENGINE 0x106927F0
	// FUNCTION: ENGINE 0x10692830
	// FUNCTION: ENGINE 0x10692870
	// FUNCTION: ENGINE 0x106928B0
	// FUNCTION: ENGINE 0x106928C0
	// FUNCTION: ENGINE 0x106928E0
	// FUNCTION: ENGINE 0x10692900
	// FUNCTION: ENGINE 0x10692910
	// FUNCTION: ENGINE 0x10692A30
	// FUNCTION: ENGINE 0x10692A50
}
