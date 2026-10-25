// The angular velocity constraint, its shared properties and the reflection of them (the unit has an assert; its
// path is code/ravenphysics/constraints/src/angularvelocity.cpp).
#include "code/content/vectormetatype.h"
#include "code/core/debug.h"
#include "code/core/refptr.h"
#include "code/math/mathconstants.h"
#include "code/ravenphysics/constraints/constraints.h"

#define ANGULARVELOCITY_FILE "..\\..\\..\\code\\ravenphysics\\constraints\\src\\angularvelocity.cpp"

namespace ravenphysics
{
	template struct content::BaseClassCasterImpl<Constraint, ConstraintAngularVelocity>;

	// FUNCTION: ENGINE 0x1066BDB0
	content::ClassInfo* ConstraintAngularVelocity::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintAngularVelocity";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066BDF0
	content::ClassInfo* ConstraintAngularVelocitySharedProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::ConstraintAngularVelocitySharedProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066BE30
	ConstraintAngularVelocity::ConstraintAngularVelocity() :
		Constraint(5),
		axis(0.0f, 1.0f, 0.0f),
		angularVelocity(0.0f),
		maxForce(1000.0f),
		sharedProperties(0)
	{
	}

	// FUNCTION: ENGINE 0x1066BE80
	ConstraintAngularVelocity::ConstraintAngularVelocity(const CollisionHandle* first, const CollisionHandle* second) :
		Constraint(first, second, 5),
		axis(0.0f, 1.0f, 0.0f),
		angularVelocity(0.0f),
		maxForce(1000.0f),
		sharedProperties(0)
	{
	}

	// FUNCTION: ENGINE 0x1066BEE0
	ConstraintAngularVelocity::ConstraintAngularVelocity(const ConstraintAngularVelocity& other) :
		Constraint(other)
	{
		axis.x = other.axis.x;
		axis.y = other.axis.y;
		axis.z = other.axis.z;
		angularVelocity = other.angularVelocity;
		maxForce = other.maxForce;
		sharedProperties = other.sharedProperties;
		if (sharedProperties)
		{
			sharedProperties->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x1066BF30
	ConstraintAngularVelocitySharedProperties* ConstraintAngularVelocity::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x1066BF40
	void ConstraintAngularVelocity::SetAxis(const math::Vector* newAxis)
	{
		math::Vector* target = &axis;
		target->x = newAxis->x;
		target->y = newAxis->y;
		target->z = newAxis->z;
		float length = target->Normalize();
		OLD_ASSERT_AT(ANGULARVELOCITY_FILE, 0x9D, length > math::EPSILON_SMALL, "l > math::EPSILON_FLOAT",
			"Axis must be of non zero length.");
	}

	// FUNCTION: ENGINE 0x1066BFB0
	void ConstraintAngularVelocity::SetAngularVelocity(float value)
	{
		angularVelocity = value;
	}

	// FUNCTION: ENGINE 0x1066BFC0
	void ConstraintAngularVelocity::SetMaxForce(float value)
	{
		maxForce = value;
	}

	// FUNCTION: ENGINE 0x1066BFD0
	unsigned short ConstraintAngularVelocity::GetKind(int unused)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1066C060
	// EQUIVALENT: the same stores; the engine stores the reference count ahead of the first member, 62.8 %
	ConstraintAngularVelocitySharedProperties::ConstraintAngularVelocitySharedProperties() :
		angularVelocity(0.0f),
		maxForce(1000.0f)
	{
	}

	// FUNCTION: ENGINE 0x1066C100
	ConstraintAngularVelocity::~ConstraintAngularVelocity()
	{
		core::SafeRelease(sharedProperties);
	}

	// FUNCTION: ENGINE 0x1066C120
	void ConstraintAngularVelocity::SetSharedProperties(ConstraintAngularVelocitySharedProperties* properties)
	{
		core::RefAssign(sharedProperties, properties);
		if (sharedProperties)
		{
			angularVelocity = sharedProperties->angularVelocity;
			maxForce = sharedProperties->maxForce;
		}
	}

	// FUNCTION: ENGINE 0x1066C250
	content::MemberList* ConstraintAngularVelocitySharedProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstraintAngularVelocitySharedProperties, float, 0>("p"),
				content::MemberOffset(&((ConstraintAngularVelocitySharedProperties*)0)->angularVelocity,
				(int)&((ConstraintAngularVelocitySharedProperties*)0)->angularVelocity), "angularVelocity" },
			{ content::GetMemberPrimitiveMetaType<ConstraintAngularVelocitySharedProperties, float, 1>("p"),
				content::MemberOffset(&((ConstraintAngularVelocitySharedProperties*)0)->maxForce,
				(int)&((ConstraintAngularVelocitySharedProperties*)0)->maxForce), "maxForce" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066C390
	content::MemberList* ConstraintAngularVelocity::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Constraint>();
		static content::BaseClassCasterImpl<Constraint, ConstraintAngularVelocity> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstraintAngularVelocity, 0>("p"),
				(int)&((ConstraintAngularVelocity*)0)->axis, "axisA" },
			{ content::GetReferenceMemberMetaType(&ConstraintAngularVelocity::GetSharedProperties,
				&ConstraintAngularVelocity::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Kept copies: the casters, the meta type getters and the reference helpers of the reflection above
	// FUNCTION: ENGINE 0x1066BFE0
	// FUNCTION: ENGINE 0x1066C010
	// FUNCTION: ENGINE 0x1066C030
	// FUNCTION: ENGINE 0x1066C090
	// FUNCTION: ENGINE 0x1066C0A0
	// FUNCTION: ENGINE 0x1066C0B0
	// FUNCTION: ENGINE 0x1066C0E0
	// FUNCTION: ENGINE 0x1066C150
	// FUNCTION: ENGINE 0x1066C190
	// FUNCTION: ENGINE 0x1066C1D0
	// FUNCTION: ENGINE 0x1066C1E0
	// FUNCTION: ENGINE 0x1066C200
	// FUNCTION: ENGINE 0x1066C220
	// FUNCTION: ENGINE 0x1066C230
	// FUNCTION: ENGINE 0x1066C300
	// FUNCTION: ENGINE 0x1066C320
}
