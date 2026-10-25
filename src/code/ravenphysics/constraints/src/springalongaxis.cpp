// The spring along an axis, its shared properties and the reflection of them (no assert path of its own; the file name
// is a guess).
#include <math.h>
#include "code/content/vectormetatype.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	// The larger of two numbers (0x1006FB70, another unit; name guess)
	float Unknown1006FB70(float first, float second);

	typedef ConstraintSpringAlongAxisSharedProperties SpringProperties;

	template struct content::BaseClassCasterImpl<Constraint, ConstraintSpringAlongAxis>;
}

namespace content
{
	// The offset of the enumeration member is worked out where it is used
	template<> inline int MemberOffset<ravenphysics::ConstraintSpringAlongAxisSharedProperties::ScaleByMassType>(
		ravenphysics::ConstraintSpringAlongAxisSharedProperties::ScaleByMassType* member, int offset)
	{
		return offset;
	}

	static const EnumValue sScaleByMassTypeValues[] =
	{
		{ "None", 0 },
		{ "ObjectA", 1 },
		{ "ObjectB", 2 },
		{ "Greater", 3 },
		{ "Total", 4 }
	};

	// FUNCTION: ENGINE 0x1066FCA0
	template<> void EnumInfo<ravenphysics::ConstraintSpringAlongAxisSharedProperties::ScaleByMassType>::Get(
		const char** name, const EnumValue** values, int* count, const char** code)
	{
		*name = "ravenphysics::ConstraintSpringAlongAxisSharedProperties::ScaleByMassType";
		*code = "pn";
		*values = sScaleByMassTypeValues;
		*count = 5;
	}
}

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1066FC50
	const math::Vector* ConstraintSpringAlongAxis::GetAxisA() const
	{
		return &axisA;
	}

	// FUNCTION: ENGINE 0x1066FC60
	content::ClassInfo* ConstraintSpringAlongAxis::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintSpringAlongAxis";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066FCD0
	content::ClassInfo* ConstraintSpringAlongAxisSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintSpringAlongAxisSharedProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066FD10
	ConstraintSpringAlongAxis::ConstraintSpringAlongAxis() :
		Constraint(0x13),
		sharedProperties(0),
		pointA(0.0f, 0.0f, 0.0f),
		axisA(0.0f, 1.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		stableDistance(1.0f),
		springConstant(1.0f),
		dampingConstant(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x1066FD80
	ConstraintSpringAlongAxis::ConstraintSpringAlongAxis(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 0x13),
		sharedProperties(0),
		pointA(0.0f, 0.0f, 0.0f),
		axisA(0.0f, 1.0f, 0.0f),
		pointB(0.0f, 0.0f, 0.0f),
		stableDistance(1.0f),
		springConstant(1.0f),
		dampingConstant(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x1066FDF0
	// EQUIVALENT: the same copies and reference; the engine tests the copied properties pointer after the numbers, 27.4 %
	ConstraintSpringAlongAxis::ConstraintSpringAlongAxis(const ConstraintSpringAlongAxis& other) :
		Constraint(other)
	{
		sharedProperties = other.sharedProperties;
		pointA.x = other.pointA.x;
		pointA.y = other.pointA.y;
		pointA.z = other.pointA.z;
		axisA.x = other.axisA.x;
		axisA.y = other.axisA.y;
		axisA.z = other.axisA.z;
		pointB.x = other.pointB.x;
		pointB.y = other.pointB.y;
		pointB.z = other.pointB.z;
		stableDistance = other.stableDistance;
		springConstant = other.springConstant;
		dampingConstant = other.dampingConstant;
		if (sharedProperties)
		{
			sharedProperties->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x1066FE70
	ConstraintSpringAlongAxisSharedProperties* ConstraintSpringAlongAxis::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x1066FE80
	unsigned short ConstraintSpringAlongAxis::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1066FE90
	void ConstraintSpringAlongAxis::SetPointA(const math::Vector* point)
	{
		pointA.x = point->x;
		pointA.y = point->y;
		pointA.z = point->z;
	}

	// FUNCTION: ENGINE 0x1066FEB0
	void ConstraintSpringAlongAxis::SetAxisA(const math::Vector* axis)
	{
		math::Vector* target = &axisA;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x1066FEE0
	void ConstraintSpringAlongAxis::SetPointB(const math::Vector* point)
	{
		pointB.x = point->x;
		pointB.y = point->y;
		pointB.z = point->z;
	}

	// FUNCTION: ENGINE 0x1066FF00
	void ConstraintSpringAlongAxis::SetStableDistance(float value)
	{
		stableDistance = value;
	}

	// FUNCTION: ENGINE 0x1066FF10
	void ConstraintSpringAlongAxis::SetSpringConstant(float value)
	{
		springConstant = value;
	}

	// FUNCTION: ENGINE 0x1066FF20
	void ConstraintSpringAlongAxis::SetDampingConstant(float value)
	{
		dampingConstant = value;
	}

	// FUNCTION: ENGINE 0x10670050
	ConstraintSpringAlongAxisSharedProperties::ConstraintSpringAlongAxisSharedProperties() :
		springConstant(1.0f),
		dampingConstant(1.0f),
		scaleByMassType(SCALE_NONE)
	{
	}

	// FUNCTION: ENGINE 0x106700F0
	ConstraintSpringAlongAxis::~ConstraintSpringAlongAxis()
	{
		core::SafeRelease(sharedProperties);
	}

	// FUNCTION: ENGINE 0x10670110
	// EQUIVALENT: the same cases and loads; the engine's jump table starts at the value 0, ours at 1, and the engine loads the constant first, 14.6 %
	void ConstraintSpringAlongAxis::UpdateConstants()
	{
		CollisionShape* first = firstObject ? firstObject->shape : 0;
		CollisionShape* second = secondObject ? secondObject->shape : 0;
		SpringProperties* properties = sharedProperties;
		float scale = 1.0f;
		switch (properties->scaleByMassType)
		{
		case SpringProperties::SCALE_NONE:
			break;
		case SpringProperties::SCALE_OBJECT_A:
			if (first)
			{
				scale = first->unknown88;
			}
			break;
		case SpringProperties::SCALE_OBJECT_B:
			if (second)
			{
				scale = second->unknown88;
			}
			break;
		case SpringProperties::SCALE_GREATER:
			if (first)
			{
				if (second)
				{
					scale = Unknown1006FB70(first->unknown88, second->unknown88);
				}
				else
				{
					scale = first->unknown88;
				}
			}
			else if (second)
			{
				scale = second->unknown88;
			}
			break;
		case SpringProperties::SCALE_TOTAL:
			if (first)
			{
				if (second)
				{
					scale = second->unknown88 + first->unknown88;
				}
				else
				{
					scale = first->unknown88;
				}
			}
			else if (second)
			{
				scale = second->unknown88;
			}
			break;
		}
		springConstant = properties->springConstant * scale;
		dampingConstant = properties->dampingConstant * scale;
	}

	// FUNCTION: ENGINE 0x106701F0
	// EQUIVALENT: the same products and the same sums; the engine loads and multiplies the components of pointA one at a time, 54.1 %
	void ConstraintSpringAlongAxis::ScaleBy(const math::Vector* scale)
	{
		math::Vector before;
		before.Sub(pointB, pointA);
		float z = scale->z;
		float y = scale->y;
		pointA.x = pointA.x * scale->x;
		pointA.y = pointA.y * y;
		pointA.z = pointA.z * z;
		y = scale->y;
		z = scale->z;
		pointB.x = pointB.x * scale->x;
		pointB.y = y * pointB.y;
		pointB.z = z * pointB.z;
		math::Vector after;
		after.Sub(pointB, pointA);
		stableDistance = (float)sqrt((double)(after.x * after.x + after.y * after.y + after.z * after.z))
			* (stableDistance / (float)sqrt((double)(before.x * before.x + before.y * before.y + before.z * before.z)));
	}

	// FUNCTION: ENGINE 0x10670470
	content::MemberList* ConstraintSpringAlongAxisSharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SpringProperties, float, 0>("pn"),
				content::MemberOffset(&((SpringProperties*)0)->springConstant,
				(int)&((SpringProperties*)0)->springConstant), "springConstant" },
			{ content::GetMemberPrimitiveMetaType<SpringProperties, float, 1>("pn"),
				content::MemberOffset(&((SpringProperties*)0)->dampingConstant,
				(int)&((SpringProperties*)0)->dampingConstant), "dampingConstant" },
			{ content::GetEnumMetaType<SpringProperties::ScaleByMassType>(),
				content::MemberOffset(&((SpringProperties*)0)->scaleByMassType,
				(int)&((SpringProperties*)0)->scaleByMassType), "scaleByMassType" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10670550
	void ConstraintSpringAlongAxis::SetSharedProperties(ConstraintSpringAlongAxisSharedProperties* properties)
	{
		core::RefAssign(sharedProperties, properties);
		if (sharedProperties)
		{
			UpdateConstants();
		}
	}

	// FUNCTION: ENGINE 0x10670660
	content::MemberList* ConstraintSpringAlongAxis::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintSpringAlongAxis> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintSpringAlongAxis, 0>("pn"),
				(int)&((ConstraintSpringAlongAxis*)0)->pointA, "pointA" },
			{ content::GetMemberVectorMetaType<ConstraintSpringAlongAxis, 1>(&ConstraintSpringAlongAxis::GetAxisA,
				&ConstraintSpringAlongAxis::SetAxisA, "pn"), 0, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintSpringAlongAxis, 2>("pn"),
				(int)&((ConstraintSpringAlongAxis*)0)->pointB, "pointB" },
			{ content::GetMemberPrimitiveMetaType<ConstraintSpringAlongAxis, float, 0>("pn"),
				content::MemberOffset(&((ConstraintSpringAlongAxis*)0)->stableDistance,
				(int)&((ConstraintSpringAlongAxis*)0)->stableDistance), "stableDistance" },
			{ content::GetReferenceMemberMetaType(&ConstraintSpringAlongAxis::GetSharedProperties,
				&ConstraintSpringAlongAxis::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x1066FF30
	// FUNCTION: ENGINE 0x1066FF90
	// FUNCTION: ENGINE 0x1066FFC0
	// FUNCTION: ENGINE 0x1066FFF0
	// FUNCTION: ENGINE 0x10670000
	// FUNCTION: ENGINE 0x10670020
	// FUNCTION: ENGINE 0x10670080
	// FUNCTION: ENGINE 0x10670090
	// FUNCTION: ENGINE 0x106700A0
	// FUNCTION: ENGINE 0x106700D0
	// FUNCTION: ENGINE 0x106702E0
	// FUNCTION: ENGINE 0x10670320
	// FUNCTION: ENGINE 0x10670360
	// FUNCTION: ENGINE 0x106703A0
	// FUNCTION: ENGINE 0x106703B0
	// FUNCTION: ENGINE 0x106703D0
	// FUNCTION: ENGINE 0x106703F0
	// FUNCTION: ENGINE 0x10670400
	// FUNCTION: ENGINE 0x10670420
	// FUNCTION: ENGINE 0x10670440
	// FUNCTION: ENGINE 0x10670450
	// FUNCTION: ENGINE 0x10670530
	// FUNCTION: ENGINE 0x10670580
	// FUNCTION: ENGINE 0x106705F0
}

template class VectorMemberGetSetter<ravenphysics::ConstraintSpringAlongAxis>;
