// engine::PhysicsBehaviour (RTTI name; base engine::Behaviour and ravenphysics::BroadPhaseObjectNotifier): unit
// 0x10921620 - 0x10924AFE. The reflection, the accessors it reaches the members through and the element access of the
// "properties" array are reconstructed.
#include "code/engine/physicsbehaviour.h"
#include "code/core/refptr.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10921A10
	content::ClassInfo* PhysicsBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "PhysicsBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109219D0
	content::ClassInfo* PhysicsBehaviour::PhysicsProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "PhysicsProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10923160
	content::MemberList* PhysicsBehaviour::PhysicsProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<PhysicsProperties>(true, true, "p"),
				ENGINE_NAME_OFFSET(PhysicsProperties, objectName), "objectName" },
			{ content::GetMemberPrimitiveMetaType<PhysicsProperties, float, 0>("p"),
				ENGINE_OFFSET(PhysicsProperties, mass), "mass" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109219B0
	ravenphysics::AbstractPhysicsObjectFactory* PhysicsBehaviour::GetPhysicsObject() const
	{
		return physicsObject;
	}

	// FUNCTION: ENGINE 0x10922C20
	void PhysicsBehaviour::SetPhysicsObject(ravenphysics::AbstractPhysicsObjectFactory* factory)
	{
		core::RefAssign(physicsObject, factory);
	}

	// FUNCTION: ENGINE 0x109219C0
	ravenphysics::AbstractPhysicsObjectFactory* PhysicsBehaviour::GetPhysicsObjectFactory() const
	{
		return physicsObjectFactory;
	}

	// FUNCTION: ENGINE 0x10922C40
	void PhysicsBehaviour::SetPhysicsObjectFactory(ravenphysics::AbstractPhysicsObjectFactory* factory)
	{
		core::RefAssign(physicsObjectFactory, factory);
	}

	// FUNCTION: ENGINE 0x10921980
	float PhysicsBehaviour::GetPhysicsToPoseBlendFactor() const
	{
		return physicsToPoseBlendFactor.Get();
	}

	// FUNCTION: ENGINE 0x10921990
	void PhysicsBehaviour::SetPhysicsToPoseBlendFactor(float value)
	{
		physicsToPoseBlendFactor.Set(value);
	}

	// FUNCTION: ENGINE 0x10921960
	bool PhysicsBehaviour::GetAutoPoseSync() const
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10921970
	void PhysicsBehaviour::SetAutoPoseSync(bool value)
	{
	}

	// FUNCTION: ENGINE 0x109239B0
	content::MemberList* PhysicsBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, PhysicsBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMemberMetaType<PhysicsBehaviour, ravenphysics::AbstractPhysicsObjectFactory, 0>(
				&PhysicsBehaviour::GetPhysicsObject, &PhysicsBehaviour::SetPhysicsObject, "p"), 0, "physicsObject" },
			{ content::GetReferenceMemberMetaType<PhysicsBehaviour, ravenphysics::AbstractPhysicsObjectFactory, 1>(
				&PhysicsBehaviour::GetPhysicsObjectFactory, &PhysicsBehaviour::SetPhysicsObjectFactory, "p"), 0,
				"physicsObjectFactory" },
			{ content::GetReferenceMetaType<PhysicsBehaviour, ravenphysics::MaterialLoader>("p"),
				ENGINE_OFFSET(PhysicsBehaviour, overrideMaterial), "overrideMaterial" },
			{ content::GetReferenceMetaType<PhysicsBehaviour, ravenphysics::IntersectionPropertiesLoader>("p"),
				ENGINE_OFFSET(PhysicsBehaviour, overrideIntersectionProperties), "overrideIntersectionProperties" },
			{ content::GetArrayDynamicMetaType<PhysicsBehaviour, PropertiesArray>(
				content::GetClassMetaType<PhysicsProperties>(), "p"),
				ENGINE_OFFSET(PhysicsBehaviour, properties), "properties" },
			{ content::GetMemberPrimitiveMetaType<PhysicsBehaviour, bool, 0>("p"),
				ENGINE_OFFSET(PhysicsBehaviour, manualVelocities), "manualVelocities" },
			{ content::GetMemberPrimitiveMetaType<PhysicsBehaviour, bool, 1>("p"),
				ENGINE_OFFSET(PhysicsBehaviour, disablePhysicsObjectSelfCollisions),
				"disablePhysicsObjectSelfCollisions" },
			{ content::GetMemberMetaType<PhysicsBehaviour, float, 0>(&PhysicsBehaviour::GetPhysicsToPoseBlendFactor,
				&PhysicsBehaviour::SetPhysicsToPoseBlendFactor, ""), 0, "physicsToPoseBlendFactor" },
			{ content::GetMemberMetaType<PhysicsBehaviour, bool, 0>(&PhysicsBehaviour::GetAutoPoseSync,
				&PhysicsBehaviour::SetAutoPoseSync, "p"), 0, "autoPoseSync" },
			{ content::GetMemberPrimitiveMetaType<PhysicsBehaviour, bool, 2>("p"),
				ENGINE_OFFSET(PhysicsBehaviour, preserveJointAnimation), "preserveJointAnimation" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10921BD0
// FUNCTION: ENGINE 0x10921C10
// FUNCTION: ENGINE 0x10921C20
// FUNCTION: ENGINE 0x10921C60
// FUNCTION: ENGINE 0x10921DF0
// FUNCTION: ENGINE 0x10922D60
// FUNCTION: ENGINE 0x10922DA0
// FUNCTION: ENGINE 0x10922DE0
// FUNCTION: ENGINE 0x10922E20
// FUNCTION: ENGINE 0x10922E60
// FUNCTION: ENGINE 0x10922E70
// FUNCTION: ENGINE 0x10922EC0
// FUNCTION: ENGINE 0x10922ED0
// FUNCTION: ENGINE 0x10922EE0
// FUNCTION: ENGINE 0x10922F00
// FUNCTION: ENGINE 0x10922F20
// FUNCTION: ENGINE 0x10922F40
// FUNCTION: ENGINE 0x10922F70
// FUNCTION: ENGINE 0x10922F90
// FUNCTION: ENGINE 0x10922FB0
// FUNCTION: ENGINE 0x10922FC0
// FUNCTION: ENGINE 0x10922FD0
// FUNCTION: ENGINE 0x10922FE0
// FUNCTION: ENGINE 0x10922FF0
// FUNCTION: ENGINE 0x10923020
// FUNCTION: ENGINE 0x10923040
// FUNCTION: ENGINE 0x10923060
// FUNCTION: ENGINE 0x10923090
// FUNCTION: ENGINE 0x109230B0
// FUNCTION: ENGINE 0x109230E0
// FUNCTION: ENGINE 0x10923140
// FUNCTION: ENGINE 0x10923550
// FUNCTION: ENGINE 0x109235A0
// FUNCTION: ENGINE 0x10923630
// FUNCTION: ENGINE 0x109236C0
// FUNCTION: ENGINE 0x10923710
// FUNCTION: ENGINE 0x10923760
// FUNCTION: ENGINE 0x109237B0
// FUNCTION: ENGINE 0x10923830
// FUNCTION: ENGINE 0x109238C0
// FUNCTION: ENGINE 0x10923930
// FUNCTION: ENGINE 0x10923970
// FUNCTION: ENGINE 0x10923DA0
// FUNCTION: ENGINE 0x10923E70
// FUNCTION: ENGINE 0x10924470
// FUNCTION: ENGINE 0x109244A0
// FUNCTION: ENGINE 0x109244E0
// FUNCTION: ENGINE 0x10924900
