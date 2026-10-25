// The constraints of code/ravenphysics/constraints (assert path .../constraints/src/constraints.cpp for the unit that
// holds the reflection of them). Class names are the engine's own (RTTI); member names are the reflected ones where
// the reflection names them, else guesses.
#ifndef RAVENPHYSICS_CONSTRAINTS_CONSTRAINTS_H
#define RAVENPHYSICS_CONSTRAINTS_CONSTRAINTS_H

#include "code/ravenphysics/constraints/constraint.h"
#include "code/ravenphysics/constraints/sharedproperties.h"

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

	// Turns the second object back to the first with a spring along the axes
	class ConstraintAngularSpring : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066B720)
		ConstraintAngularSpring();
		// Between the objects two handles name (0x1066B770)
		ConstraintAngularSpring(const CollisionHandle* first, const CollisionHandle* second);
		// A copy (0x1066B7D0)
		ConstraintAngularSpring(const ConstraintAngularSpring& other);
		virtual ~ConstraintAngularSpring();
		virtual unsigned short GetKind(int unused);

		// The shared properties (0x1066B830 / 0x1066BA40); the setter also takes the spring and damping constants over
		ConstraintAngularSpringSharedProperties* GetSharedProperties() const;
		void SetSharedProperties(ConstraintAngularSpringSharedProperties* properties);
		// The axes (0x1066B840 / 0x1066B870); the setters normalise
		void SetAxisA(const math::Vector* axis);
		void SetAxisB(const math::Vector* axis);
		// The constants (0x1066B8A0 / 0x1066B8B0)
		void SetSpringConstant(float value);
		void SetDampingConstant(float value);

		math::Vector axisA;           // 0x24
		math::Vector axisB;           // 0x30
		float springConstant;         // 0x3C
		float dampingConstant;        // 0x40
		ConstraintAngularSpringSharedProperties* sharedProperties;  // 0x44
	};

	// Turns the second object against the first around an axis at a speed, with a limit on the force
	class ConstraintAngularVelocity : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066BE30)
		ConstraintAngularVelocity();
		// Between the objects two handles name (0x1066BE80)
		ConstraintAngularVelocity(const CollisionHandle* first, const CollisionHandle* second);
		// A copy (0x1066BEE0)
		ConstraintAngularVelocity(const ConstraintAngularVelocity& other);
		virtual ~ConstraintAngularVelocity();
		virtual unsigned short GetKind(int unused);

		// The shared properties (0x1066BF30 / 0x1066C120); the setter also takes the velocity and force over
		ConstraintAngularVelocitySharedProperties* GetSharedProperties() const;
		void SetSharedProperties(ConstraintAngularVelocitySharedProperties* properties);
		// The axis (0x1066BF40); the setter normalises
		void SetAxis(const math::Vector* axis);
		// The numbers (0x1066BFB0 / 0x1066BFC0)
		void SetAngularVelocity(float value);
		void SetMaxForce(float value);

		math::Vector axis;            // 0x24
		float angularVelocity;        // 0x30
		float maxForce;               // 0x34
		ConstraintAngularVelocitySharedProperties* sharedProperties;  // 0x38
	};

	// Keeps a point of the second object on a line through a point of the first, with a limit on how far it may go
	class ConstraintSlider : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066F810)
		ConstraintSlider();
		// Between the objects two handles name (0x1066F8F0)
		ConstraintSlider(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// The point of the first object (0x1066F5D0 / 0x1066F790); the setter also sets the local point
		const math::Vector* GetPointA() const;
		void SetPointA(const math::Vector* point);
		// The axis (0x1066F5C0 / 0x1066F720); the setter normalises and builds the two axes perpendicular to it
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		// The perpendicular axes from the axis (0x1066F6E0)
		void UpdatePerpendicular();
		// The point of the second object (0x1066F7C0) and the extent (0x1066F770)
		void SetPointB(const math::Vector* point);
		void SetExtent(float value);

		math::Vector pointA;          // 0x24
		math::Vector pointALocal;     // 0x30 (the point before the matrix turns it into pointA)
		math::Vector axisA;           // 0x3C
		math::Vector axisALocal;      // 0x48 (the axis before the matrix turns it into axisA)
		math::Vector perpendicular;   // 0x54
		math::Vector cross;           // 0x60
		float unknown6C;              // 0x6C
		float unknown70;              // 0x70
		float unknown74;              // 0x74
		math::Vector pointB;          // 0x78
		float extent;                 // 0x84
	};

	// A spring between a point of each object that pulls them to a stable distance along the line between them
	class ConstraintSpringAlongAxis : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x1066FD10)
		ConstraintSpringAlongAxis();
		// Between the objects two handles name (0x1066FD80)
		ConstraintSpringAlongAxis(const CollisionHandle* first, const CollisionHandle* second);
		// A copy (0x1066FDF0)
		ConstraintSpringAlongAxis(const ConstraintSpringAlongAxis& other);
		virtual ~ConstraintSpringAlongAxis();
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// The shared properties (0x1066FE70 / 0x10670550); the setter also takes the constants over
		ConstraintSpringAlongAxisSharedProperties* GetSharedProperties() const;
		void SetSharedProperties(ConstraintSpringAlongAxisSharedProperties* properties);
		// The constants of the properties, scaled by the masses of the objects the properties ask for (0x10670110)
		void UpdateConstants();
		// The points and the axis (0x1066FE90 / 0x1066FEE0 / 0x1066FC50 and 0x1066FEB0); the setter normalises
		void SetPointA(const math::Vector* point);
		void SetPointB(const math::Vector* point);
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		// The distance at which the spring is at rest (0x1066FF00) and the constants (0x1066FF10 / 0x1066FF20)
		void SetStableDistance(float value);
		void SetSpringConstant(float value);
		void SetDampingConstant(float value);

		ConstraintSpringAlongAxisSharedProperties* sharedProperties;  // 0x24
		math::Vector pointA;          // 0x28
		math::Vector axisA;           // 0x34
		math::Vector pointB;          // 0x40
		float stableDistance;         // 0x4C
		float springConstant;         // 0x50
		float dampingConstant;        // 0x54
	};

	// Keeps an axis of the second object at a right angle to an axis of the first
	class ConstraintPerpendicular2Axes : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x106708B0)
		ConstraintPerpendicular2Axes();
		// Between the objects two handles name (0x106709A0)
		ConstraintPerpendicular2Axes(const CollisionHandle* first, const CollisionHandle* second);
		virtual void Rotate(const math::Matrix* matrix);
		virtual unsigned short GetKind(int unused);

		// The axes (0x106707B0 / 0x10670820 and 0x106707C0 / 0x10670860); the setters normalise, the first also sets
		// the local axis
		const math::Vector* GetAxisA() const;
		void SetAxisA(const math::Vector* axis);
		const math::Vector* GetAxisB() const;
		void SetAxisB(const math::Vector* axis);

		math::Vector axisA;           // 0x24
		math::Vector axisALocal;      // 0x30 (the axis before the matrix turns it into axisA)
		math::Vector axisB;           // 0x3C
		float unknown48;              // 0x48
		float unknown4C;              // 0x4C
	};

	// Keeps the distance between a point of each object along an axis
	class ConstraintFixDistanceAlongAxis : public Constraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A constraint between no objects (0x106783E0)
		ConstraintFixDistanceAlongAxis();
		// Between the objects two handles name (0x10678440)
		ConstraintFixDistanceAlongAxis(const CollisionHandle* first, const CollisionHandle* second);
		virtual void ScaleBy(const math::Vector* scale);
		virtual unsigned short GetKind(int unused);

		// The points (0x106784A0 / 0x106784C0) and the axis (0x106784E0; it is normalised and must not be of no length)
		void SetPointA(const math::Vector* point);
		void SetPointB(const math::Vector* point);
		void SetAxis(const math::Vector* newAxis);
		// The distance and how the correction of it is limited (0x10678550 / 0x10678560 / 0x10678570)
		void SetDistance(float value);
		void SetDistanceCorrectionScale(float value);
		void SetMaxDistanceCorrectionForce(float value);

		math::Vector pointA;          // 0x24
		math::Vector pointB;          // 0x30
		math::Vector axis;            // 0x3C
		float distance;               // 0x48
		float distanceCorrectionScale;  // 0x4C
		float maxDistanceCorrectionForce;  // 0x50
		float unknown54;              // 0x54
		float unknown58;              // 0x58
		float unknown5C;              // 0x5C
	};
}

#endif
