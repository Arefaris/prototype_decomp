// The deformable orientation constraint, its shared properties and the reflection of them (the unit after
// deformablefixdistancealongaxis.cpp; no assert path of its own, so the file name is a guess).
#include "code/content/vectormetatype.h"
#include "code/core/refptr.h"
#include "code/math/matrix3.h"
#include "code/ravenphysics/constraints/constraints.h"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintDeformableOrientation>;

	// FUNCTION: ENGINE 0x10692C10
	content::ClassInfo* ConstraintDeformableOrientation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintDeformableOrientation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10692C50
	content::ClassInfo* DeformableOrientationConstraintSharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::DeformableOrientationConstraintSharedProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10692C90
	ConstraintDeformableOrientation::ConstraintDeformableOrientation() :
		Constraint(7),
		sharedProperties(0),
		maximumStaticForce(1e12f),
		maximumDynamicForce(1e12f),
		flag(false)
	{
		basis.Identity();
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
	}

	// FUNCTION: ENGINE 0x10692CF0
	ConstraintDeformableOrientation::ConstraintDeformableOrientation(const CollisionHandle* first,
		const CollisionHandle* second) :
		Constraint(first, second, 7),
		sharedProperties(0),
		maximumStaticForce(1e12f),
		maximumDynamicForce(1e12f),
		flag(false)
	{
		basis.Identity();
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
	}

	// FUNCTION: ENGINE 0x10692D60
	DeformableOrientationConstraintSharedProperties* ConstraintDeformableOrientation::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x10692D70
	unsigned short ConstraintDeformableOrientation::GetKind(int unused)
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x10692D80
	void ConstraintDeformableOrientation::SetMaximumStaticForce(float value)
	{
		maximumStaticForce = value;
	}

	// FUNCTION: ENGINE 0x10692D90
	void ConstraintDeformableOrientation::SetMaximumDynamicForce(float value)
	{
		maximumDynamicForce = value;
	}

	// FUNCTION: ENGINE 0x10692DF0
	DeformableOrientationConstraintSharedProperties::DeformableOrientationConstraintSharedProperties() :
		maximumStaticForce(10000.0f),
		maximumDynamicForce(10000.0f)
	{
	}

	// FUNCTION: ENGINE 0x10692E90
	ConstraintDeformableOrientation::~ConstraintDeformableOrientation()
	{
		core::SafeRelease(sharedProperties);
	}

	// FUNCTION: ENGINE 0x10692EB0
	// NONMATCHING: the engine copies the three rows of the basis with the vector copy constructor loop (__vec_cctor) in
	// place; a member object or a plain copy does not give that code, best about 60 %
#ifdef NONMATCHING
	ConstraintDeformableOrientation::ConstraintDeformableOrientation(const ConstraintDeformableOrientation& other) :
		Constraint(other),
		sharedProperties(other.sharedProperties),
		basis(other.basis)
	{
		maximumStaticForce = other.maximumStaticForce;
		maximumDynamicForce = other.maximumDynamicForce;
		flag = other.flag;
		if (sharedProperties)
		{
			sharedProperties->AddRef();
		}
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
	}
#endif

	// FUNCTION: ENGINE 0x10692F30
	void ConstraintDeformableOrientation::SetSharedProperties(DeformableOrientationConstraintSharedProperties* properties)
	{
		core::RefAssign(sharedProperties, properties);
		if (sharedProperties)
		{
			maximumStaticForce = sharedProperties->maximumStaticForce;
			maximumDynamicForce = sharedProperties->maximumDynamicForce;
		}
	}

	// FUNCTION: ENGINE 0x10693060
	content::MemberList* DeformableOrientationConstraintSharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DeformableOrientationConstraintSharedProperties, float, 0>("p"),
				content::MemberOffset(&((DeformableOrientationConstraintSharedProperties*)0)->maximumStaticForce,
				(int)&((DeformableOrientationConstraintSharedProperties*)0)->maximumStaticForce),
				"maximumStaticForce" },
			{ content::GetMemberPrimitiveMetaType<DeformableOrientationConstraintSharedProperties, float, 1>("p"),
				content::MemberOffset(&((DeformableOrientationConstraintSharedProperties*)0)->maximumDynamicForce,
				(int)&((DeformableOrientationConstraintSharedProperties*)0)->maximumDynamicForce),
				"maximumDynamicForce" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x106931A0
	content::MemberList* ConstraintDeformableOrientation::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintDeformableOrientation> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMemberMetaType(&ConstraintDeformableOrientation::GetSharedProperties,
				&ConstraintDeformableOrientation::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// Kept copies: the casters, the deleting destructors, the meta type getters and the reference helpers of the
	// reflection above
	// FUNCTION: ENGINE 0x10692DA0
	// FUNCTION: ENGINE 0x10692DC0
	// FUNCTION: ENGINE 0x10692E20
	// FUNCTION: ENGINE 0x10692E30
	// FUNCTION: ENGINE 0x10692E40
	// FUNCTION: ENGINE 0x10692E70
	// FUNCTION: ENGINE 0x10692F60
	// FUNCTION: ENGINE 0x10692FA0
	// FUNCTION: ENGINE 0x10692FE0
	// FUNCTION: ENGINE 0x10692FF0
	// FUNCTION: ENGINE 0x10693010
	// FUNCTION: ENGINE 0x10693030
	// FUNCTION: ENGINE 0x10693040
	// FUNCTION: ENGINE 0x10693110
	// FUNCTION: ENGINE 0x10693130
}
