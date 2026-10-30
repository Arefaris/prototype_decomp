// The shared properties of the constraints (RTTI: ravenphysics::Constraint...SharedProperties): content library objects that
// several constraints refer to for their constants. They are apart from constraints.h so that the reflected-class
// declarations of the engine's factories can use them without the collision object.
#ifndef RAVENPHYSICS_CONSTRAINTS_SHAREDPROPERTIES_H
#define RAVENPHYSICS_CONSTRAINTS_SHAREDPROPERTIES_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace ravenphysics
{
	// The numbers an angular spring constraint shares between the constraints that refer to the same properties
	class ConstraintAngularSpringSharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x1066B980)
		ConstraintAngularSpringSharedProperties();

		float springConstant;         // 0x08
		float dampingConstant;        // 0x0C
	};

	// The numbers an angular velocity constraint shares
	class ConstraintAngularVelocitySharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x1066C060)
		ConstraintAngularVelocitySharedProperties();

		float angularVelocity;        // 0x08
		float maxForce;               // 0x0C
	};

	// The numbers a spring along an axis shares between the constraints that refer to the same properties
	class ConstraintSpringAlongAxisSharedProperties : public content::MetaLoadObject
	{
	public:
		// What the spring and damping constants are scaled by (RTTI: ...::ScaleByMassType; the value names are the
		// engine's own)
		enum ScaleByMassType
		{
			SCALE_NONE = 0,
			SCALE_OBJECT_A = 1,
			SCALE_OBJECT_B = 2,
			SCALE_GREATER = 3,
			SCALE_TOTAL = 4
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x10670050)
		ConstraintSpringAlongAxisSharedProperties();

		float springConstant;         // 0x08
		float dampingConstant;        // 0x0C
		ScaleByMassType scaleByMassType;  // 0x10
	};

	// The numbers a deformable slider constraint shares (RTTI: DeformableSliderConstraintSharedProperties)
	class DeformableSliderConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x10692590)
		DeformableSliderConstraintSharedProperties();

		float distanceCorrectionScale;     // 0x08
		float maxDistanceCorrectionForce;  // 0x0C
		float maximumStaticForce;          // 0x10
		float maximumDynamicForce;         // 0x14
	};

	// The forces a deformable orientation constraint gives way at (RTTI: DeformableOrientationConstraintSharedProperties)
	class DeformableOrientationConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x10692DF0)
		DeformableOrientationConstraintSharedProperties();

		float maximumStaticForce;     // 0x08
		float maximumDynamicForce;    // 0x0C
	};

	// The limits a powered orientation constraint turns the second object with (RTTI: PoweredConstraintSharedProperties)
	class PoweredConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x10693B90)
		PoweredConstraintSharedProperties();

		float maxAngularVelocity;     // 0x08
		float maxOrientationForce;    // 0x0C
	};

	// The limits a powered linear constraint moves the second object with (RTTI: PoweredLinearConstraintSharedProperties)
	class PoweredLinearConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The engine's defaults (0x10694080)
		PoweredLinearConstraintSharedProperties();

		float maxLinearVelocity;      // 0x08
		float maxLinearForce;         // 0x0C
		float alignmentRigidity;      // 0x10
	};
}

#endif
