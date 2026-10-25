// The angular spring constraint, its shared properties and the reflection of them (the unit before angularvelocity.cpp;
// no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintAngularSpring>;

	// FUNCTION: ENGINE 0x1066B6A0
	content::ClassInfo* ConstraintAngularSpring::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintAngularSpring";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066B6E0
	content::ClassInfo* ConstraintAngularSpringSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintAngularSpringSharedProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066B720
	ConstraintAngularSpring::ConstraintAngularSpring() :
		Constraint(4),
		axisA(0.0f, 1.0f, 0.0f),
		axisB(0.0f, 1.0f, 0.0f),
		springConstant(0.0f),
		dampingConstant(0.0f),
		sharedProperties(0)
	{
	}

	// FUNCTION: ENGINE 0x1066B770
	ConstraintAngularSpring::ConstraintAngularSpring(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 4),
		axisA(0.0f, 1.0f, 0.0f),
		axisB(0.0f, 1.0f, 0.0f),
		springConstant(0.0f),
		dampingConstant(0.0f),
		sharedProperties(0)
	{
	}

	// FUNCTION: ENGINE 0x1066B7D0
	ConstraintAngularSpring::ConstraintAngularSpring(const ConstraintAngularSpring& other) :
		Constraint(other)
	{
		axisA.x = other.axisA.x;
		axisA.y = other.axisA.y;
		axisA.z = other.axisA.z;
		axisB.x = other.axisB.x;
		axisB.y = other.axisB.y;
		axisB.z = other.axisB.z;
		springConstant = other.springConstant;
		dampingConstant = other.dampingConstant;
		sharedProperties = other.sharedProperties;
		if (sharedProperties)
		{
			sharedProperties->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x1066B830
	ConstraintAngularSpringSharedProperties* ConstraintAngularSpring::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x1066B840
	void ConstraintAngularSpring::SetAxisA(const math::Vector* axis)
	{
		math::Vector* target = &axisA;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x1066B870
	void ConstraintAngularSpring::SetAxisB(const math::Vector* axis)
	{
		math::Vector* target = &axisB;
		target->x = axis->x;
		target->y = axis->y;
		target->z = axis->z;
		target->Normalize();
	}

	// FUNCTION: ENGINE 0x1066B8A0
	void ConstraintAngularSpring::SetSpringConstant(float value)
	{
		springConstant = value;
	}

	// FUNCTION: ENGINE 0x1066B8B0
	void ConstraintAngularSpring::SetDampingConstant(float value)
	{
		dampingConstant = value;
	}

	// FUNCTION: ENGINE 0x1066B8C0
	unsigned short ConstraintAngularSpring::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1066B980
	ConstraintAngularSpringSharedProperties::ConstraintAngularSpringSharedProperties() :
		springConstant(0.0f),
		dampingConstant(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x1066BA20
	ConstraintAngularSpring::~ConstraintAngularSpring()
	{
		core::SafeRelease(sharedProperties);
	}

	// FUNCTION: ENGINE 0x1066BA40
	void ConstraintAngularSpring::SetSharedProperties(ConstraintAngularSpringSharedProperties* properties)
	{
		core::RefAssign(sharedProperties, properties);
		if (sharedProperties)
		{
			springConstant = sharedProperties->springConstant;
			dampingConstant = sharedProperties->dampingConstant;
		}
	}

	// FUNCTION: ENGINE 0x1066BB70
	content::MemberList* ConstraintAngularSpringSharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstraintAngularSpringSharedProperties, float, 0>("p"),
				content::MemberOffset(&((ConstraintAngularSpringSharedProperties*)0)->springConstant,
				(int)&((ConstraintAngularSpringSharedProperties*)0)->springConstant), "springConstant" },
			{ content::GetMemberPrimitiveMetaType<ConstraintAngularSpringSharedProperties, float, 1>("p"),
				content::MemberOffset(&((ConstraintAngularSpringSharedProperties*)0)->dampingConstant,
				(int)&((ConstraintAngularSpringSharedProperties*)0)->dampingConstant), "dampingConstant" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066BCB0
	content::MemberList* ConstraintAngularSpring::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintAngularSpring> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintAngularSpring, 0>("p"),
				(int)&((ConstraintAngularSpring*)0)->axisA, "axisA" },
			{ content::GetMemberVectorMetaType<ConstraintAngularSpring, 1>("p"),
				(int)&((ConstraintAngularSpring*)0)->axisB, "axisB" },
			{ content::GetReferenceMemberMetaType(&ConstraintAngularSpring::GetSharedProperties,
				&ConstraintAngularSpring::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// Kept copies: the casters, the meta type getters and the reference helpers of the reflection above
	// FUNCTION: ENGINE 0x1066B8D0
	// FUNCTION: ENGINE 0x1066B900
	// FUNCTION: ENGINE 0x1066B930
	// FUNCTION: ENGINE 0x1066B950
	// FUNCTION: ENGINE 0x1066B9B0
	// FUNCTION: ENGINE 0x1066B9C0
	// FUNCTION: ENGINE 0x1066B9D0
	// FUNCTION: ENGINE 0x1066BA00
	// FUNCTION: ENGINE 0x1066BA70
	// FUNCTION: ENGINE 0x1066BAB0
	// FUNCTION: ENGINE 0x1066BAF0
	// FUNCTION: ENGINE 0x1066BB00
	// FUNCTION: ENGINE 0x1066BB20
	// FUNCTION: ENGINE 0x1066BB40
	// FUNCTION: ENGINE 0x1066BB50
	// FUNCTION: ENGINE 0x1066BC20
	// FUNCTION: ENGINE 0x1066BC40
}
