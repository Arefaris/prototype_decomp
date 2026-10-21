// The joint drivers of the secondary physics (RTTI and reflection names): engine::SecondaryPhysicsJointDriver (the
// interface, six vftable slots) and its three implementations engine::SecondaryPhysicsAmbientWind,
// engine::SecondaryPhysicsPinJoint and engine::SecondaryPhysicsPoweredJoint. A driver owns a number of constraints of
// the physics library (their handles live in an array of the secondary physics properties, one run per driver) and
// feeds them every step. The interface's own members (class info, empty member list, slots) are in another unit
// (0x10937750 - 0x10937820); this unit holds the three implementations, their reflection and the kept copies of the
// interface's constructor and deleting destructor. Unit 0x10915FD0 - 0x109179F0 (no assert path; the directory and file
// name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_SECONDARYPHYSICSJOINTS_H
#define ENGINE_SECONDARYPHYSICSJOINTS_H

#include "code/container/arraydynamicstatic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	struct CollisionHandle;
	class CollisionShape;
}

namespace engine
{
	// A run of constraint handles of the properties' handle array (the driver's share of it)
	struct SecondaryPhysicsHandleRange
	{
		ravenphysics::CollisionHandle* begin;
		ravenphysics::CollisionHandle* end;
	};

	class SecondaryPhysicsJointDriver
	{
	public:
		// 0x10916010 (a copy of the inline constructor)
		SecondaryPhysicsJointDriver()
		{
		}
		// 0x109377C0 (another unit; deleting destructor 0x10916020)
		virtual ~SecondaryPhysicsJointDriver();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1: how many constraint handles the driver owns (0x109377D0: none)
		virtual int GetHandleCount();
		// vftable slot 2 (0x109377E0)
		virtual void Slot2(SecondaryPhysicsHandleRange* range);
		// vftable slot 3 (0x109377F0)
		virtual void Slot3(const SecondaryPhysicsHandleRange* range);
		// vftable slot 4 (0x10937800)
		virtual void Slot4(const SecondaryPhysicsHandleRange* range, const void* a, int b, const void* c, const void* d,
			bool* e);
		// vftable slot 5 (0x10937810)
		virtual void Slot5(ravenphysics::CollisionShape* shape, const math::Matrix* matrix);
	};

	// Pushes a body about with a random wind
	class SecondaryPhysicsAmbientWind : public SecondaryPhysicsJointDriver
	{
	public:
		// 0x109161C0
		SecondaryPhysicsAmbientWind();
		// 0x10916040 (deleting destructor 0x10916230)
		virtual ~SecondaryPhysicsAmbientWind();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x10916050): the wind of this step, a random vector scaled by windForceScale (one random
		// number for all three components when constantDirection is set), added to the shape's velocity
		virtual void Slot5(ravenphysics::CollisionShape* shape, const math::Matrix* matrix);

		math::Vector windForceScale;  // +4
		bool constantDirection;  // +0x10
	};

	// Pins a point of a body to its parent
	class SecondaryPhysicsPinJoint : public SecondaryPhysicsJointDriver
	{
	public:
		// 0x10916400
		SecondaryPhysicsPinJoint();
		// 0x109163A0 (deleting destructor 0x10916460)
		virtual ~SecondaryPhysicsPinJoint();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x109163B0)
		virtual int GetHandleCount();
		// vftable slot 2 (0x10916480)
		virtual void Slot2(SecondaryPhysicsHandleRange* range);
		// vftable slot 4 (0x109164A0)
		virtual void Slot4(const SecondaryPhysicsHandleRange* range, const void* a, int b, const void* c, const void* d,
			bool* e);

		math::Vector constraintPointOffset;  // +4
	};

	// Turns a body towards its parent with a force that follows a curve of the angle
	class SecondaryPhysicsPoweredJoint : public SecondaryPhysicsJointDriver
	{
	public:
		// One point of the force curve: the angle and the largest force at it
		struct ForceCurvePoint
		{
			// 0x10916810
			ForceCurvePoint()
			{
				angle = 0.0f;
				maxOrientationForce = 0.0f;
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10916830 / 0x10916840 (the member is kept in radians)
			float GetAngleDegrees() const;
			void SetAngleDegrees(float degrees);

			float angle;  // +0
			float maxOrientationForce;  // +4
		};

		typedef container::ArrayDynamic<ForceCurvePoint, container::AllocatorNew> ForceCurveArray;

		// 0x10917900
		SecondaryPhysicsPoweredJoint();
		// 0x10917930 (deleting destructor 0x109179D0)
		virtual ~SecondaryPhysicsPoweredJoint();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10916970 / 0x10916980
		float GetMaxAngularVelocityDegrees() const;
		void SetMaxAngularVelocityDegrees(float degrees);

		// 0x10916B90: the largest force at an angle, interpolated on the curve
		float EvaluateForceCurve(float angle) const;

		// vftable slot 1 (0x10916860): one handle, four with a damping constant
		virtual int GetHandleCount();
		// vftable slot 2 (0x10916AA0)
		virtual void Slot2(SecondaryPhysicsHandleRange* range);
		// vftable slot 3 (0x10916B10)
		virtual void Slot3(const SecondaryPhysicsHandleRange* range);
		// vftable slot 4 (0x10916F20)
		virtual void Slot4(const SecondaryPhysicsHandleRange* range, const void* a, int b, const void* c, const void* d,
			bool* e);

		ForceCurveArray forceCurve;  // +4
		float unknown10;
		float dampingConstant;  // +0x14
		float maxAngularVelocity;  // +0x18 (radians)
	};
}

#endif
