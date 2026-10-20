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

	// Pins a point of the second object to a point of the first
	class ConstraintBallInSocket : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1065B9F0)
		ConstraintBallInSocket();
		// Between the objects two handles name (0x1065BA70)
		ConstraintBallInSocket(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// The flag the solver raises (0x1065BB70 / 0x1065BB80)
		bool GetFlag() const;
		void ClearFlag();
		// The point of the first object (0x1065B9A0 / 0x1065BAF0): the setter also sets the local point
		const math::Vector* GetPointA() const;
		void SetPointA(const math::Vector* point);
		// The point of the second object (0x1065BB20)
		void SetPointB(const math::Vector* point);

		math::Vector pointA;          // 0x24
		math::Vector pointALocal;     // 0x30 (the point before the matrix turns it into pointA)
		math::Vector pointB;          // 0x3C
		float unknown48;              // 0x48
		float unknown4C;              // 0x4C
		float unknown50;              // 0x50
		float unknown54;              // 0x54
		float unknown58;              // 0x58
		float unknown5C;              // 0x5C
		bool flag;                    // 0x60
	};

	// Keeps an axis of the second object parallel to an axis of the first
	class ConstraintAlign2Axes : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1065BFE0)
		ConstraintAlign2Axes();
		// Between the objects two handles name (0x1065C0E0)
		ConstraintAlign2Axes(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual unsigned short GetKind(int unused);

		// The axes (0x1065BEC0 / 0x1065BF20 and 0x1065BED0 / 0x1065BF60); the setters normalise, the second also
		// builds the two axes perpendicular to it
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		const math::Vector* GetAxisB() const;
		void SetAxisB(const math::Vector* axis);

		math::Vector axisA;           // 0x24
		math::Vector axisALocal;      // 0x30 (the axis before the matrix turns it into axisA)
		math::Vector axisB;           // 0x3C
		math::Vector perpendicular;   // 0x48
		math::Vector cross;           // 0x54
		float unknown60;              // 0x60
		float unknown64;              // 0x64
		float unknown68;              // 0x68
		float unknown6C;              // 0x6C
		float unknown70;              // 0x70
		float unknown74;              // 0x74
	};

	// A ball in a socket and two aligned axes: a hinge
	class ConstraintHinge : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066B2B0)
		ConstraintHinge();
		// Between the objects two handles name (0x1066B0E0)
		ConstraintHinge(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// Vftable slots 8 and 9: take the object a handle names for one side, in the constraint and in both parts (0x1066B1A0 / 0x1066B1E0)
		virtual void SetFirstObject(const CollisionHandle* handle);
		virtual void SetSecondObject(const CollisionHandle* handle);
		// The ball's flag (0x1066B180 / 0x1066B190)
		bool GetFlag() const;
		void ClearFlag();
		// The ball's points (0x1066B280 / 0x1066B240 and 0x1066B290 / 0x1066B250) and the axes (0x1066B260 / 0x1066B220
		// and 0x1066B270 / 0x1066B230)
		const math::Vector* GetPointA() const;
		void SetPointA(const math::Vector* point);
		const math::Vector* GetPointB() const;
		void SetPointB(const math::Vector* point);
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		const math::Vector* GetAxisB() const;
		void SetAxisB(const math::Vector* axis);

		ConstraintBallInSocket ball;  // 0x24
		ConstraintAlign2Axes align;   // 0x88
	};
}

#endif
