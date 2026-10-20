// The constraints of code/ravenphysics/constraints (assert path .../constraints/src/constraints.cpp for the unit that
// holds the reflection of them). Class names are the engine's own (RTTI); member names are the reflected ones where
// the reflection names them, else guesses.
#ifndef RAVENPHYSICS_CONSTRAINTS_CONSTRAINTS_H
#define RAVENPHYSICS_CONSTRAINTS_CONSTRAINTS_H

#include "code/ravenphysics/constraints/constraint.h"

namespace ravenphysics
{
	// Keeps a point of the second object inside a sphere around a point of the first
	class ConstraintInsideOfSphere : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x10661580)
		ConstraintInsideOfSphere();
		// Between the objects two handles name (0x106615F0)
		ConstraintInsideOfSphere(const CollisionHandle* first, const CollisionHandle* second);
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// The setters (0x10661660 / 0x10661680 / 0x106616A0 / 0x106616B0 / 0x106616C0)
		void SetPointA(const math::Vector* point);
		void SetPointB(const math::Vector* point);
		void SetSphereRadius(float value);
		void SetUnknown40(float value);
		void SetUnknown44(float value);

		math::Vector pointA;          // 0x24
		math::Vector pointB;          // 0x30
		float sphereRadius;           // 0x3C
		float unknown40;              // 0x40
		float unknown44;              // 0x44
	};

	// Keeps the second object's axis inside a cone around an axis of the first
	class ConstraintInsideOfCone : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066AB40)
		ConstraintInsideOfCone();
		// Between the objects two handles name (0x1066ABC0)
		ConstraintInsideOfCone(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual unsigned short GetKind(int unused);

		// The flag the solver raises (0x1066AC70 / 0x1066AC80)
		bool GetFlag() const;
		void ClearFlag();
		// The angle of the cone, kept as its sine and cosine (0x1066AAD0 / 0x1066AC90)
		float GetConeAngle() const;
		void SetConeAngle(float angle);
		// The axes (0x1066AAE0 / 0x1066ACC0 and 0x1066AAF0 / 0x1066AD00); the setters normalise
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		const math::Vector* GetAxisB() const;
		void SetAxisB(const math::Vector* axis);

		math::Vector axisA;           // 0x24
		math::Vector axisALocal;      // 0x30 (the axis before the matrix turns it into axisA)
		math::Vector axisB;           // 0x3C
		float sine;                   // 0x48
		float cosine;                 // 0x4C
		float unknown50;              // 0x50
		float unknown54;              // 0x54
		bool flag;                    // 0x58
	};
}

#endif
